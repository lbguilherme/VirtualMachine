
InstructionTable = {
    :"nop" => ["l", [[1]]],
    :"mov" => ["bwl", [:value, :ref, [1, 1, 1]]],
    :"movsb" => ["wl", [:value8, :reg, [1, 1]]],
    :"movsw" => ["l", [:value16, :reg, [1]]],
    :"movzb" => ["wl", [:value8, :reg, [1, 1]]],
    :"movzw" => ["l", [:value16, :reg, [1]]],
    :"push" => ["bwl", [:value, [2, 2, 2]]],
    :"pop" => ["bwl", [:ref, [2, 2, 2]]],
    :"add" => ["bwl", [:value, :ref, [1, 1, 1]]],
    :"adc" => ["bwl", [:value, :ref, [1, 1, 1]]],
    :"and" => ["bwl", [:value, :ref, [1, 1, 1]]],
    :"sub" => ["bwl", [:value, :ref, [1, 1, 1]]],
    :"sbb" => ["bwl", [:value, :ref, [1, 1, 1]]],
    :"xor" => ["bwl", [:value, :ref, [1, 1, 1]]],
    :"or" => ["bwl", [:value, :ref, [1, 1, 1]]],
    :"not" => ["bwl", [:ref, [1, 1, 1]]],
    :"neg" => ["bwl", [:ref, [1, 1, 1]]],
    :"inc" => ["bwl", [:ref, [1, 1, 1]]],
    :"dec" => ["bwl", [:ref, [1, 1, 1]]],
    :"call" => ["l", [:ptr, [50]]],
    :"leave" => ["l", [[2]]],
    :"ret" => ["l", [[50]]],
    :"int" => ["l", [:imm, [100]]],
    :"cmp" => ["bwl", [:value, :value, [1, 1, 1]]],
    :"test" => ["bwl", [:value, :value, [1, 1, 1]]],
    :"jmp" => ["l", [:ptr, [20]]],
    [:"j"] => ["l", [:ptr, [25]]],
    [:"set"] => ["b", [:ref, [5]]],
    :"lea" => ["bwl", [:mem, :reg32, [1, 1, 1]]],
    :"mul" => ["bwl", [:ref, [5, 5, 5]]],
    :"imul" => ["bwl", [:ref, [5, 5, 5]], [:ref, :reg, [6, 6, 6]], [:ref, :reg, :imm, [8, 8, 8]]],
    :"div" => ["bwl", [:ref, [25, 30, 40]]],
    :"idiv" => ["bwl", [:ref, [25, 30, 40]]],
    :"cbtw" => ["b", [[3]]],
    :"cwtl" => ["w", [[3]]],
    :"cwtd" => ["w", [[3]]],
    :"cltd" => ["l", [[3]]],
    :"rep_movs" => ["bwl", [[10, 10, 10]]],
    :"movs" => ["bwl", [[2, 2, 2]]],
    :"sal" => ["bwl", [:value8, :ref, [1, 1, 1]], [:ref, [1, 1, 1]]],
    :"sar" => ["bwl", [:value8, :ref, [1, 1, 1]], [:ref, [1, 1, 1]]],
    :"shl" => ["bwl", [:value8, :ref, [1, 1, 1]], [:ref, [1, 1, 1]]],
    :"shr" => ["bwl", [:value8, :ref, [1, 1, 1]], [:ref, [1, 1, 1]]],
    :"bsf" => ["wl", [:value, :reg, [5, 5]]],
    :"bsr" => ["wl", [:value, :reg, [5, 5]]],
}

CC = %w[o no b nae nb ae e z ne nz be na nbe a s ns p pe np po l nge nl ge le ng nle g]

InstructionList = []

InstructionTable.each do |entry|
    entry[1][0].chars.each_with_index do |w, wi|
        s = 32
        case w
        when "b"; s = 8
        when "w"; s = 16
        when "l"; s = 32
        end
        entry[1][1..-1].each do |args|
            args2 = []
            args[0..-2].each do |arg|
                case arg
                when :value; args2 << [[:imm, s], [:reg, s], [:mem, s]]
                when :value8; args2 << [[:imm, 8], [:reg, 8], [:mem, 8]]
                when :value16; args2 << [[:imm, 16], [:reg, 16], [:mem, 16]]
                when :value32; args2 << [[:imm, 32], [:reg, 32], [:mem, 32]]
                when :ref; args2 << [[:reg, s], [:mem, s]]
                when :reg; args2 << [[:reg, s]]
                when :reg8; args2 << [[:reg, 8]]
                when :reg16; args2 << [[:reg, 16]]
                when :reg32; args2 << [[:reg, 32]]
                when :mem; args2 << [[:mem, s]]
                when :imm; args2 << [[:imm, s]]
                when :ptr; args2 << [[:reg, s], [:mem, s]]
                end
            end
            list = []
            if args2.size > 0
                args2.shift.each {|a| list << [a] }
                args2.each do |arg|
                    newlist = []
                    arg.each do |a|
                        newlist += list.map {|l| l.dup << a }
                    end
                    list = newlist
                end
            end
            list = [[]] if list.size == 0
            list.each do |kind|
                if Array === entry[0]
                    CC.each do |cc|
                        InstructionList << [(entry[0][0].to_s+cc).to_sym, s, kind, args[0..-2], args[-1][wi], [entry[0][0], cc.to_sym]]
                    end
                else
                    InstructionList << [entry[0], s, kind, args[0..-2], args[-1][wi]]
                end
            end
        end
    end
