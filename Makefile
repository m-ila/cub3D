# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/06 14:38:55 by mbruyant          #+#    #+#              #
#    Updated: 2024/04/24 23:05:56 by mbruyant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 -g
MLXFLAGS = minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -lX11 -lXext
SOURCES = srcs/p_map.c srcs/bool_is.c srcs/main.c srcs/errors.c srcs/i_data.c \
srcs/i_null.c srcs/free.c srcs/i_color.c srcs/i_map.c
OBJS = ${SOURCES:.c=.o}
INC = inc/
LIBFT = libft/
LIBFTHD = libft/libft.h
MLX = minilibx-linux

all: ${NAME}

${NAME}: ${OBJS} ${INC} ${SOURCES} ${LIBFT} ${MLX}
	${MAKE} -C minilibx-linux
	${MAKE} -C libft/
	${CC} ${CFLAGS} ${SOURCES} -o ${NAME} -I ${INC} -include ${LIBFTHD} ${MLXFLAGS} libft/libft.a

clean :
	${MAKE} -C minilibx-linux clean
	${MAKE} -C libft/ clean
	${RM} ${OBJS}
	@echo "\033[0;31;1mClean OK\033[0m"

fclean : clean
	${MAKE} -C libft/ fclean
	${RM} ${NAME}
	@echo "\033[0;31;1mfclean OK\033[0m"

re : fclean all

.PHONY : all fclean clean re