/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:42 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/17 15:30:18 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_player_minimap(t_data *cub, int start_x, int start_y)
{
	int	player_minimap_x;
	int	player_minimap_y;

	int (i) = 0;
	int (j) = 0;
	player_minimap_x = start_x + \
	(int)((float)cub->position.x / TILE_SIZE * MINI_TILE_SIZE);
	player_minimap_y = start_y + \
	(int)((float)cub->position.y / TILE_SIZE * MINI_TILE_SIZE);
	while (i < 2)
	{
		while (j < 2)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_3d, \
			player_minimap_x + i, player_minimap_y + j, C_RED);
			j++;
		}
		i++;
	}
}

void	draw_minimap_tile(t_data *cub, t_point tile, t_point start)
{
	int	color;

	int (i) = -1;
	int (j) = -1;
	int (pixel_x) = start.x + tile.x * MINI_TILE_SIZE;
	int (pixel_y) = start.y + tile.y * MINI_TILE_SIZE;
	if (cub->map->raw_map[tile.y][tile.x] == '1')
		color = 0xFFFFFF;
	else
		color = 0x000000;
	while (++i < MINI_TILE_SIZE)
	{
		j = -1;
		while (++j < MINI_TILE_SIZE)
			mlx_pixel_put(cub->mlx_ptr, cub->win_3d, pixel_x + i, \
							pixel_y + j, color);
	}
}

void	render_minimap(t_data *cub)
{
	t_point	tile;
	t_point	minimap_start;

	minimap_start.x = W_WIDTH + 1;
	minimap_start.y = W_HEIGHT - (cub->map->y_size_max * MINI_TILE_SIZE);
	tile.y = 0;
	while (tile.y < (int)cub->map->y_size_max)
	{
		tile.x = 0;
		while (tile.x < (int)cub->map->x_size_max)
		{
			draw_minimap_tile(cub, tile, minimap_start);
			tile.x++;
		}
		tile.y++;
	}
	draw_player_minimap(cub, minimap_start.x, minimap_start.y);
}
