/*
** EPITECH PROJECT, 2021
** nm
** File description:
** Recreate the nm function
*/

#include "nm.h"

int print_symbols_64(elf_data_t *elf)
{
    char sym_char;

    for (long int i = 0; i != elf->symbols_size; i++)
    {
        if (elf->symbols_64[i].st_info != STT_FILE
        && elf->symbols_64[i].st_name != 0)
        {
            sym_char = get_type_64(&elf->symbols_64[i], elf->shdr_64);
            if (((unsigned int)elf->symbols_64[i].st_value == 0
            && sym_char == 'w') || sym_char == 'U')
                printf("\t\t ");
            else
                printf("%016x ", (unsigned int)elf->symbols_64[i].st_value);
            printf("%c ", get_type_64(&elf->symbols_64[i], elf->shdr_64));
            printf("%s\n", &elf->str_symbols[elf->symbols_64[i].st_name]);
        }
    }
    return 0;
}

int get_symbols_64(elf_data_t *elf)
{
    bool sym_found = false;

    for (int i = 0; i < elf->ehdr_64->e_shnum; i++)
    {
        if (elf->shdr_64[i].sh_type == SHT_SYMTAB)
        {
            elf->str_symbols = (unsigned char *)elf->data
            + elf->shdr_64[elf->shdr_64[i].sh_link].sh_offset;
            elf->symbols_size = elf->shdr_64[i].sh_size
            / elf->shdr_64[i].sh_entsize;
            elf->symbols_64 = (Elf64_Sym *)((char *)elf->ehdr_64 +
                                            elf->shdr_64[i].sh_offset);
            sym_found = true;
            i = elf->ehdr_64->e_shnum;
        }
    }
    if (sym_found == true)
        return print_symbols_64(elf);
    return 84;
}