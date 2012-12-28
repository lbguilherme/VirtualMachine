
require 'parslet'

class Parser < Parslet::Parser
    rule(:space)  { match["\s\t\f"].repeat(1) }
    rule(:space?) { space.maybe }
    rule(:newline) { match["\r\n;"].repeat(1) }

    rule(:nothing) {
        str("").as(:nothing)
    }

    rule(:integer) {
        (
            match["+-"].maybe >> (
                (str("0")) |
                (match["1-9"] >> match["0-9"].repeat) |
                (str("0b") >> match["01"].repeat(1)) |
                (str("0") >> match["0-9"].repeat(1)) |
                (str("0x") >> match["0-9A-Fa-f"].repeat(1))
            )
        ).as(:integer)
    }

    rule(:string) {
        str('"') >> (
            str('\\') >> any |
            str('"').absent? >> any
        ).repeat.as(:string) >> str('"')
    }

    rule(:identifier) {
        (match("[a-zA-Z._@-]") >> match("[0-9a-zA-Z._@-]").repeat(0)).as(:identifier)
    }

    rule(:directive_argument) { (string | integer | identifier | nothing) >> space? }
    rule(:directive_mnemonic) { (str(".") >> match["a-zA-Z0-9_"].repeat(1)).as(:mnemonic) }

    rule(:directive) {
        (
            directive_mnemonic >>
            (
                space >> directive_argument >>
                (
                    str(",") >> space? >> directive_argument
                ).repeat
            ).as(:arguments).maybe
        ).as(:directive) >> space?
    }

    rule(:register) {
        str("%") >> (
            str("eax") | str("ebx") | str("ecx") | str("edx") |
            str("esi") | str("edi") | str("esp") | str("ebp") |
            str("ax") | str("bx") | str("cx") | str("dx") |
            str("si") | str("di") | str("sp") | str("bp") |
            str("ah") | str("bh") | str("ch") | str("dh") |
            str("al") | str("bl") | str("cl") | str("dl")
        ).as(:register)
    }

    rule(:memory) {
        (((integer | identifier).as(:offset) >> space?).maybe >> (str("(") >> (
            register.as(:base).maybe >> (
                str(",") >> space? >> register.as(:index).maybe >> (
                    str(",") >> space? >> integer.as(:scale).maybe
                ).maybe
            ).maybe
        ) >> str(")")).maybe).as(:memory)
    }

    rule(:immediate) {
        str("$") >> (integer | identifier).as(:immediate)
    }

    rule(:instruction_argument) { str("*").maybe >>
                                  (immediate | register | memory) >> space? }
    rule(:instruction_mnemonic) { (str("rep ").maybe >> match["a-zA-Z"].repeat(1)).as(:mnemonic) }

    rule(:instruction) {
        (
            instruction_mnemonic >>
            (
                space >> instruction_argument >>
                (
                    str(",") >> space? >> instruction_argument
                ).repeat
            ).as(:arguments).maybe
        ).as(:instruction) >> space?
    }

    rule(:label) {
        (match("[a-zA-Z._@]") >> match("[a-zA-Z._@0-9]").repeat(0)).as(:label) >>
        str(":") >> space?
    }

    rule(:comment) { str("#") >> match["^\r\n"].repeat }

    rule(:line) { space? >> (comment | label | directive | instruction) }
    rule(:asm) { line >> (newline >> line).repeat >> newline.maybe }

    root(:asm)

end
