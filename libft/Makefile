# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 23:13:38 by hvayon            #+#    #+#              #
#    Updated: 2022/03/06 14:52:48 by sazelda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER			= libft.h
NAMES			= ft_memset.c ft_bzero.c ft_memcpy.c\
					ft_memmove.c ft_memchr.c\
				  ft_memcmp.c ft_strlen.c ft_isalpha.c\
				  ft_isdigit.c ft_isalnum.c ft_isascii.c\
				  ft_isprint.c ft_toupper.c ft_tolower.c\
					ft_strchr.c ft_strrchr.c ft_strncmp.c\
				   	ft_strlcpy.c ft_strlcat.c ft_strnstr.c\
				   	ft_atoi.c ft_calloc.c ft_strdup.c\
					ft_substr.c ft_strjoin.c ft_split.c\
					ft_itoa.c ft_strmapi.c ft_putchar_fd.c\
					ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
					ft_strtrim.c ft_strtrim.c ft_striteri.c\

BONUS_NAMES		= 	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			 		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\

OBJS			= $(NAMES:.c=.o)
BONUS_OBJS		= $(BONUS_NAMES:.c=.o)

CC				= gcc
CFLAGS			= #-Wall -Wextra -Werror
NAME			= libft.a


.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) ${HEADER} Makefile
	ar rcs $(NAME) $(OBJS)

bonus:	$(OBJS) $(BONUS_OBJS) ${HEADER} Makefile
		@make "OBJS = $(BONUS_OBJS)" all

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus
