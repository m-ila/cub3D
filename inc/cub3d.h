/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:07:33 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/16 11:38:35 by mbruyant         ###   ########.fr       */
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
#include <stdint.h>  // For uint32_t

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
# define C_BLUE 0x0000FF
# define C_GREEN 0x00FF00
# define C_CYAN 0x00FFFF
# define C_MAGENTA 0xFF00FF
# define C_ORANGE 0xFFA500
# define C_PURPLE 0x800080
# define C_BROWN 0xA52A2A
# define C_PINK 0xFFC0CB
# define C_SILVER 0xC0C0C0
# define C_GOLD 0xFFD700
# define INCR_DEG 5.0
# define INCR_STEP 5
# define TILE_SIZE 65
# define MINI_TILE_SIZE 13
# define W_HEIGHT 400
# define W_WIDTH 720
# define COLUMN_W 4
# define FOV 90

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_data
{
	t_map	*map;
	t_point_d	position;
	double	angle;
	char	*path_texture[5];
	t_rgb	floor_c;
	t_rgb	ceiling_c;
	void	*mlx_ptr;
	void	*win_2d;
	void	*win_3d;
	t_img_mlx	**imgs;
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
int		exit_cleanup(t_data *cub);
void	ft_free_img(t_data *cub);
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
/* srcs/game/bool.c */
bool	ft_is_within_map_bounds(t_data *cub, t_point coord);
bool	ft_facing_up(double angle);
bool	ft_pointing_left(double angle);
/* srcs/game/game_angle_math.c */
double	ft_deg_to_rad(double deg);
double	ft_norm_angle(double angle);
double	ft_abs(double val);
/* srcs/game/game_angle.c */
void	ft_handle_angle(t_data *cub, int keycode);
void	ft_draw_angle(t_data *cub, t_point_d *pos, double angle, int color);
void	ft_get_starting_angle(t_data *cub);
void	ft_get_hor_vert(t_data *cub, t_segment *seg);
/* srcs/game/game_coord_hor.c */
double	ft_get_x_hrz(t_point_d from, t_point_d pos, double angle);
double	ft_get_y_hrz(t_point_d from, double angle);
double	ft_get_dx_hrz(double angle);
/* srcs/game/game_coord_ver.c */
double	ft_get_y_vrt(t_point_d from, t_point_d pos, double angle);
double	ft_get_x_vrt(t_point_d pos, double angle);
double	ft_get_dy_vrt(double angle);
/* srcs/game/game_hor_or_vert.c */
double	ft_hzt_intersections(t_data *cub, t_segment *seg);
double	ft_vrt_intersections(t_data *cub, t_segment *seg);
double	ft_pos_y_inc(t_point_d pos, t_point_d d, double angle);
double	ft_pos_x_inc(t_point_d pos, t_point_d d, double angle);
/* srcs/game/game.c */
void	ft_game(t_data *cub);
/* srcs/game/game_init_img.c */
bool	ft_free_imgs(t_data *cub, int i, bool err);
bool	ft_open_images(t_data *cub);
/* srcs/game/game_init.c */
void	init_mlx(t_data *cub);
void	init_windows(t_data *cub);
void	ft_draw_angle(t_data *cub, t_point_d *pos, double angle, int color);
int		key_hook(int keycode, void *param);

void	render_2d_map(t_data *cub);
void	draw_player(t_data *cub, t_point_d pos, int color);

void	render_3d(t_data *cub);
/* srcs/game/game_input.c */
int		ft_handle_clic(int button, int x, int y, void *param);
/* srcs/games/game_moves.c */
void	ft_up(t_data *cub, t_point_d *new);
void	ft_down(t_data *cub, t_point_d *new);
void	ft_left(t_data *cub, t_point_d *new);
void	ft_right(t_data *cub, t_point_d *new);
/* srcs/game/game_multi_rays.c */
void	ft_malloc_rays(t_data *cub);
void	ft_free_rays(t_data *cub);
void	ft_print_all_rays(t_data *cub);
/* srcs/games/game_ray_math.c */
t_segment	ft_segment(t_data *cub, double angle);
t_point_d	ft_find_end_point(t_data *cub, t_point_d *end, double angle);
double	ft_len_ray(t_point_d start, t_point_d end);
void	ft_seg_refresh(t_data *cub);
/* srcs/games/game_draw.c */
void	ft_draw_angle_seg(t_data *cub, t_segment seg, int color);
/* srcs/game/game_which_pixel.c */
int	ft_get_pixel(t_data *cub, t_segment *seg, int i);
/* srcs/games/game_which_texture.c */
t_compass	ft_get_which_wall(t_segment *seg, double angle, t_point_d until);

// void	ft_draw_angle_deb(t_data *cub, t_segment seg, int color);

#endif