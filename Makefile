NAME	=	minishell
CC		=	cc
CFLAGS	=	#-Wall -Werror -Wextra
SRC		=	main.c ft_lst.c

OBJ = $(patsubst %.c,%.o,$(SRC))
INCLUDES = minishell.h
DIR_LIB = libft
LIB = $(DIR_LIB)/libft.a

all : lib $(NAME)

lib : 
	make -C $(DIR_LIB)

$(NAME) : $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -ltermcap -lreadline

%.o : %.c $(INCLUDES)
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)
	make -C $(DIR_LIB) clean

fclean : clean
	rm -f $(NAME)
	make -C $(DIR_LIB) fclean
	
re : fclean all

.PHONY : all clean fclean re