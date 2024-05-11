/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:44:32 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/10 18:26:32 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_draw_square(t_data *cub, t_point square)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = square.x * TILE_SIZE;
	start_y = square.y * TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_2d, start_x + i, start_y + j, C_RED);
			j++;
		}
		i++;
	}
}

void	ft_draw_angle_seg(t_data *cub, t_segment seg, int color)
{
	double	dx;
	double	dy;
	int		x;
	int		y;
	double		i;

	dx = cos(ft_deg_to_rad(seg.angle));
	dy = sin(ft_deg_to_rad(seg.angle));
	i = 4.0;
	while (i < seg.slope_len)
	{
		x = seg.from.x + round(i * dx);
		y = seg.from.y - round(i * dy);
		mlx_pixel_put(cub->mlx_ptr, cub->win_2d, x, y, color);
		i += 1.0;
	}
}
