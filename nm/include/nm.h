/*
** EPITECH PROJECT, 2021
** nm
** File description:
** Recreated the nm function
*/

#ifndef MY_NM
#define MY_NM

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>

typedef struct elf_data_s {
    Elf64_Ehdr *ehdr_64;
    Elf64_Shdr *shdr_64;
    Elf64_Sym *symbols_64;

    Elf32_Ehdr *ehdr_32;
    Elf32_Shdr *shdr_32;
    Elf32_Sym *symbols_32;

    void *data;
    unsigned char *str_symbols;
    int long symbols_size;

    int return_value;
    bool file_default;
    int file_nbr;
    char *file_path;
    long file_size;
    int fd;
} elf_data_t;

int file_get_content_64(elf_data_t *elf);
int get_symbols_64(elf_data_t *elf);
char get_type_64(Elf64_Sym *sym, Elf64_Shdr *shdr);

int file_get_content_32(elf_data_t *elf);
int get_symbols_32(elf_data_t *elf);
char get_type_32(Elf32_Sym *sym, Elf32_Shdr *shdr);


#endif /* !MY_NM */
