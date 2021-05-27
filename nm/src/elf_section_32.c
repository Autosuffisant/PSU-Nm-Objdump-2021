/*
** EPITECH PROJECT, 2021
** nm
** File description:
** Recreate the nm function
*/

#include "nm.h"

char is_undefined_32(Elf32_Sym *symbol_32)
{
    if (symbol_32->st_shndx == SHN_UNDEF)
    {
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_WEAK)
            return 'w';
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_GLOBAL)
            return 'U';
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_LOCAL)
            return 'u';
    }
    if (symbol_32->st_shndx == SHN_COMMON)
        return 'C';
    return 0;
}

char is_data_32(Elf32_Sym *symbol_32, Elf32_Shdr *shdr)
{
    if ((shdr[symbol_32->st_shndx].sh_type == SHT_PROGBITS
    && (shdr[symbol_32->st_shndx].sh_flags & SHF_ALLOC))
    || (shdr[symbol_32->st_shndx].sh_type == SHT_DYNAMIC)) {
        if (shdr[symbol_32->st_shndx].sh_flags & SHF_WRITE) {
            if (ELF32_ST_BIND(symbol_32->st_info) == STB_GLOBAL)
                return 'D';
            if (ELF32_ST_BIND(symbol_32->st_info) == STB_LOCAL)
                return 'd';
            if (ELF32_ST_BIND(symbol_32->st_info) == STB_WEAK)
                return 'W';
        } else {
            if (ELF32_ST_BIND(symbol_32->st_info) == STB_GLOBAL)
                return 'R';
            if (ELF32_ST_BIND(symbol_32->st_info) == STB_LOCAL)
                return 'r';
            if (ELF32_ST_BIND(symbol_32->st_info) == STB_WEAK)
                return 'W';
        }
    }
    return 0;
}

char is_prog_32(Elf32_Sym *symbol_32, Elf32_Shdr *shdr)
{
    if (ELF32_ST_TYPE(symbol_32->st_info) == STT_FUNC
    && shdr[symbol_32->st_shndx].sh_type == SHT_PROGBITS
    && (shdr[symbol_32->st_shndx].sh_flags & SHF_EXECINSTR)
    && (shdr[symbol_32->st_shndx].sh_flags & SHF_ALLOC)) {
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_WEAK)
            return 'W';
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_GLOBAL)
            return 'T';
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_LOCAL)
            return 't';
    }
    return 0;
}

char is_notype_32(Elf32_Sym *symbol_32, Elf32_Shdr *shdr)
{
    if ((ELF32_ST_TYPE(symbol_32->st_info) == STT_OBJECT
    || ELF32_ST_TYPE(symbol_32->st_info) == STT_NOTYPE)
    && (shdr[symbol_32->st_shndx].sh_flags & SHF_WRITE)
    && (shdr[symbol_32->st_shndx].sh_flags & SHF_ALLOC)) {
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_WEAK)
            return 'W';
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_GLOBAL)
            return 'T';
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_LOCAL)
            return 't';
    }
    return '?';
}

char get_type_32(Elf32_Sym *symbol_32, Elf32_Shdr *shdr)
{
    char type;

    if ((type = is_undefined_32(symbol_32)) != 0)
        return (type);
    if (symbol_32->st_shndx == SHN_ABS)
        return 'A';
    if (ELF32_ST_TYPE(symbol_32->st_info) == STT_OBJECT
    && ELF32_ST_BIND(symbol_32->st_info) == STB_WEAK)
        return 'V';
    if (shdr[symbol_32->st_shndx].sh_type == SHT_NOBITS) {
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_WEAK)
            return 'W';
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_GLOBAL)
            return 'B';
        if (ELF32_ST_BIND(symbol_32->st_info) == STB_LOCAL)
            return 'b';
    }
    if ((type = is_prog_32(symbol_32, shdr)) != 0)
        return type;
    if ((type = is_data_32(symbol_32, shdr)) != 0)
        return type;
    type = is_notype_32(symbol_32, shdr);
    return type;
}