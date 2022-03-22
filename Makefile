# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 16:56:48 by mriant            #+#    #+#              #
#    Updated: 2022/03/22 10:07:38 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = ${addprefix srcs/, \
	main.c}

OBJS = ${patsubst srcs/%.c, build/%.o, ${SRCS}}

DEPS = ${patsubst srcs/%.c, build/%.d, ${SRCS}}

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I./includes

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

build/%.o: srcs/%.c
	mkdir -p build
	${CC} ${CFLAGS} -c $< -o $@ ${IFLAGS}

all: ${NAME}

clean:
	rm -rf ${OBJS}
	rm -rf ${DEPS}
	rm -rf build

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re

-include ${DEPS}