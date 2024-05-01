# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/06 14:38:55 by mbruyant          #+#    #+#              #
#    Updated: 2024/05/01 18:04:26 by yuewang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 -g
INCFLAGS  = -I inc/ -I src/libft/ -I/usr/include/readline
MLXFLAGS = minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -lX11 -lXext
SRC_DIR    = srcs/
#wildcard to be changed to sources filenames
SRC_FILES = $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)game/*.c)
# SRC_FILES  = srcs/p_map.c srcs/bool_is.c srcs/main.c srcs/errors.c srcs/i_data.c \
# srcs/i_null.c srcs/free.c srcs/i_color.c srcs/i_map.c srcs/p_map_find.c \
# srcs/debug_utils.c srcs/str_manip.c
INC = inc/
LIBFT = libft/
LIBFTHD = libft/libft.h
MLX = minilibx-linux
OBJ_DIR    = objs/
OBJS 	   = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: ${NAME}

${NAME}: ${OBJS} ${INC} ${SRC_FILES} ${LIBFT} ${MLX}
	${MAKE} -C minilibx-linux
	${MAKE} -C libft/
	${CC} ${CFLAGS} ${SRC_FILES} -o ${NAME} -I ${INC} -include ${LIBFTHD} ${MLXFLAGS} libft/libft.a

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(INCFLAGS) -c $< -o $@

clean :
	${MAKE} -C minilibx-linux clean
	${MAKE} -C libft/ clean
	${RM} ${OBJS}
	@echo "\033[0;31;1mClean OK\033[0m"

fclean : clean
	${MAKE} -C libft/ fclean
	${RM} ${NAME}
	$(RM) -r $(OBJ_DIR)
	@echo "\033[0;31;1mfclean OK\033[0m"

re : fclean all

leaks: all
	valgrind -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./cub3d

.PHONY : all fclean clean re