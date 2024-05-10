/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:15:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/10 14:46:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_get_starting_angle(t_data *cub)
{
	if (cub->map->spawn_angle == 'N')
		cub->angle = 90;
	if (cub->map->spawn_angle == 'S')
		cub->angle = 270;
	if (cub->map->spawn_angle == 'E')
		cub->angle = 0;
	if (cub->map->spawn_angle == 'W')
		cub->angle = 180;
}

/*
i starts at 4 so the angle ray doesn't go over the player
*/
void	ft_draw_angle(t_data *cub, t_point *pos, double angle, int color)
{
	double	dx;
	double	dy;
	int		x;
	int		y;
	int		i;

	dx = cos(ft_deg_to_rad(angle));
	dy = sin(ft_deg_to_rad(angle));
	i = 4;
	while (i < 14)
	{
		x = pos->x + round(i * dx);
		y = pos->y - round(i * dy);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x, y, color);
		i++;
	}
}

void	ft_handle_angle(t_data *cub, int keycode)
{
	if (keycode == LEFT_ARROW || keycode == CLIC)
		cub->angle += INCR_DEG;
	if (keycode == RIGHT_ARROW || keycode == R_CLIC)
		cub->angle -= INCR_DEG;
	if (cub->angle < 0)
		cub->angle += 360;
	else if (cub->angle > 360)
		cub->angle -= 360;
}
/*
bool	ft_has_v_side_wall(t_data *cub, t_point pt)
{
	if ((pt.y >= 1 && cub->map->raw_map[pt.y - 1][pt.x] == '1') || \
	(pt.y < cub->map->y_size_max && cub->map->raw_map[pt.y + 1][pt.x] == '1'))
			return (true);
	return (false);
}

bool	ft_has_h_side_wall(t_data *cub, t_point pt)
{
	if (pt.x >= 1 && cub->map->raw_map[pt.y][pt.x - 1] == '1')
		if (pt.x < cub->map->x_size_max && cub->map->raw_map[pt.y][pt.x + 1] == '1')
			return (true);
	return (false);
}
*/

/*
>= because at the exact "limit" angle will be a corner (not drawn ?)
but still needs to be handled to avoir errors
*/
t_compass	ft_get_which_wall(t_segment *seg)
{
	if (seg->angle == 0 || seg->angle == 360)
		return (EA);
	else if (seg->angle == 90)
		return (NO);
	else if (seg->angle == 180)
		return (WE);
	else if (seg->angle == 270)
		return (SO);
	else if (seg->angle > 0 && seg->angle < 90)
	{
		if ((seg->until.x % TILE_SIZE == 0 || seg->until.x % TILE_SIZE == 64) && (seg->until.y % TILE_SIZE != 0 && seg->until.y % TILE_SIZE != 64))
			return (EA);
		return (NO);
	}
	else if (seg->angle > 90 && seg->angle < 180)
	{
		if ((seg->until.x % TILE_SIZE == 0 || seg->until.x % TILE_SIZE == 64) && (seg->until.y % TILE_SIZE != 0 && seg->until.y % TILE_SIZE != 64))
			return (WE);
		return (NO);
	}
	else if (seg->angle > 180 && seg->angle < 270)
	{
		if ((seg->until.x % TILE_SIZE == 0 || seg->until.x % TILE_SIZE == 64) && (seg->until.y % TILE_SIZE != 0 && seg->until.y % TILE_SIZE != 64))
			return (WE);
		return (SO);
	}
	else if (seg->angle > 270 && seg->angle < 360)
	{
		if ((seg->until.x % TILE_SIZE == 0 || seg->until.x % TILE_SIZE == 64) && (seg->until.y % TILE_SIZE != 0 && seg->until.y % TILE_SIZE != 64))
			return (EA);
		return (SO);
	}
	return (ERR);
}
