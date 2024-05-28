# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/06 14:38:55 by mbruyant          #+#    #+#              #
#    Updated: 2024/05/28 21:03:52 by mbruyant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 -g
INCFLAGS  = -I inc/
MLXFLAGS = ../minilibx-linux/libmlx.a ../minilibx-linux/libmlx_Linux.a \
-lX11 -lXext -lm
SRC_DIR = srcs/
SRC_FILES = srcs/game/bool.c \
srcs/game/game_coord_hor.c \
srcs/game/game_init.c \
srcs/game/game_multi_ray.c \
srcs/game/game_which_texture.c \
srcs/game/game_angle.c \
srcs/game/game_coord_ver.c \
srcs/game/game_init_img.c \
srcs/game/game_ray_math.c \
srcs/game/render_maps.c \
srcs/game/game_angle_math.c \
srcs/game/game_input.c \
srcs/game/game_seg.c \
srcs/game/render_minimap.c \
srcs/game/game.c \
srcs/game/game_hor_or_vert.c \
srcs/game/game_moves.c \
srcs/game/game_which_pixel.c \
srcs/parsing/bool_is.c \
srcs/parsing/emb_free.c \
srcs/parsing/free.c \
srcs/parsing/i_data.c \
srcs/parsing/i_null.c \
srcs/parsing/p_file.c \
srcs/parsing/p_map_find.c \
srcs/parsing/debug_utils.c \
srcs/parsing/errors.c \
srcs/parsing/i_color.c \
srcs/parsing/i_map.c \
srcs/parsing/p_map.c \
srcs/parsing/main.c \
srcs/parsing/str_manip.c

INC = inc/
LIBFT = libft/
LIBFTHD = libft/libft.h
MLX = ../minilibx-linux
OBJ_DIR    = objs/
OBJS 	   = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

${NAME}: ${OBJS} ${INC} ${SRC_FILES} ${LIBFT} ${MLX}
	${MAKE} -C ../minilibx-linux
	${MAKE} -C libft/
	${CC} ${CFLAGS} ${SRC_FILES} -o ${NAME} -I ${INC} -include \
	${LIBFTHD} ${MLXFLAGS} libft/libft.a

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(INCFLAGS) -c $< -o $@

clean :
	${MAKE} -C ../minilibx-linux clean
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
	valgrind -s --track-fds=yes --track-origins=yes \
	--leak-check=full --show-leak-kinds=all ./cub3d

.PHONY : all fclean clean re
