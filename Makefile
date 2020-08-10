##
## EPITECH PROJECT, 2020
## PSU_2019_malloc
## File description:
## Makefile
##

SRCL	=	src/malloc.c	\
			src/realloc.c	\

OBJL	=	malloc.o		\
			realloc.o 		\

LIB = libmy_malloc.so

all: $(LIB)

$(LIB):
	gcc -c -Wall -Wextra -fpic $(SRCL)
	gcc -shared -o $(LIB) $(OBJL)

clean:
	rm -f $(OBJL)

fclean: clean
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re