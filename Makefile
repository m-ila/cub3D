# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/06 14:38:55 by mbruyant          #+#    #+#              #
#    Updated: 2024/04/08 13:10:54 by mbruyant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 -g
MLXFLAGS = minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -lX11 -lXext
SOURCES = srcs/p_map.c
OBJS = ${SOURCES:.c=.o}
INC = inc/
LIBFT = libft/

all: ${NAME}

${NAME}: ${OBJS} ${INC} ${SOURCES} ${LIBFT}
	${MAKE} -C libft/
	${CC} ${CFLAGS} ${SOURCES} -o ${NAME} -I ${INC} ${MLXFLAGS} 

clean :
	${RM} ${OBJS}
	@echo "\033[0;31;1mClean OK\033[0m"

fclean : clean
	${RM} ${NAME}
	@echo "\033[0;31;1mfclean OK\033[0m"

re : fclean all

.PHONY : all fclean clean re