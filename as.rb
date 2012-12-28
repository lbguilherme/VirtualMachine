#! /usr/bin/ruby -I.

require 'parser'
require 'instructions'
require 'trollop'
require 'pp'

Registers = [nil] + %w[
eax ebx ecx edx esi edi esp ebp
 ax  bx  cx  dx  si  di  sp  bp
 ah  bh  ch  dh  __  __  __  __
 al  bl  cl  dl  __  __  __  __
].map(&:to_sym)

$opts = Trollop::options do
    opt :output, "Output file", :type => :string
    opt :verbose, "Print extra information while processing files"
end

$opts[:input] = ARGV.uniq

if ARGV.size == 0
    Trollop::die "No input files"
end

if $opts[:output] == nil and ARGV.size != 1
    Trollop::die "No output file"
end

if $opts[:output] == nil
    $opts[:output] = $opts[:input].first.sub(/\.\w+$|$/i, ".bin")
end

$asm = {}

$opts[:input].each do |input|
    if $opts[:verbose]
        puts "Parsing file '#{input}'..."
    end
    parser = Parser.new
    begin
        $asm[input] = parser.parse(File.read(input))
    rescue Errno::ENOENT
        $stderr.puts $!.message
        exit!
    rescue Parslet::ParseFailed
        $stderr.puts "Syntax Error: #{$!.message}"
        exit!
    end
end

$rodata = [[0]]
$instructions = [[0]]
$data = [[0]]
$globl = []
$static = 0
$labels = {}
$local = {}
$variables = {}
$functions = {}
$section = nil

