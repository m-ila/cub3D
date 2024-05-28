/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:47:51 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/28 21:02:48 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_colored_vertical_slice(t_data *cub, t_segment *seg, int x_start)
{
	int		x;
	int		y;
	t_point	colors;

	x = x_start;
	colors.x = rgb_to_int(cub->ceiling_c);
	colors.y = rgb_to_int(cub->floor_c);
	if (ft_player_is_in_wall(cub, seg))
	{
		colors.x = C_GREY;
		colors.y = C_GREY;
	}
	while (x < x_start + COLUMN_W)
	{
		y = -1;
		while (++y < seg->top_pix)
			mlx_pixel_put(cub->mlx_ptr, cub->win_3d, W_WIDTH - x, y, colors.x);
		while (++y <= seg->bot_pix)
			mlx_pixel_put(cub->mlx_ptr, cub->win_3d, W_WIDTH - x, y, \
			ft_get_pixel(cub, seg, y));
		while (++y < W_HEIGHT)
			mlx_pixel_put(cub->mlx_ptr, cub->win_3d, W_WIDTH - x, y, colors.y);
		x++;
	}
}

void	render_3d(t_data *cub)
{
	int	column;

	column = 0;
	while (column < (W_WIDTH / COLUMN_W) - 1)
	{
		cub->seg[column].top_pix = (W_HEIGHT / 2) - \
		(cub->seg[column].wall_height / 2) - 1;
		if (cub->seg[column].top_pix < 0)
			cub->seg[column].top_pix = 0;
		cub->seg[column].bot_pix = cub->seg[column].top_pix + \
		cub->seg[column].wall_height;
		if (cub->seg[column].bot_pix > W_HEIGHT)
			cub->seg[column].bot_pix = W_HEIGHT;
		draw_colored_vertical_slice(cub, &cub->seg[column], column * COLUMN_W);
		column++;
	}
}
