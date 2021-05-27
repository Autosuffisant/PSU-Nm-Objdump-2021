/*
** EPITECH PROJECT, 2021
** nm
** File description:
** Recreate the nm function
*/

#include "nm.h"

char is_undefined_64(Elf64_Sym *symbol_64)
{
    if (symbol_64->st_shndx == SHN_UNDEF)
    {
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_WEAK)
            return 'w';
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_GLOBAL)
            return 'U';
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_LOCAL)
            return 'u';
    }
    if (symbol_64->st_shndx == SHN_COMMON)
        return 'C';
    return 0;
}

char is_data_64(Elf64_Sym *symbol_64, Elf64_Shdr *shdr)
{
    if ((shdr[symbol_64->st_shndx].sh_type == SHT_PROGBITS
    && (shdr[symbol_64->st_shndx].sh_flags & SHF_ALLOC))
    || (shdr[symbol_64->st_shndx].sh_type == SHT_DYNAMIC)) {
        if (shdr[symbol_64->st_shndx].sh_flags & SHF_WRITE) {
            if (ELF64_ST_BIND(symbol_64->st_info) == STB_GLOBAL)
                return 'D';
            if (ELF64_ST_BIND(symbol_64->st_info) == STB_LOCAL)
                return 'd';
            if (ELF64_ST_BIND(symbol_64->st_info) == STB_WEAK)
                return 'W';
        } else {
            if (ELF64_ST_BIND(symbol_64->st_info) == STB_GLOBAL)
                return 'R';
            if (ELF64_ST_BIND(symbol_64->st_info) == STB_LOCAL)
                return 'r';
            if (ELF64_ST_BIND(symbol_64->st_info) == STB_WEAK)
                return 'W';
        }
    }
    return 0;
}

char is_prog_64(Elf64_Sym *symbol_64, Elf64_Shdr *shdr)
{
    if (ELF64_ST_TYPE(symbol_64->st_info) == STT_FUNC
    && shdr[symbol_64->st_shndx].sh_type == SHT_PROGBITS
    && (shdr[symbol_64->st_shndx].sh_flags & SHF_EXECINSTR)
    && (shdr[symbol_64->st_shndx].sh_flags & SHF_ALLOC)) {
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_WEAK)
            return 'W';
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_GLOBAL)
            return 'T';
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_LOCAL)
            return 't';
    }
    return 0;
}

char is_notype_64(Elf64_Sym *symbol_64, Elf64_Shdr *shdr)
{
    if ((ELF64_ST_TYPE(symbol_64->st_info) == STT_OBJECT
    || ELF64_ST_TYPE(symbol_64->st_info) == STT_NOTYPE)
    && (shdr[symbol_64->st_shndx].sh_flags & SHF_WRITE)
    && (shdr[symbol_64->st_shndx].sh_flags & SHF_ALLOC)) {
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_WEAK)
            return 'W';
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_GLOBAL)
            return 'T';
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_LOCAL)
            return 't';
    }
    return '?';
}

char get_type_64(Elf64_Sym *symbol_64, Elf64_Shdr *shdr)
{
    char type;

    if ((type = is_undefined_64(symbol_64)) != 0)
        return (type);
    if (symbol_64->st_shndx == SHN_ABS)
        return 'A';
    if (ELF64_ST_TYPE(symbol_64->st_info) == STT_OBJECT
    && ELF64_ST_BIND(symbol_64->st_info) == STB_WEAK)
        return 'V';
    if (shdr[symbol_64->st_shndx].sh_type == SHT_NOBITS) {
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_WEAK)
            return 'W';
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_GLOBAL)
            return 'B';
        if (ELF64_ST_BIND(symbol_64->st_info) == STB_LOCAL)
            return 'b';
    }
    if ((type = is_prog_64(symbol_64, shdr)) != 0)
        return type;
    if ((type = is_data_64(symbol_64, shdr)) != 0)
        return type;
    type = is_notype_64(symbol_64, shdr);
    return type;
}