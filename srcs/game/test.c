/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:56:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/14 18:15:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	ft_hzt_intersections(t_data *cub, t_segment *seg)
{
	t_point_d	d;
	t_point_d	pos;
	bool		buff;

	if (seg->angle == 0 || seg->angle == 90 || seg->angle == 180 || \
	seg->angle == 270 || seg->angle == 360)
		return (DBL_MAX);
	d.y = TILE_SIZE;
	d.x = TILE_SIZE / tan(seg->angle);
	buff = 0;
	pos.y = floor(seg->from.y / TILE_SIZE) * TILE_SIZE;
	if (seg->angle > 0 && seg->angle < 180)
		pos.y += TILE_SIZE;
	if (seg->angle > 180 && seg->angle < 360)
	{
		buff = -TILE_SIZE;
	}
	pos.x = seg->from.x + (pos.y - seg->from.y) / tan(seg->angle);
	if (seg->angle > 0 && seg->angle < 180)
		d.y *= -1.0;
	if ((seg->angle > 90 && seg->angle < 270) && d.x > 0.0)
		d.x *= -1.0;
	else if (!(seg->angle > 90 && seg->angle < 270) && d.x < 0.0)
		d.x *= -1.0;
	while ((int)(pos.y) / TILE_SIZE > 0 && (int)(pos.x) / TILE_SIZE > 0 && \
	(int)(pos.y) / TILE_SIZE < (int) cub->map->y_size_max && (int)(pos.x) / TILE_SIZE < (int) cub->map->x_size_max)
	{
		if (cub->map->raw_map[(int)(pos.y + buff) / TILE_SIZE][(int)pos.x / TILE_SIZE] == '1')
			return (ft_len_ray(seg->from, (t_point) {pos.x, pos.y}));
		pos.x += d.x;
		pos.y += d.y;
	}
	return (DBL_MAX);
}

double	ft_vrt_intersections(t_data *cub, t_segment *seg)
{
	t_point_d	d;
	t_point_d	pos;
	bool		buff;

	if (seg->angle == 0 || seg->angle == 90 || seg->angle == 180 || \
	seg->angle == 270 || seg->angle == 360)
		return (DBL_MAX);
	buff = 0;
	pos.x = floor(seg->from.x / TILE_SIZE) * TILE_SIZE;
	if (!(seg->angle > 90 && seg->angle < 270))
	{
		buff = -TILE_SIZE;
		pos.x += TILE_SIZE;
	}
	pos.y = seg->from.y + (pos.x - seg->from.x) * tan(seg->angle);
	d.x = TILE_SIZE;
	if (seg->angle > 90 && seg->angle < 270)
		d.x *= -1.0;
	d.y = TILE_SIZE * tan(seg->angle);
	if ((seg->angle > 0 && seg->angle < 180) && d.y > 0.0)
		d.y *= -1.0;
	else if ((seg->angle > 180 && seg->angle < 360) && d.y < 0.0)
		d.y *= -1.0;
	while ((int)(pos.y) / TILE_SIZE > 0 && (int)(pos.x) / TILE_SIZE > 0 && \
	(int)(pos.y) / TILE_SIZE < (int) cub->map->y_size_max && (int)(pos.x) / TILE_SIZE < (int) cub->map->x_size_max)
	{
		if (cub->map->raw_map[(int)((pos.y) / TILE_SIZE)][(int)((pos.x + buff) / TILE_SIZE)] == '1')
			return (ft_len_ray(seg->from, (t_point) {pos.x, pos.y}));
		pos.x += d.x;
		pos.y += d.y;
	}
	return (DBL_MAX);
}
