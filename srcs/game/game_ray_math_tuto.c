/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ray_math_tuto.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:05:45 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/09 19:51:04 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
https://www.permadi.com/tutorial/raycast/rayc7.html
*/

/*
if (angle > 0 && angle < 180), ray is facing up
*/
static double	ft_find_first_y(t_point from, double angle)
{
	t_point_d	translate;

	translate.x = (double) from.x;
	translate.y = (double) from.y;
	if (angle > 0 && angle < 180)
		return ((floor(translate.y / TILE_SIZE) * TILE_SIZE));
	return ((floor(translate.y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE);
}

static double	ft_find_first_x(t_data *cub, t_point_d goal, double angle)
{
	return (cub->position.x + (goal.y - cub->position.y) / \
	tan(ft_deg_to_rad(angle)));
}

double	ft_check_horizontal(t_data *cub, double angle)
{
	t_point_d	goal;
	t_point_d	incr;
	int		buffer;

	if (angle == 0 || angle == 180 || angle == 360)
		return (DBL_MAX);
	goal.x = 0;
	goal.y = ft_find_first_y(cub->position, angle);
	goal.x = ft_find_first_x(cub, goal, angle);
	buffer = 0;
	//printf("first horizontal\nangle : %f\ny = %d\nx = %d\n", angle, goal.y / TILE_SIZE, goal.x / TILE_SIZE);
	incr.y = TILE_SIZE;
	if (angle > 0 && angle < 180)
	{
		incr.y *= -1;
		buffer = -TILE_SIZE;
	}
	else
		incr.y *= -1;
	incr.x = TILE_SIZE / tan(ft_deg_to_rad(angle));
	if (angle > 90 && angle < 270 && incr.x > 0.0)
		incr.x *= -1;
	if (!(angle > 90 && angle < 270) && incr.x < 0.0)
		incr.x *= -1;
	while (cub->map->raw_map[(int) goal.y / TILE_SIZE][(int) goal.x / TILE_SIZE])
	{
		if (goal.y + buffer >= 0 && \
		cub->map->raw_map[(int) (goal.y + buffer) / TILE_SIZE][(int) goal.x / TILE_SIZE] == '1')
			return (ft_len_ray(cub->position, (t_point){(int) goal.x, (int) goal.y}));
		goal.x += incr.x;
		goal.y += incr.y;
	}
	return (DBL_MAX);
}
