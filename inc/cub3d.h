/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:07:33 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/09 12:12:30 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* read, write */
# include <unistd.h>
/* exit, malloc, free */
# include <stdlib.h>
/* open, close */
# include <fcntl.h>
/* strerror */
# include <string.h>
/* printf, perror */
# include <stdio.h>
/* math.h */
# include <math.h>
# include <float.h>
# include "point.h"
# include "def_mlx.h"
# include "../libft/libft.h"

/* minilibx */
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define ALLOWED_BASE "01NSEW\t\b\v\f "
# define B_SPAWN "NSEW"
# define B_FIRSTLINE " 01\n\t\b\v\f"
# define B_DIGIT "0123456789"
# define B_WHITESPACE "\t\b\v\f "
# define B_WHTZEUN "\t\b\v\f 01"
# define B_WALL "\t\b\v\f 1"
# define E_PATH "usage : (ID) (VALUE) and nothing else"
# define PI 3.14159265359
# define C_BLACK 0x000000
# define C_RED 0xFF0000
# define C_YELLOW 0xFFD500
# define C_WHITE 0xF5F5F5
# define C_GREY 0xAAAAAA
# define INCR_DEG 5.0
# define INCR_STEP 5
# define TILE_SIZE 65

typedef enum compass
{
	NO,
	SO,
	WE,
	EA,
	ERR
}	t_compass;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_data
{
	t_map	*map;
	t_point	position;
	double	angle;
	char	*path_texture[5];
	t_rgb	floor_c;
	t_rgb	ceiling_c;
	void	*mlx_ptr;
	void	*win_ptr;
	int		tmp_fd;
	char	*tmp_line;
	bool	end;
	t_segment	*seg;
}	t_data;

/* srcs/bool_is.c */
bool	ft_is_valid_file_component(char *str);
bool	ft_is_text(char *str);
bool	ft_is_color(char *str);
int		ft_bool_endline(char c);
/* srcs/debug_utils.c */
void	ft_display_2d(char **arr);
/* srcs/errors.c */
int		ft_err_ret(char *msg, char *name, int ret);
/* srcs/free.c */
void	ft_safe_free(char **str);
void	ft_free_textures(t_data *cub);
void	ft_free_map(t_map *m);
/* srcs/i_color.c */
bool	ft_color_range(char **arr);
bool	ft_process_color(t_data *cub, char **arr);
/* srcs/i_data.c */
/*check if str is NO/SO/WE/EA/C/F */
bool	ft_is_valid_file_component(char *str);
bool	ft_open_file(t_data *cub, char *path_file);
void	ft_close_fd(int *fd);
bool	ft_init_struct(t_data *cub, char *path_file);
/* srcs/i_map.c */
bool	ft_start_map_condition(char *str);
bool	ft_get_data_map(t_map *m);
/* srcs/i_null.c */
void	ft_init_null(t_data *cub);
void	ft_array_set_null(char **arr, size_t len);
/* srcs/p_map_find.c */
int		ft_find_end_line(char *str);
int		ft_find_start_line(char *str);
/* srcs/p_map.c */
void	ft_flood_fill(t_point *position, t_map *map);
bool	ft_parse_flood_fill(t_map *map);
/* srcs/str_manip.c */
bool	ft_add_line_to_arr(char ***arr, char **line);
/* srcs/game/game_angle_math.c */
double	ft_deg_to_rad(double deg);
/* srcs/game/game_angle.c */
void	ft_handle_angle(t_data *cub, int keycode);
void	ft_draw_angle(t_data *cub, t_point *pos, double angle, int color);
void	ft_get_starting_angle(t_data *cub);
t_compass	ft_get_which_wall(double angle);
/* srcs/game/game_init.c */
void	ft_game(t_data *cub);
void	ft_draw_angle(t_data *cub, t_point *pos, double angle, int color);
int		key_hook(int keycode, void *param);
/* srcs/game/game_input.c */
int		ft_handle_clic(int button, int x, int y, void *param);
/* srcs/games/game_moves.c */
void	ft_up(t_data *cub, t_point *new);
void	ft_down(t_data *cub, t_point *new);
void	ft_left(t_data *cub, t_point *new);
void	ft_right(t_data *cub, t_point *new);
/* srcs/game/game_multi_rays.c */
void	ft_malloc_rays(t_data *cub);
void	ft_free_rays(t_data *cub);
void	ft_print_all_rays(t_data *cub);
/* srcs/games/game_ray_math.c */
t_segment	ft_segment(t_data *cub, double angle);
t_point	ft_find_end_point(t_data *cub, t_point_d *end, double angle);
double	ft_len_ray(t_point start, t_point end);
/* srcs/games/game_ray_math.c */
double	ft_check_horizontal(t_data *cub);
void	ft_seg_refresh(t_data *cub);
/* srcs/games/game_draw.c */
void	ft_draw_angle_seg(t_data *cub, t_segment seg, int color);


#endif