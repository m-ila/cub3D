/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:56:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/14 21:01:39 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// /*
// when used, has to put other condition in the loop or else it will be infinite
// */
// bool	ft_is_wall(t_data *cub, t_point_d pt)
// {
// 	t_point	translate;

// 	if (pt.x < 0 || pt.y < 0)
// 		return (false);
// 	translate.x = (int) floor(pt.x / TILE_SIZE);
// 	translate.y = (int) floor(pt.y / TILE_SIZE);
// 	if (translate.y >= (int) cub->map->y_size_max || translate.x >= (int) ft_strlen(cub->map->raw_map[translate.y]))
// 		return (false);
// 	if (cub->map->raw_map[translate.y] && translate.x < (int) ft_strlen(cub->map->raw_map[translate.y]))
// 		if (cub->map->raw_map[translate.y][translate.x] == '1')
// 			return (true);
// 	return (false);
// }

// /*
// check if a point is withing the map without having to deal with TILE_SIZE beforehand
// */
// bool	ft_is_within_map(t_data *cub, t_point_d pt)
// {
// 	t_point	translate;
	
// 	if (pt.x < 0 || pt.y < 0)
// 		return (false);
// 	translate.x = (int) floor(pt.x / TILE_SIZE);
// 	translate.y = (int) floor(pt.y / TILE_SIZE);
// 	if (translate.y >= (int) cub->map->y_size_max || translate.x >= (int) ft_strlen(cub->map->raw_map[translate.y]))
// 		return (false);
// 	return (true);
// }

// /*
// for horizontal intersection only
// ensures that the step for the x axe is in the same direction of the angle
// */
// void	ft_adjust_step_horizontal(t_data *cub, t_point_d *step)
// {
// 	if ((cub->angle > 90 && cub->angle < 270) && step->x > 0)
// 		step->x *= -1;
// 	else if (!(cub->angle > 90 && cub->angle < 270) && step->x < 0)
// 		step->x *= -1;
// }

// /*
// for vertical intersection only
// ensures that the step for the y axe is in the same direction of the angle
// */
// void	ft_adjust_step_vertical(t_data *cub, t_point_d *step)
// {
// 	if ((cub->angle > 0 && cub->angle < 180) && step->y < 0)
// 		step->y *= -1;
// 	else if (!(cub->angle > 0 && cub->angle < 180) && step->y > 0)
// 		step->y *= -1;
// }

// /*
// if angle included in ]0,180[, then looking for horizontal in the updward direction
// else, must look in the downward direction, so the step.y has to be in the negatives
// the variable buffer is here to take into account the current line we're in, depending on
// the angle (direction + or -)
// */
// double	ft_hzt_intersections(t_data *cub)
// {
// 	t_point_d	hor;
// 	t_point_d	step;
// 	double		buffer;

// 	if (cub->angle == 0 || cub->angle == 180 || cub->angle == 360)
// 		return (DBL_MAX);
// 	step.y = TILE_SIZE;
// 	step.x = TILE_SIZE / tan(cub->angle);
// 	hor.y = floor(cub->position.y / TILE_SIZE) * TILE_SIZE;
// 	if (cub->angle > 0 && cub->angle < 180)
// 	{
// 		hor.y += TILE_SIZE;
// 		buffer = -1;
// 	}
// 	else
// 	{
// 		step.y *= -1;
// 		buffer = 1;
// 	}
// 	hor.x = cub->position.x + (hor.y - cub->position.y) / tan(cub->angle);
// 	ft_adjust_step_horizontal(cub, &step);
// 	while (ft_is_within_map(cub, (t_point_d){hor.x, (hor.y - buffer)}) && \
// 	!ft_is_wall(cub, (t_point_d){hor.x, (hor.y - buffer)}))
// 	{
// 		hor.x += step.x;
// 		hor.y += step.y;
// 	}
// 	return (sqrt((pow(hor.y - cub->position.y, 2.0)) + (pow(hor.x - cub->position.x, 2.0))));
// }

