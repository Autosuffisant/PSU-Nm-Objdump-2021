##
## EPITECH PROJECT, 2021
## nm
## File description:
## Makefile
##

NAME	=	my_nm

CC	=	gcc

RM	=	rm -f

SRCS	:=	$(shell find src/ -name *.c)

OBJS	=	$(SRCS:.c=.o)

IDIR	=	./include/

CFLAGS	=	-Wall -Wextra -Werror -I$(IDIR)

LDFLAGS	=	\

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LDFLAGS)
	mv $(NAME) ../

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re