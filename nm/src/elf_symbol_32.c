/*
** EPITECH PROJECT, 2021
** nm
** File description:
** Recreate the nm function
*/

#include "nm.h"

int print_symbols_32(elf_data_t *elf)
{
    char sym_char;

    for (long int i = 0; i != elf->symbols_size; i++)
    {
        if (elf->symbols_32[i].st_info != STT_FILE
        && elf->symbols_32[i].st_name != 0)
        {
            sym_char = get_type_32(&elf->symbols_32[i], elf->shdr_32);
            if (((unsigned int)elf->symbols_32[i].st_value == 0 &&
            sym_char == 'w') || sym_char == 'U')
                printf("\t\t ");
            else
                printf("%016x ", (unsigned int)elf->symbols_32[i].st_value);
            printf("%c ", get_type_32(&elf->symbols_32[i], elf->shdr_32));
            printf("%s\n", &elf->str_symbols[elf->symbols_32[i].st_name]);
        }
    }
    return 0;
}

int get_symbols_32(elf_data_t *elf)
{
    bool sym_found = false;

    for (int i = 0; i < elf->ehdr_32->e_shnum; i++)
    {
        if (elf->shdr_32[i].sh_type == SHT_SYMTAB)
        {
            elf->str_symbols = (unsigned char *)elf->data +
            elf->shdr_32[elf->shdr_32[i].sh_link].sh_offset;
            elf->symbols_size = elf->shdr_32[i].sh_size
            / elf->shdr_32[i].sh_entsize;
            elf->symbols_32 = (Elf32_Sym *)((char *)elf->ehdr_32 +
                                            elf->shdr_32[i].sh_offset);
            sym_found = true;
            i = elf->ehdr_32->e_shnum;
        }
    }
    if (sym_found == true)
        return print_symbols_32(elf);
    return 84;
}