// double	ft_vrt_intersections(t_data *cub)
// {
// 	t_point_d	ver;
// 	t_point_d	step;
// 	double		buffer;

// 	if (cub->angle == 90 || cub->angle == 270)
// 		return (1000000.0);
// 	step.y = TILE_SIZE;
// 	step.x = TILE_SIZE / tan(cub->angle);
// 	ver.x = floor(cub->position.y / TILE_SIZE) * TILE_SIZE;
// 	if (!(cub->angle > 90 && cub->angle < 270))
// 	{
// 		ver.x += TILE_SIZE;
// 		buffer = -1;
// 	}
// 	else
// 	{
// 		step.x *= -1;
// 		buffer = 1;
// 	}
// 	ver.y = cub->position.y + (ver.x - cub->position.x) / tan(cub->angle);
// 	ft_adjust_step_vertical(cub, &step);
// 	while (ft_is_within_map(cub, (t_point_d){(ver.x - buffer), ver.y}) && \
// 	!ft_is_wall(cub, (t_point_d){(ver.x - buffer), ver.y}))
// 	{
// 		ver.x += step.x;
// 		ver.y += step.y;
// 	}
// 	return (sqrt((pow(ver.y - cub->position.y, 2.0)) + (pow(ver.x - cub->position.x, 2.0))));
// }

bool	ft_facing_up(double angle)
{
	return (angle > 0 && angle < 180);
}

bool	ft_pointing_left(double angle)
{
	return (angle > 90 && angle < 270);
}

// double	ft_hzt_intersections(t_data *cub, t_segment *seg)
// {
// 	t_point_d	d;
// 	t_point_d	pos;
// 	bool		buff;

// 	if (seg->angle == 0 || seg->angle == 90 || seg->angle == 180 || \
// 	seg->angle == 270 || seg->angle == 360)
// 		return (DBL_MAX);
// 	d.y = TILE_SIZE;
// 	d.x = TILE_SIZE / tan(seg->angle);
// 	buff = 0;
// 	pos.y = floor(seg->from.y / TILE_SIZE) * TILE_SIZE;
// 	if (!ft_facing_up(seg->angle))
// 	{
// 		pos.y += TILE_SIZE;
// 		buff = -TILE_SIZE;
// 	}
// 	pos.x = seg->from.x + (pos.y - seg->from.y) / tan(seg->angle);
// 	if (ft_facing_up(seg->angle))
// 		d.y *= -1.0;
// 	if (ft_pointing_left(seg->angle) && d.x > 0.0)
// 		d.x *= -1.0;
// 	else if (!ft_pointing_left(seg->angle) && d.x < 0.0)
// 		d.x *= -1.0;
// 	while ((int)(pos.y) / TILE_SIZE > 0 && (int)(pos.x) / TILE_SIZE > 0 && \
// 	(int)(pos.y) / TILE_SIZE < (int) cub->map->y_size_max && (int)(pos.x) / TILE_SIZE < (int) cub->map->x_size_max)
// 	{
// 		if (cub->map->raw_map[(int)(pos.y + buff) / TILE_SIZE][(int)pos.x / TILE_SIZE] == '1')
// 			return (ft_len_ray(seg->from, pos));
// 		pos.x += d.x;
// 		pos.y += d.y;
// 	}
// 	return (DBL_MAX);
// }

// double	ft_vrt_intersections(t_data *cub, t_segment *seg)
// {
// 	t_point_d	d;
// 	t_point_d	pos;
// 	bool		buff;

