# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 16:56:48 by mriant            #+#    #+#              #
#    Updated: 2022/04/07 09:45:30 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONUS_NAME = pipex_bonus

SRCS = ${addprefix srcs/, \
	main.c \
	parsing.c \
	utils.c}
BONUS_SRCS = ${addprefix srcs/, \
	main_bonus.c \
	parsing_bonus.c \
	utils_bonus.c}
GNL_SRCS = ${addprefix Get_next_line/, \
	get_next_line.c \
	get_next_line_utils.c}

OBJS = ${patsubst srcs/%.c, build/%.o, ${SRCS}}
BONUS_OBJS = ${patsubst srcs/%.c, build/%.o, ${BONUS_SRCS}}
GNL_OBJS = ${patsubst Get_next_line/%.c, build/%.o, ${GNL_SRCS}}

DEPS = ${patsubst srcs/%.c, build/%.d, ${SRCS}}
BONUS_DEPS = ${patsubst srcs/%.c, build/%.d, ${BONUS_SRCS}}
GNL_DEPS = ${patsubst Get_next_line/%.c, build/%.d, ${GNL_SRCS}}

LIBFT = libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -MMD
IFLAGS = -I./includes -I./libft -I./Get_next_line
LFLAGS = -L./libft -lft

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

${LIBFT}:
	make -C libft

${BONUS_NAME}: ${LIBFT} ${BONUS_OBJS} ${GNL_OBJS}
	${CC} ${CFLAGS} ${BONUS_OBJS} ${GNL_OBJS} -o ${BONUS_NAME} ${LFLAGS}

build/%.o: srcs/%.c
	mkdir -p build
	${CC} ${CFLAGS} -c $< -o $@ ${IFLAGS}
build/%.o: Get_next_line/%.c
	mkdir -p build
	${CC} ${CFLAGS} -c $< -o $@ ${IFLAGS}

.PHONY: bonus
bonus: ${BONUS_NAME}

.PHONY: all
all: ${NAME} bonus

.PHONY: clean
clean:
	rm -rf ${OBJS} ${BONUS_OBJS} ${GNL_OBJS}
	rm -rf ${DEPS} ${BONUS_DEPS} ${GNL_DEPS}
	rm -rf build
	make -C libft clean

.PHONY: fclean
fclean: clean
	rm -rf ${NAME} ${BONUS_NAME}
	make -C libft fclean

.PHONY: re
re: fclean ${NAME}

.PHONY: re_bonus
re_bonus: fclean ${BONUS_NAME}

.PHONY: re_all
re_all: fclean all

-include ${DEPS} ${BONUS_DEPS} ${GNL_DEPS}
