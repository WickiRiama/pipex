# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 16:56:48 by mriant            #+#    #+#              #
#    Updated: 2022/03/21 17:02:48 by mriant           ###   ########.fr        #
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