// 	if (seg->angle == 0 || seg->angle == 90 || seg->angle == 180 || \
// 	seg->angle == 270 || seg->angle == 360)
// 		return (DBL_MAX);
// 	buff = 0;
// 	pos.x = floor(seg->from.x / TILE_SIZE) * TILE_SIZE;
// 	if (!ft_pointing_left(seg->angle))
// 	{
// 		buff = -TILE_SIZE;
// 		pos.x += TILE_SIZE;
// 	}
// 	pos.y = seg->from.y + (pos.x - seg->from.x) * tan(seg->angle);
// 	mlx_pixel_put(cub->mlx_ptr, cub->win_2d, (int)pos.x, (int)pos.y, C_PURPLE);
// 	d.x = TILE_SIZE;
// 	if (ft_pointing_left(seg->angle))
// 		d.x *= -1.0;
// 	d.y = TILE_SIZE * tan(seg->angle);
// 	if (ft_facing_up(seg->angle) && d.y > 0.0)
// 		d.y *= -1.0;
// 	else if (!ft_facing_up(seg->angle) && d.y < 0.0)
// 		d.y *= -1.0;
// 	while ((int)(pos.y) / TILE_SIZE > 0 && (int)(pos.x) / TILE_SIZE > 0 && \
// 	(int)(pos.y) / TILE_SIZE < (int) cub->map->y_size_max && (int)(pos.x) / TILE_SIZE < (int) cub->map->x_size_max)
// 	{
// 		if (cub->map->raw_map[(int)((pos.y) / TILE_SIZE)][(int)((pos.x + buff) / TILE_SIZE)] == '1')
// 			return (ft_len_ray(seg->from, pos));
// 		pos.x += d.x;
// 		pos.y += d.y;
// 	}
// 	return (DBL_MAX);
// }

double	ft_hzt_intersections(t_data *cub, t_segment *seg)
{
	t_point_d	d;
	t_point_d	pos;
	t_point_d	first;

	if (seg->angle == 0 || seg->angle == 90 || seg->angle == 180 || \
	seg->angle == 270 || seg->angle == 360)
		return (DBL_MAX);
	if (ft_facing_up(seg->angle))
		first.y = floor(seg->from.y / TILE_SIZE) * TILE_SIZE - 0.0001;
	else
		first.y = floor(seg->from.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	first.x = seg->from.x + (seg->from.y - first.y) / tan(seg->angle);
	if (ft_facing_up(seg->angle))
		d.y = -TILE_SIZE;
	else
		d.y = TILE_SIZE;
	d.x = (d.y - 1) / tan(seg->angle);
	pos = first;
	while ((int)(pos.y) / TILE_SIZE > 0 && (int)(pos.x) / TILE_SIZE > 0 && \
	(int)(pos.y) / TILE_SIZE < (int) cub->map->y_size_max && (int)(pos.x) / TILE_SIZE < (int) cub->map->x_size_max)
	{
		if (cub->map->raw_map[(int)(pos.y) / TILE_SIZE][(int)pos.x / TILE_SIZE] == '1')
			return (ft_len_ray(seg->from, pos));
		pos.x += d.x;
		pos.y += d.y;
	}
	return (DBL_MAX);
}

double	ft_vrt_intersections(t_data *cub, t_segment *seg)
{
	t_point_d	d;
	t_point_d	pos;
	t_point_d	first;

	if (seg->angle == 0 || seg->angle == 90 || seg->angle == 180 || \
	seg->angle == 270 || seg->angle == 360)
		return (DBL_MAX);
	if (ft_pointing_left(seg->angle))
		first.x = floor(seg->from.x / TILE_SIZE) * TILE_SIZE - 0.00001;
	else
		first.x = floor(seg->from.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	first.y = seg->from.y + (seg->from.x - first.x) * tan(seg->angle);
	if (ft_pointing_left(seg->angle))
		d.x = -TILE_SIZE;
	else
		d.x = TILE_SIZE;
	d.y = TILE_SIZE * tan(seg->angle);
	pos = first;
	while ((int)(pos.y) / TILE_SIZE > 0 && (int)(pos.x) / TILE_SIZE > 0 && \
	(int)(pos.y) / TILE_SIZE < (int) cub->map->y_size_max && (int)(pos.x) / TILE_SIZE < (int) cub->map->x_size_max)
	{
		if (cub->map->raw_map[(int)((pos.y) / TILE_SIZE)][(int)((pos.x) / TILE_SIZE)] == '1')
			return (ft_len_ray(seg->from, pos));
		pos.x += d.x;
		pos.y += d.y;
	}
	return (DBL_MAX);
}