end

InstructionList.uniq!

if __FILE__ == $0 and ARGV == ["generate"]
    File.open("include/instr_decl.hpp", "w") do |f|
        f << "// This file is generated by instructions.rb. Do not edit here.\n"
        f << "\n"
        decls = []
        InstructionTable.each do |entry|
            entry[1][1..-1].each do |arglist|
                entry[1][0].chars.each do |w|
                    s = 32
                    case w
                    when "b"; s = 8
                    when "w"; s = 16
                    when "l"; s = 32
                    end
                    if Array === entry[0]
                        decl = "    void _#{entry[0][0]}cc#{s}(bool cc"
                        decl << ", " if arglist.size > 1
                    else
                        decl = "    void _#{entry[0]}#{s}("
                    end
                    arglist[0..-2].each_with_index do |argt, i|
                        case argt
                        when :value, :ptr, :imm; decl << "uint#{s}_t arg#{i+1}"
                        when :value8; decl << "uint8_t arg#{i+1}"
                        when :value16; decl << "uint16_t arg#{i+1}"
                        when :value32; decl << "uint32_t arg#{i+1}"
                        when :ref, :reg, :mem; decl << "uint#{s}_t& arg#{i+1}"
                        when :reg8; decl << "uint8_t& arg#{i+1}"
                        when :reg16; decl << "uint16_t& arg#{i+1}"
                        when :reg32; decl << "uint32_t& arg#{i+1}"
                        end
                        if i+1 < arglist.size-1
                            decl << ", "
                        end
                    end
                    decl << ");"
                    decls << decl
                end
            end
        end
        f << decls.uniq.sort.join("\n") << "\n\n"
    end
    File.open("src/instr.cpp", "w") do |f|
        f << "// This file is generated by instructions.rb. Do not edit here.\n"
        f << "\n"
        f << "#include <string>\n"
        f << "#include <stdexcept>\n"
        f << "#include <iostream>\n"
        f << "\n"
        f << "#include <vm.hpp>\n"
        f << "\n"
        f << "void VirtualMachine::runInstruction()\n"
        f << "{\n"
        f << "    uint16_t opcode = toNative(mem<uint16_t>(toNative(eip)));\n"
        f << "    eip = fromNative(toNative(eip) + 2);\n"
        f << "    switch (opcode)\n"
        f << "    {\n"
        InstructionList.each_with_index do |instr, i|
            f << "        case #{i}:#{" " * (8-i.to_s.size)}// #{instr[0]}("
            instr[2].each_with_index do |arg, ai|
                f << arg[0].to_s
                f << arg[1].to_s unless arg[0].to_s[-1].to_i != 0
                f << ", " unless ai+1 == instr[2].size
            end
            f << ")\n"
            f << "        {\n"
            f << "            clocks += #{instr[4]};\n" if instr[4] != 0
            f << "#ifndef NDEBUG\n"
            iname = "#{instr[0].to_s.sub("_", " ")}#{{8 => "b", 16 => "w", 32 => "l"}[instr[1]]}"
            f << "            std::clog << \"\\t#{iname}#{" " * (12 - iname.size)}\";\n"
            f << "#endif\n"
            instr[2].each_with_index do |arg, ai|
                f << "            uint#{arg[1]}_t"
                if arg[0] != :imm and instr[3][ai] != :ptr
                    f << "&"
                end
                f << " arg#{ai+1} = "
                if instr[3][ai] == :ptr
                    case arg[0]
                    when :reg; f << "readRegister<uint#{arg[1]}_t>();\n"
                    when :mem; f << "(char*)&readMemory<uint#{arg[1]}_t>() - (char*)memory;\n"
                    end
                else
                    case arg[0]
                    when :imm; f << "readImmediate<uint#{arg[1]}_t>();\n"
                    when :reg; f << "readRegister<uint#{arg[1]}_t>();\n"
                    when :mem; f << "readMemory<uint#{arg[1]}_t>();\n"
                    end
                end
                unless ai+1 == instr[2].size
                    f << "#ifndef NDEBUG\n"
                    f << "            std::clog << \", \";\n"
                    f << "#endif\n"
                end
            end
            f << "#ifndef NDEBUG\n"
            f << "            std::clog << \"\\n\";\n"
            f << "#endif\n"
            if instr[5]
                f << "            _#{instr[5][0]}cc#{instr[1]}(_#{instr[5][1].to_s.upcase}()"
                f << ", " if instr[2].size > 0
            else
                f << "            _#{instr[0]}#{instr[1]}("
            end
            instr[2].size.times do |ai|
                f << "arg#{ai+1}#{", " unless ai+1 == instr[2].size}"
            end
            f << ");\n"
            f << "            break;\n"
            f << "        }\n"
        end
        f << "        default:\n"
        f << "            throw std::runtime_error(\"Invalid instruction code: \" + std::to_string(opcode));\n"
        f << "    }\n"
        f << "}\n"
    end
end
