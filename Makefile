# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/06 14:38:55 by mbruyant          #+#    #+#              #
#    Updated: 2024/05/28 21:04:08 by mbruyant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
MANDATORY_FILES = mandatory/srcs/game/bool.c \
mandatory/srcs/game/game_coord_hor.c \
mandatory/srcs/game/game_init.c \
mandatory/srcs/game/game_multi_ray.c \
mandatory/srcs/game/game_which_texture.c \
mandatory/srcs/game/game_angle.c \
mandatory/srcs/game/game_coord_ver.c \
mandatory/srcs/game/game_init_img.c \
mandatory/srcs/game/game_ray_math.c \
mandatory/srcs/game/render_maps.c \
mandatory/srcs/game/game_angle_math.c \
mandatory/srcs/game/game_input.c \
mandatory/srcs/game/game_seg.c \
mandatory/srcs/game/game.c \
mandatory/srcs/game/game_hor_or_vert.c \
mandatory/srcs/game/game_moves.c \
mandatory/srcs/game/game_which_pixel.c \
mandatory/srcs/parsing/bool_is.c \
mandatory/srcs/parsing/emb_free.c \
mandatory/srcs/parsing/free.c \
mandatory/srcs/parsing/i_data.c \
mandatory/srcs/parsing/i_null.c \
mandatory/srcs/parsing/p_file.c \
mandatory/srcs/parsing/p_map_find.c \
mandatory/srcs/parsing/debug_utils.c \
mandatory/srcs/parsing/errors.c \
mandatory/srcs/parsing/i_color.c \
mandatory/srcs/parsing/i_map.c \
mandatory/srcs/parsing/p_map.c \
mandatory/srcs/parsing/main.c \
mandatory/srcs/parsing/str_manip.c \
mandatory/inc/cub3d.h \
mandatory/inc/def_mlx.h \
mandatory/inc/point.h \
mandatory/libft

all: $(NAME)

${NAME}: ${MANDATORY_FILES}
	${MAKE} -C mandatory/
	mv mandatory/cub3D .

clean :
	${MAKE} -C mandatory/ clean
	${MAKE} -C bonus/ clean

fclean : clean
	${MAKE} -C mandatory/ fclean
	${MAKE} -C bonus/ fclean
	rm -rf cub3D_bonus cub3D

re : fclean all

bonus :
	${MAKE} -C bonus/
	mv bonus/cub3D_bonus .

leaks: all
	valgrind -s --track-fds=yes --track-origins=yes \
	--leak-check=full --show-leak-kinds=all ./cub3D

.PHONY : all fclean clean re bonus
