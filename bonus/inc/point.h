/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:35 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 17:08:51 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include "cub3d.h"
# include <stdbool.h>

typedef enum compass
{
	NO,
	SO,
	WE,
	EA,
	ERR
}	t_compass;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_point_d
{
	double	x;
	double	y;
}	t_point_d;

typedef struct s_map
{
	char	**raw_map;
	char	**map_cpy;
	size_t	x_size_max;
	size_t	y_size_max;
	size_t	x_size_playable;
	size_t	y_size_playable;
	size_t	x_from;
	size_t	x_until;
	size_t	y_from;
	size_t	y_until;
	int		spawn_nb;
	char	spawn_angle;
	t_point	spawn;
}	t_map;

typedef struct s_segment
{
	t_point_d	from;
	t_point_d	until;
	t_point		tile_hit;
	double		angle;
	double		hrz_slope;
	double		vrt_slope;
	double		slope_len;
	double		len_processed;
	bool		vertical_hit;
	bool		horizontal_hit;
	t_compass	direction;
	double		wall_height;
	int			top_pix;
	int			bot_pix;
}	t_segment;

#endif