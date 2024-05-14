/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ray_math_tuto.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:05:45 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/14 18:33:54 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
https://www.permadi.com/tutorial/raycast/rayc7.html
*/

/*
if (angle > 0 && angle < 180), ray is facing up
parenthese avec -1 ?????
*/
int	ft_find_first_y(t_point_d from, double angle)
{
	if (angle > 0 && angle < 180)
		return ((floor(from.y / TILE_SIZE) * TILE_SIZE) - 1);
	return (floor(from.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
}

int	ft_find_first_x(t_data *cub, t_point_d goal)
{
	return (cub->position.x + (cub->position.y - goal.y) / tan(cub->angle));
}

double	ft_check_horizontal(t_data *cub)
{
	t_point_d	goal;

	if (cub->angle == 0 || cub->angle == 180 || cub->angle == 360)
		return (DBL_MAX);
	goal.x = 0;
	goal.y = ft_find_first_y(cub->position, cub->angle);
	goal.x = floor(ft_find_first_x(cub, goal));
	printf("first horizontal\nangle : %f\ny = %f\nx = %f\n", cub->angle, goal.y / TILE_SIZE, goal.x / TILE_SIZE);
	return (DBL_MAX);
}
