/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:07:33 by mbruyant          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/01 17:27:34 by mbruyant         ###   ########.fr       */
=======
/*   Updated: 2024/05/01 16:13:22 by yuewang          ###   ########.fr       */
>>>>>>> yuewang
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
# define E_PATH "usage : (ID) (VALUE) and nothing else"

typedef enum path_txt
{
	NO,
	SO,
	WE,
	EA,
	ERR
}	t_path_txt;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_data
{
	t_map	*map;
	t_point	*position;
	char	*path_texture[5];
	t_rgb	floor_c;
	t_rgb	ceiling_c;
	void	*mlx_ptr;
	void	*win_ptr;
	int		tmp_fd;
	char	*tmp_line;
	bool	end;
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
void	ft_add_line_to_arr(char ***arr, char **line);
/* ft_game.c */
void ft_game(t_data *cub);




#endif