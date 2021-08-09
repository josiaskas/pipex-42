# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/05 16:57:50 by jkasongo          #+#    #+#              #
#    Updated: 2021/08/09 15:49:00 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
TEST_NAME = prog
CC = gcc
CFLAGS = -Wall -Wextra -Werror

#source
SRCS =	main.c pipex.c utils.c
SRCS_TEST1 =	prog_test1.c
SRCS_TEST2 =	prog_test2.c

OBJS= $(SRCS:%.c=%.o)
OBJS_TEST1= $(SRCS_TEST1:%.c=%.o)
OBJS_TEST2= $(SRCS_TEST2:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) re -C ./libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft -lft
	@echo "pipex builded"

test: $(OBJS_TEST1) $(OBJS_TEST2)
	@$(CC) $(CFLAGS) $(OBJS_TEST1) -o $(TEST_NAME)1
	@echo "test prog1 builded"
	@$(CC) $(CFLAGS) $(OBJS_TEST2) -o $(TEST_NAME)2
	@echo "test prog2 builded"

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_TEST1)
	@rm -f $(OBJS_TEST2)

fclean: 	clean
	@rm -f $(NAME)
	@rm -f $(TEST_NAME) $(TEST_NAME2)

re: fclean all

.PHONY:		all clean fclean re