$asm.each do |input, asm|
    $labels[input] = {}
    $local[input] = []
    $rodata << [$rodata[-1][0]]
    $rodata[-2] = input
    $instructions << [$instructions[-1][0]]
    $instructions[-2] = input
    $data << [$data[-1][0]]
    $data[-2] = input
    if $opts[:verbose]
        puts "Processing file '#{input}'..."
    end
    asm.each do |asmline|
        type = asmline.keys.first
        data = asmline[type]
        case type
        when :label
            if $globl.include? data.to_sym
                $labels.each do |file, labels|
                    labels.each do |sym, value|
                        if data.to_sym == sym
                            $stderr.puts "Error: Multiple definition of symbol '#{sym}'."
                            exit!
                        end
                    end
                end
            end
            $labels[input][data.to_sym] = [$section, case $section
            when :rodata; $rodata.last[0]
            when :data; $data.last[0]
            when :text; $instructions.last[0]
            end]
        when :directive
            mnemonic = data[:mnemonic].to_s[1..-1].to_sym
            arguments = [*data[:arguments]]
            arguments.map! do |arg|
                if Hash === arg
                    [arg.keys.first, arg.values.first]
                else
                    [arg[0], arg[1]]
                end
            end
            arguments.map! do |arg|
                if Parslet::Slice === arg[1]
                    [arg[0], arg[1].to_s]
                else
                    [arg[0], ""]
                end
            end
            arguments.map! do |arg|
                case arg[0]
                when :integer; eval(arg[1])
                when :identifier; arg[1].to_sym
                when :string; arg[1]
                when :nothing; nil
                end
            end
            case mnemonic
            when :file
            when :p2align
                # todo
            when :local
                variable = arguments[0]
                $local[input] << arguments[0]
            when :comm
                variable = arguments[0]
                size = arguments[1]
                align = arguments[2]
                if $variables.keys.include? variable
                    $stderr.puts "Error: Multiple definition of global variable '#{variable}'."
                    exit!
                end
                unless $static % align == 0
                    $static += align - $static % align
                end
                unless $local[input].include? variable
                    $labels[input][variable] = [:static, $static]
                    $variables[variable] = input
                end
                $static += size
            when :section
                section = arguments[0]
                $section = section[1..-1].to_s.sub(/\..*/, "").to_sym
            when :text
                $section = :text
            when :data
                $section = :data
            when :bss
                $section = :data
            when :align
                align = arguments[0]
                case $section
                when :rodata
                    unless $rodata.last[0] % align == 0
                        $rodata.last[0] += align - $rodata.last[0] % align
                    end
                when :data
                    unless $data.last[0] % align == 0
                        $data.last[0] += align - $data.last[0] % align
                    end
                end
            when :string
                string = arguments[0]
                string.gsub!(/\\([\\nrbtfv"']|[0-9]{3})/) do
                    match = $1
                    if /^[0-9]{3}$/ =~ match
                        "" << match.to_i(8)
                    else
                        eval("\"\\#{match}\"")
                    end
                end
                case $section
                when :rodata
                    $rodata.last << string
                    $rodata << [$rodata.last[0] + string.size+1]
                when :data
                    $data.last << string
                    $data << [$data.last[0] + string.size+1]
                end
            when :long
                value = arguments[0]
                case $section
                when :rodata
                    $rodata.last << value
                    $rodata << [$rodata.last[0] + 4]
                when :data
                    $data.last << value
                    $data << [$data.last[0] + 4]
                end
            when :zero
                count = arguments[0]
                case $section
                when :rodata
                    $rodata.last << ("\0" * (count-1))
                    $rodata << [$rodata.last[0] + count]
                when :data
                    $data.last << ("\0" * (count-1))
                    $data << [$data.last[0] + count]
                end
            when :globl
                symbol = arguments[0]
                unless $globl.include? symbol
                    $globl << symbol
                end
            when :type
                symbol = arguments[0]
                type = arguments[1]
                next unless $globl.include? symbol
                case type
                when :@function
                    $functions[symbol] = input
                when :@object
                    $variables[symbol] = input
                end
            when :size
            when :ident
            else
                if mnemonic.to_s !~ /^cfi/
                    $stderr.puts "Fixme: Unknown meta-instruction '#{mnemonic}'."
                    exit!
                end
            end
        when :instruction
            mnemonic = data[:mnemonic].to_s.downcase.gsub(/[^a-z]/, "_").to_sym
            arguments = [*data[:arguments]]
            name = nil
            wide = nil
            InstructionList.each do |entry|
                this = case entry[1]
                when 8; mnemonic.to_s == entry[0].to_s+"b"
                when 16; mnemonic.to_s == entry[0].to_s+"w"
                when 32; mnemonic.to_s == entry[0].to_s+"l"
                end
                if this
                    name = entry[0]
                    wide = entry[1]
                end
            end
            unless name
                wides = []
                InstructionList.each do |entry|
                    if entry[0] == mnemonic
                        name = entry[0]
                        wide = entry[1]
                        wides << wide
                    end
                end
                wides.uniq!
                case
                when wides.size > 1
                    $stderr.puts "Fixme: Ambiguos instruction '#{mnemonic}'."
                    exit!
                when wides.size == 0
                    $stderr.puts "Fixme: Unknown instruction '#{mnemonic}'."
                    exit!
                end
            end
            instr = [name.to_sym, wide, 0, []]
            arguments.each do |arg|
                if Hash === arg
                    type = arg.keys.first
                    value = arg.values.first
                else
                    type = arg[0]
                    value = arg[1]
                end
                case type
                when :register
                    instr[-1] << [:reg, value.to_sym]
                when :immediate
                    case value.keys.first
                    when :integer
                        instr[-1] << [:imm, eval(value[:integer])]
                    when :identifier
                        instr[-1] << [:imm, value[:identifier].to_sym]
                    end
                when :memory
                    offset = 0
                    if value[:offset]
                        case value[:offset].keys.first
                        when :integer
                            offset = eval(value[:offset][:integer])
                        when :identifier
                            offset = value[:offset][:identifier].to_sym
                        end
                    end
                    base = nil
                    if value[:base]
                        base = value[:base][:register].to_sym
                    end
                    index = nil
                    if value[:index]
                        index = value[:index][:register].to_sym
                    end
                    scale = 1
                    if value[:scale]
                        scale = eval(value[:scale][:integer])
                    end
                    instr[-1] << [:mem, offset, base, index, scale]
                end
            end
            opcode = nil
            InstructionList.each_with_index do |spec, op|
                next unless instr[0] == spec[0] and instr[1] == spec[1]
                next unless spec[2].size == instr[-1].size
                matches = true
                spec[2].size.times do |i|
                    arg = instr[-1][i][0]
                    argt = spec[2][i][0]
                    unless arg == argt
                        matches = false
                    end
                end
                next unless matches
                opcode = op
            end
            if opcode == nil
                if $opts[:verbose]
                    print "\n"
                end
                $stderr.puts "Error: Unable to handle instruction #{instr[0]}#{instr[1]} with arguments #{instr[-1].inspect}."
                exit!
            end
            size = 2
            InstructionList[opcode][2].each do |argt|
                case argt[0]
                when :imm; size += argt[1]/8
                when :reg; size += 1
                when :mem; size += 6
                end
            end
            instr[2] = opcode
            $instructions.last << instr
            $instructions << [$instructions.last[0] + size]
        end
    end
end

def solvesym(sym, file)
    values = {}
    $labels.keys.each do |file|
        values[file] = $labels[file][sym] if $labels[file].include? sym
    end
    if values[file]
        value = values[file]
    else
        if values.size == 1
            value = values.values.first
        elsif values.size == 0
            if $opts[:verbose]
                print "\n"
            end
            $stderr.puts "Error: Undefined reference to symbol '#{sym}'."
            exit!
        else
            if $opts[:verbose]
                print "\n"
            end
            $stderr.puts "Error: Ambiguos use of symbol '#{sym}'."
            exit!
        end
    end
    case value[0]
    when :rodata; return 1 + value[1]
    when :text; return 1 + $rodata.last[0] + value[1]
    when :data; return 1 + $rodata.last[0] + $instructions.last[0] + value[1]
    when :static; return 1 + $rodata.last[0] + $instructions.last[0] + $data.last[0] + value[1]
    end
end

File.open($opts[:output], "w") do |output|
    output << ".DRONEWARBIN."

    output << [$rodata.last[0]].pack("V")
    file = nil
    $rodata.each do |rodata|
        if $opts[:verbose]
            print "\rGenerating rodata section... #{rodata[0]} bytes"
        end
        case rodata
        when String
            file = rodata
        when Array
            break if rodata.size == 1
            value = rodata[1]
            case value
            when Symbol
                output << [solvesym(value, file)].pack("V")
            when String
                output << value << "\0"
            when Integer
                output << [value].pack("V")
            end
        end
    end
    if $opts[:verbose]
        print "\n"
    end

    output << [$instructions.last[0]].pack("V")
    file = nil
    $instructions.each do |instr|
        if $opts[:verbose]
            print "\rGenerating text section... #{instr[0]} bytes"
        end
        case instr
        when String
            file = instr
        when Array
            break if instr.size == 1
            output << [instr[1][2]].pack("v")
            instr[1][-1].each_with_index do |arg, ia|
                case arg[0]
                when :imm
                    i = 0
                    case arg[1]
                    when Integer; i = arg[1]
                    when Symbol; i = solvesym(arg[1], file)
                    end
                    case InstructionList[instr[1][2]][2][ia][1]
                    when 8; output << ("" << i)
                    when 16; output << [i].pack("v")
                    when 32; output << [i].pack("V")
                    end
                when :reg
                    output << ("" << Registers.index(arg[1]))
                when :mem
                    case arg[1]
                    when Integer; output << [arg[1]].pack("V")
                    when Symbol; output << [solvesym(arg[1], file)].pack("V")
                    end
                    v = Registers.index(arg[2]) << 9
                    v += Registers.index(arg[3]) << 2
                    case arg[4]
                    when 1; v += 0b00
                    when 2; v += 0b01
                    when 4; v += 0b10
                    when 8; v += 0b11
                    end
                    output << [v].pack("v")
                end
            end
        end
    end
    if $opts[:verbose]
        print "\n"
    end

    output << [$data.last[0]].pack("V")
    file = nil
    $data.each do |data|
        if $opts[:verbose]
            print "\rGenerating data section... #{data[0]} bytes"
        end
        case data
        when String
            file = data
        when Array
            break if data.size == 1
            value = data[1]
            case value
            when Symbol
                output << [solvesym(value, file)].pack("V")
            when String
                output << value << "\0"
            when Integer
                output << [value].pack("V")
            end
        end
    end
    if $opts[:verbose]
        print "\n"
    end

    if $opts[:verbose]
        print "Generating static section... #{$static} bytes\n"
    end
    output << [$static].pack("V")

    output << [$variables.size + $functions.size].pack("v")
    $variables.each do |sym, file|
        if $opts[:verbose]
            print "\rGenerating symbol table... #{$variables.keys.index(sym)+1} variables + 0 functions"
        end
        output << [sym.to_s.size].pack("v")
        output << sym.to_s
        output << [solvesym(sym, file)].pack("V")
    end
    $functions.each do |sym, file|
        if $opts[:verbose]
            print "\rGenerating symbol table... #{$variables.size} variables + #{$functions.keys.index(sym)+1} functions"
        end
        output << [sym.to_s.size].pack("v")
        output << sym.to_s
        output << [solvesym(sym, file)].pack("V")
    end
    if $opts[:verbose]
        print "\n"
    end
end

if $opts[:verbose]
    puts "Done. Final size: #{File.size($opts[:output])} bytes."
end
