/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:07:33 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/23 15:52:09 by mbruyant         ###   ########.fr       */
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

# define ALLOWED_BASE "01NSEW"
# define B_DIGIT "0123456789"

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
}	t_data;

/* srcs/errors.c */
int		ft_err_ret(char *msg, char *name, int ret);

/* srcs/i_data.c */
/*check if str is NO/SO/WE/EA/C/F */
bool	ft_is_valid_file_component(char *str);
bool	ft_open_file(t_data *cub, char *path_file);
void	ft_close_fd(int *fd);
bool	ft_init_struct(t_data *cub, char *path_file);
/* srcs/i_null.c */
void	ft_init_null(t_data *cub);
void	ft_array_set_null(char **arr, size_t len);

#endif