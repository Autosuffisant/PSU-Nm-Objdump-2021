/*
** EPITECH PROJECT, 2021
** nm
** File description:
** Recreate the nm function
*/

#include "nm.h"

int file_get_content_64(elf_data_t *elf)
{
    if ((elf->fd = (open(elf->file_path, O_RDONLY)))
    == -1)
        return fprintf(stderr, "my_nm: '%s': No such file\n", elf->file_path);
    if ((elf->file_size = lseek((elf->fd), 0, SEEK_END))
    == -1) {
        close(elf->fd);
        return fprintf(stderr, "my_nm: '%s': file format not recognized\n",
        elf->file_path);
    }
    elf->data = mmap(NULL, elf->file_size, PROT_READ, MAP_SHARED, elf->fd, 0);
    if (elf->data == MAP_FAILED && elf->file_size > 0) {
        close(elf->fd);
        return fprintf(stderr, "my_nm: '%s': file format not recognized\n",
        elf->file_path);
    }
    if (elf->file_nbr > 1)
        printf("\n%s:\n", elf->file_path);
    return 0;
}