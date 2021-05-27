/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** recreate the objdump function
*/

#include "objdump.h"

uint32_t get_flag_64(elf_data_t *elf)
{
    uint32_t flag = 0;
    bool is_symbol_flag = false;

    for (unsigned int i = 0; i < elf->ehdr_64->e_shnum; i++)
        if (elf->shdr_64[i].sh_type != SHT_SYMTAB
        || elf->shdr_64[i].sh_type != SHT_DYNAMIC)
            is_symbol_flag = true;
    if (is_symbol_flag == true)
        flag |= HAS_SYMS;
    if (elf->ehdr_64->e_type == ET_EXEC)
        flag |= EXEC_P;
    if (elf->ehdr_64->e_type == ET_REL)
        flag |= HAS_RELOC;
    if (elf->ehdr_64->e_phnum != 0)
        flag |= D_PAGED;
    if (elf->ehdr_64->e_type == ET_DYN)
        flag |= DYNAMIC;
    return flag;
}

void print_flags_64(elf_data_t *elf)
{
    int	flag_print = 0;
    bool is_symbol_flag = false;

    if (elf->ehdr_64->e_type == ET_REL)
        flag_print += printf("HAS_RELOC");
    if (elf->ehdr_64->e_type == ET_EXEC)
        flag_print += printf((flag_print)? ", EXEC_P": "EXEC_P");
    for (unsigned int i = 0; i < elf->ehdr_64->e_shnum; i++)
        if (elf->shdr_64[i].sh_type != SHT_SYMTAB
        || elf->shdr_64[i].sh_type != SHT_DYNAMIC)
            is_symbol_flag = true;
    if (is_symbol_flag == true)
        flag_print += printf((flag_print)? ", HAS_SYMS": "HAS_SYMS");
    if (elf->ehdr_64->e_type == ET_DYN)
        flag_print += printf((flag_print)? ", DYNAMIC": "DYNAMIC");
    if (elf->ehdr_64->e_phnum != 0)
        flag_print += printf((flag_print)? ", D_PAGED": "D_PAGED");
    printf("\n");
}

int	check_section_64(Elf64_Shdr *shdr, int i)
{
    return (shdr[i].sh_type != SHT_NOBITS
        && shdr[i].sh_size > 0
        && shdr[i].sh_name
        && shdr->sh_flags != SHF_INFO_LINK
        && (shdr[i].sh_addr || (!shdr[i].sh_addr
        && shdr[i].sh_type != SHT_REL
        && shdr[i].sh_type != SHT_RELA
        && shdr[i].sh_type != SHT_SYMTAB
        && shdr[i].sh_type != SHT_STRTAB))
    );
}