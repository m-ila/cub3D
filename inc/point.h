/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:35 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/03 12:34:44 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include "cub3d.h"

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

#endif