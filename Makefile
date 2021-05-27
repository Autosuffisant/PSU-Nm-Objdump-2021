##
## EPITECH PROJECT, 2021
## nm
## File description:
## Makefile
##

NMDIR = ./nm
OBJDUMPDIR = ./objdump

all: nm objdump

nm:
		@make -C $(NMDIR) -f Makefile

objdump:
		@make -C $(OBJDUMPDIR) -f Makefile

clean:
		@make clean -C $(NMDIR) -f Makefile
		@make clean -C $(OBJDUMPDIR) -f Makefile
fclean:
		@make fclean -C $(NMDIR) -f Makefile
		@make fclean -C $(OBJDUMPDIR) -f Makefile
		rm -rf my_objdump
		rm -rf my_nm

re:
		@make re -C $(NMDIR) -f Makefile
		@make re -C $(OBJDUMPDIR) -f Makefile

.PHONY:all nm objdump clean fclean nmmess objdumpmess
