/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** recreate the objdump function
*/

#include "objdump.h"

int	address_size(long int addr)
{
    long int i = 1;
    int	size = 0;

    while (i < addr || size < 4) {
        i *= 16;
        size += 1;
    }
    return size;
}

int	print_ascii(unsigned int j, unsigned int z, unsigned char *w, char *t)
{
    for (unsigned int x = j; x % 16; x++) {
        if (!(x % 4) && x % 16)
            printf("   ");
        else
            printf("  ");
    }
    printf("  ");
    for (; z < j; z++) {
        if (isprint(w[z]))
            printf("%c", t[z]);
        else
            printf(".");
    }
    for (; z % 16 != 0; z++)
        printf(" ");
    printf("\n");
    return j;
}

void print_section_64(elf_data_t *elf, char *str_sections, int i)
{
    int address = elf->shdr_64[i].sh_addr;
    unsigned char *w = (unsigned char *)((char *)elf->ehdr_64
    + elf->shdr_64[i].sh_offset);
    unsigned int z = 0;

    printf("Contents of section %s:\n", &str_sections[elf->shdr_64[i].sh_name]);
    for (unsigned int j = 0; j < elf->shdr_64[i].sh_size;) {
        if (j % 16 == 0)
            printf(" %0*x ", address_size((long int)(elf->shdr_64[i].sh_addr*
            + elf->shdr_64[i].sh_size)), address);
        printf("%02x", w[j++]);
        if (j % 4 == 0 && j % 16 && j < elf->shdr_64[i].sh_size)
            printf(" ");
        if (j % 16 == 0)
            address += 16;
        if (j % 16 == 0 || j >= elf->shdr_64[i].sh_size)
            z = print_ascii(j, z, w, (char *)w);
    }
}

void sections_64(elf_data_t *elf, char *str_sections)
{
    for (int i = 0; i < elf->ehdr_64->e_shnum; i++)
        if (check_section_64(elf->shdr_64, i))
            print_section_64(elf, str_sections, i);
}

void print_objdump_64(elf_data_t *elf)
{
    char *str_sections = (char *)((char *)elf->data
    + elf->shdr_64[elf->ehdr_64->e_shstrndx].sh_offset);

    printf("architecture: i386:x86-64, flags 0x%.8x:\n", get_flag_64(elf));
    print_flags_64(elf);
    printf("start address 0x%016x\n\n", (int)elf->ehdr_64->e_entry);
    sections_64(elf, str_sections);
}