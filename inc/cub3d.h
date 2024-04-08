/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:07:33 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/08 17:10:20 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
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

typedef enum path_txt
{
	NO,
	SO,
	WE,
	EA
};

typedef struct s_data
{
	t_map	*map;
	t_point	*position;
	char	path_texture[4];
	char	floor_c;
	char	ceiling_c;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

#endif