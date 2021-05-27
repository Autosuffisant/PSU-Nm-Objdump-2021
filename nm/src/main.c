/*
** EPITECH PROJECT, 2021
** nm
** File description:
** Reproduce the nm function
*/

#include "nm.h"

int nm_32(elf_data_t *elf)
{
    elf->ehdr_32 = (Elf32_Ehdr*)elf->data;
    elf->shdr_32 = (Elf32_Shdr *)((char *)elf->data + elf->ehdr_32->e_shoff);
    get_symbols_32(elf);
    return 0;
}

int nm_64(elf_data_t *elf)
{
    elf->shdr_64 = (Elf64_Shdr *)((char *)elf->data + elf->ehdr_64->e_shoff);
    get_symbols_64(elf);
    return 0;
}

int nm(elf_data_t *elf, int ac)
{
    elf->file_nbr = ac - 1;
    if (file_get_content_64(elf)) {
        elf->return_value++;
        return 0;
    }
    elf->ehdr_64 = (Elf64_Ehdr*)elf->data;
    if (elf->ehdr_64->e_ident[EI_CLASS] == ELFCLASS64) {
        return nm_64(elf);
    } else {
        return nm_32(elf);
    }
}

int argument_handling(int ac, char **av)
{
    elf_data_t elf;
    elf.return_value = 0;
    elf.file_default = false;

    if (ac == 1) {
        elf.file_default = true;
        ac = 2;
    }
    for (int i = 1; i < ac; i++) {
        if (elf.file_default == true)
            elf.file_path = strdup("a.out");
        else
            elf.file_path = av[i];
        if (nm(&elf, ac) == 84)
            return 84;
    }
    return elf.return_value;
}

int main(int ac, char **av)
{
    return argument_handling(ac, av);
}