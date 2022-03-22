# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 16:56:48 by mriant            #+#    #+#              #
#    Updated: 2022/03/22 17:14:34 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = ${addprefix srcs/, \
	main.c}

OBJS = ${patsubst srcs/%.c, build/%.o, ${SRCS}}

DEPS = ${patsubst srcs/%.c, build/%.d, ${SRCS}}

LIBFT = libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I./includes -I./libft
LFLAGS = -L./libft -lft

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

${LIBFT}:
	make -C libft

build/%.o: srcs/%.c
	mkdir -p build
	${CC} ${CFLAGS} -c $< -o $@ ${IFLAGS}

.PHONY: all
all: ${NAME}

.PHONY: clean
clean:
	rm -rf ${OBJS}
	rm -rf ${DEPS}
	rm -rf build
	make -C libft clean

.PHONY: fclean
fclean: clean
	rm -rf ${NAME}
	make -C libft fclean

.PHONY: re
re: fclean all

-include ${DEPS}