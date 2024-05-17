/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:47:51 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/17 10:06:44 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	rgb_to_int(t_rgb color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	put_map_cell_to_window(t_data *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_2d, x * TILE_SIZE + i, \
			y * TILE_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *cub, t_point_d pos, int color)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = pos.x - 2;
	start_y = pos.y - 2;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_2d, \
							start_x + i, start_y + j, color);
			j++;
		}
		i++;
	}
}

void	render_2d_map(t_data *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)cub->map->y_size_max)
	{
		x = 0;
		while (x < (int)ft_strlen(cub->map->raw_map[y]))
		{
			if (cub->map->raw_map[y][x] == '1')
				put_map_cell_to_window(cub, x, y, C_GREY);
			else
				put_map_cell_to_window(cub, x, y, C_WHITE);
			if (x == cub->map->spawn.x && y == cub->map->spawn.y)
			{
				draw_player(cub, cub->position, C_RED);
				ft_print_all_rays(cub);
			}
			x++;
		}
		while (x < (int)cub->map->x_size_max)
		{
			put_map_cell_to_window(cub, x, y, C_WHITE);
			x++;
		}
		y++;
	}
}

/*
Marianne
*/
void	draw_colored_vertical_slice(t_data *cub, t_segment *seg, int x_start)
{
	int	x;
	int	y;
	t_point	colors;

	x = x_start;
	colors.x = rgb_to_int(cub->ceiling_c);
	colors.y = rgb_to_int(cub->floor_c);
	if (cub->map->raw_map[(int) seg->from.y / TILE_SIZE]\
	[(int) seg->from.x / TILE_SIZE] == '1')
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

void	render_3d_view(t_data *cub)
{
	int	column;

	column = 0;
	while (column < (W_WIDTH / COLUMN_W) - 1)
	{
		cub->seg[column].top_pix = (W_HEIGHT / 2) - (cub->seg[column].wall_height / 2);
		if (cub->seg[column].top_pix < 0)
			cub->seg[column].top_pix = 0;
		cub->seg[column].bot_pix = cub->seg[column].top_pix + cub->seg[column].wall_height;
		if (cub->seg[column].bot_pix > W_HEIGHT)
			cub->seg[column].bot_pix = W_HEIGHT;
		draw_colored_vertical_slice(cub, &cub->seg[column], column * COLUMN_W);
		column++;
	}
}

void	render_3d(t_data *cub)
{
	render_3d_view(cub);
}
