# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/06 02:21:09 by jkasongo          #+#    #+#              #
#    Updated: 2021/05/28 13:46:02 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Librairie personnel pour les projets en C
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

#source
SRCS =	ft_memset.c ft_bzero.c ft_memcpy.c\
		ft_memccpy.c ft_memmove.c ft_memchr.c\
		ft_memcmp.c ft_strlen.c ft_isalpha.c\
		ft_isdigit.c ft_isalnum.c ft_isascii.c\
		ft_isprint.c ft_toupper.c ft_tolower.c\
		ft_strchr.c ft_strrchr.c ft_strncmp.c\
		ft_strlcpy.c ft_strlcat.c ft_strnstr.c\
		ft_strrev.c \
		ft_atoi.c ft_calloc.c ft_strdup.c\
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c\
		ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_strndup.c ft_isspace.c\
		 ft_lstadd_back.c ft_lstclear.c ft_lstlast.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstdelone.c \
		ft_lstiter.c ft_lstmap.c ft_lstsize.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(SRCS)
	@ar rc $(NAME) $(OBJS)
	@echo "libft.a builded"

clean:
	@rm -f $(OBJS)

fclean: 	clean
	@rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re
