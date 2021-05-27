/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** recreate the objdump function
*/

#include "objdump.h"

void print_section_32(elf_data_t *elf, char *str_sections, int i)
{
    int address = elf->shdr_32[i].sh_addr;
    unsigned char *w = (unsigned char *)((char *)elf->ehdr_32
    + elf->shdr_32[i].sh_offset);
    unsigned int z = 0;

    printf("Contents of section %s:\n", &str_sections[elf->shdr_32[i].sh_name]);
    for (unsigned int j = 0; j < elf->shdr_32[i].sh_size;) {
        if (j % 16 == 0)
            printf(" %0*x ", address_size((long int)(elf->shdr_32[i].sh_addr
            + elf->shdr_32[i].sh_size)), address);
        printf("%02x", w[j++]);
        if (j % 4 == 0 && j % 16 && j < elf->shdr_32[i].sh_size)
            printf(" ");
        if (j % 16 == 0)
            address += 16;
        if (j % 16 == 0 || j >= elf->shdr_32[i].sh_size)
            z = print_ascii(j, z, w, (char *)w);
    }
}

void sections_32(elf_data_t *elf, char *str_sections)
{
    for (int i = 0; i < elf->ehdr_32->e_shnum; i++)
        if (check_section_32(elf->shdr_32, i))
            print_section_32(elf, str_sections, i);
}

void print_objdump_32(elf_data_t *elf)
{
    char *str_sections = (char *)((char *)elf->data
    + elf->shdr_32[elf->ehdr_32->e_shstrndx].sh_offset);

    printf("architecture: i386:x86-32, flags 0x%.8x:\n", get_flag_32(elf));
    print_flags_32(elf);
    printf("start address 0x%016x\n\n", (int)elf->ehdr_32->e_entry);
    sections_32(elf, str_sections);
}