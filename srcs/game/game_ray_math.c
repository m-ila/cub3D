/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ray_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:05:45 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 12:19:21 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	ft_check_embed(t_data *cub, t_point_d *end)
{
	t_point	left;
	t_point	right;

	left.y = (int) end->y / TILE_SIZE;
	left.x = (int)(end->x - 1) / TILE_SIZE;
	right.y = (int) end->y / TILE_SIZE;
	right.x = (int)(end->x + 1) / TILE_SIZE;
	return ((cub->map->raw_map[left.y][left.x] && \
	cub->map->raw_map[left.y][left.x] == '1') || \
	(cub->map->raw_map[right.y][right.x] && \
	cub->map->raw_map[right.y][right.x] == '1'));
}

/*
If ray hits an exact pixel being a corner, will
check the ones on the right and left (deals with diagonal walls)
*/
static bool	ft_check_diag_wall(t_data *cub, t_point_d *end)
{
	if (((int) end->x % TILE_SIZE == 0.0 || \
	(int) end->x % TILE_SIZE == TILE_SIZE - 1) && \
	((int) end->y % TILE_SIZE == 0.0 || \
	(int) end->y % TILE_SIZE == TILE_SIZE - 1) && ft_check_embed(cub, end))
		return (true);
	return (false);
}

t_point_d	ft_find_end_point(t_data *cub, t_point_d *end, double angle)
{
	t_point_d	translate;
	double		dx;
	double		dy;
	double		length;

	dx = cos(ft_deg_to_rad(angle));
	dy = sin(ft_deg_to_rad(angle));
	length = sqrt(dx * dx + dy * dy);
	dx /= length;
	dy /= length;
	while (ft_is_within_map_bounds(cub, \
	(t_point){end->x / TILE_SIZE, end->y / TILE_SIZE}) && \
	cub->map->raw_map[(int)end->y / TILE_SIZE][(int)end->x / TILE_SIZE] && \
	cub->map->raw_map[(int)end->y / TILE_SIZE][(int)end->x / TILE_SIZE] != '1')
	{
		if (ft_check_diag_wall(cub, end))
			break ;
		end->x += dx;
		end->y -= dy;
	}
	translate.x = (int) end->x;
	translate.y = (int) end->y;
	return (translate);
}

double	ft_len_ray(t_point_d start, t_point_d end)
{
	return (sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)));
}
