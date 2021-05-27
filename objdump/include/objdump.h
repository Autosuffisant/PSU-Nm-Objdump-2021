/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** recreate the objdump function
*/

#ifndef MY_OBJDUMP_
#define MY_OBJDUMP_

#include "flags.h"
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
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

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

int file_get_content(elf_data_t *elf);
int	address_size(long int addr);
int	print_ascii(unsigned int j, unsigned int z, unsigned char *w, char *t);

int	check_section_64(Elf64_Shdr *shdr, int i);
int	check_section_32(Elf32_Shdr *shdr, int i);

void print_flags_64(elf_data_t *elf);
void print_flags_32(elf_data_t *elf);

uint32_t get_flag_64(elf_data_t *elf);
uint32_t get_flag_32(elf_data_t *elf);

void print_objdump_64(elf_data_t *elf);
void print_objdump_32(elf_data_t *elf);

#endif /* !MY_OBJDUMP_ */
