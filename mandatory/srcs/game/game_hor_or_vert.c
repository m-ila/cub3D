/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hor_or_vert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:56:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 11:55:45 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	ft_pos_y_inc(t_point_d pos, t_point_d d, double angle)
{
	if (ft_facing_up(angle))
		return (pos.y - d.y);
	return (pos.y + d.y);
}

double	ft_pos_x_inc(t_point_d pos, t_point_d d, double angle)
{
	if (!ft_pointing_left(angle))
		return (pos.x + d.x);
	return (pos.x - d.x);
}

double	ft_vrt_intersections(t_data *cub, t_segment *seg)
{
	t_point_d	d;
	t_point_d	pos;
	t_point		map;

	if (seg->angle == 90.0 || seg->angle == 270.0)
		return (DBL_MAX);
	d.x = TILE_SIZE;
	d.y = ft_get_dy_vrt(seg->angle);
	pos.x = ft_get_x_vrt(seg->from, seg->angle);
	pos.y = ft_get_y_vrt(seg->from, pos, seg->angle);
	map.x = (int) floor(pos.x / TILE_SIZE);
	map.y = (int) floor(pos.y / TILE_SIZE);
	while (map.y > 0 && map.x > 0 && \
	map.y < (int) cub->map->y_size_max && map.x < (int) cub->map->x_size_max)
	{
		if (ft_is_within_map_bounds(cub, map) && \
		cub->map->raw_map[map.y][map.x] == '1')
			return (ft_len_ray(seg->from, pos));
		pos.x = ft_pos_x_inc(pos, d, seg->angle);
		pos.y = ft_pos_y_inc(pos, d, seg->angle);
		map.x = (int) floor(pos.x / TILE_SIZE);
		map.y = (int) floor(pos.y / TILE_SIZE);
	}
	return (ft_len_ray(seg->from, pos));
}

double	ft_hzt_intersections(t_data *cub, t_segment *seg)
{
	t_point_d	d;
	t_point_d	pos;
	t_point		map;

	if (seg->angle == 0.0 || seg->angle == 180.0 || seg->angle == 360.0)
		return (DBL_MAX);
	d.y = TILE_SIZE;
	d.x = ft_get_dx_hrz(seg->angle);
	pos.y = ft_get_y_hrz(seg->from, seg->angle);
	pos.x = ft_get_x_hrz(seg->from, pos, seg->angle);
	map.x = (int) floor(pos.x / TILE_SIZE);
	map.y = (int) floor(pos.y / TILE_SIZE);
	while (map.y > 0 && map.x > 0 && \
	map.y < (int) cub->map->y_size_max && map.x < (int) cub->map->x_size_max)
	{
		if (ft_is_within_map_bounds(cub, map) && \
		cub->map->raw_map[map.y][map.x] == '1')
			return (ft_len_ray(seg->from, pos));
		pos.x = ft_pos_x_inc(pos, d, seg->angle);
		pos.y = ft_pos_y_inc(pos, d, seg->angle);
		map.x = (int) floor(pos.x / TILE_SIZE);
		map.y = (int) floor(pos.y / TILE_SIZE);
	}
	return (ft_len_ray(seg->from, pos));
}
