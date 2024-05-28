/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:48:33 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 13:31:04 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	ft_is_within_map_bounds(t_data *cub, t_point coord)
{
	return (coord.x >= 0 && coord.y >= 0 && \
	coord.x < (int) cub->map->x_size_max \
	&& coord.y < (int) cub->map->y_size_max && \
	coord.x < (int) ft_strlen(cub->map->raw_map[coord.y]));
}

bool	ft_facing_up(double angle)
{
	return (angle > 0.0 && angle < 180.0);
}

bool	ft_pointing_left(double angle)
{
	return (angle > 90.0 && angle < 270.0);
}

bool	ft_player_is_in_wall(t_data *cub, t_segment *seg)
{
	t_point	pt;

	pt.y = (int) seg->from.y / TILE_SIZE;
	pt.x = (int)seg->from.x / TILE_SIZE;
	return (cub->map->raw_map[pt.y][pt.x] == '1');
}
