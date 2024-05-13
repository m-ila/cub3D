/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:47:51 by yuewang           #+#    #+#             */

/*   Updated: 2024/05/12 14:05:47 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int rgb_to_int(t_rgb color)
{
    return ((color.r << 16) | (color.g << 8) | color.b);
}

void	put_map_cell_to_window(t_data *cub, int x, int y, int color)
{
	int i;
	int j;

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

void draw_player(t_data *cub, t_point pos, int color)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = pos.x - 2;
	start_y = pos.y - 2;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_2d, start_x + i, start_y + j, color);
			j++;
		}
		i++;
	}
}

void render_2d_map(t_data *cub)
{
	int x;
	int y;

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

void draw_colored_vertical_slice(t_data *cub, t_segment *seg, int x_start)
{
    int shade;
    int x;
    int y;

    shade = 255 - (int)(seg->len_processed * 0.5);
    if (shade < 0)
        shade = 0;
    x = x_start;
    while (x < x_start + 10)
    {
        y = 0;
        while (y < seg->top_pix)
        {
            mlx_pixel_put(cub->mlx_ptr, cub->win_3d, W_WIDTH - x, y, rgb_to_int(cub->ceiling_c));
            y++;
        }
        while (y <= seg->bot_pix)
        {

            mlx_pixel_put(cub->mlx_ptr, cub->win_3d, W_WIDTH - x, y, ft_get_pixel(cub, seg, y));
            y++;
        }
        while (y < W_HEIGHT)
        {
            mlx_pixel_put(cub->mlx_ptr, cub->win_3d, W_WIDTH - x, y, rgb_to_int(cub->floor_c));
            y++;
        }
        x++;
    }
}

void render_3d_view(t_data *cub) {
    int column = 0;
    while (column < 90) {
        cub->seg[column].top_pix = (W_HEIGHT / 2) - (cub->seg[column].wall_height / 2);
        if (cub->seg[column].top_pix < 0) {
            cub->seg[column].top_pix = 0;
        }
        cub->seg[column].bot_pix = cub->seg[column].top_pix + cub->seg[column].wall_height;
        if (cub->seg[column].bot_pix > W_HEIGHT) {
            cub->seg[column].bot_pix = W_HEIGHT;
        }
        draw_colored_vertical_slice(cub, &cub->seg[column], column * 10);
        column++;
    }
}

void draw_minimap_tile(t_data *cub, int x, int y, int start_x, int start_y)
{
    int pixel_x = start_x + x * MINI_TILE_SIZE;
    int pixel_y = start_y + y * MINI_TILE_SIZE;
    int color = (cub->map->raw_map[y][x] == '1') ? 0xFFFFFF : 0x000000;  // White for walls, black for paths

    for (int i = 0; i < MINI_TILE_SIZE; i++) {
        for (int j = 0; j < MINI_TILE_SIZE; j++) {
            mlx_pixel_put(cub->mlx_ptr, cub->win_3d, pixel_x + i, pixel_y + j, color);
        }
    }
}

void draw_player_minimap(t_data *cub, int start_x, int start_y) {
    int player_minimap_x = start_x + (int)((float)cub->position.x / TILE_SIZE * MINI_TILE_SIZE);
    int player_minimap_y = start_y + (int)((float)cub->position.y / TILE_SIZE * MINI_TILE_SIZE);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mlx_pixel_put(cub->mlx_ptr, cub->win_3d, player_minimap_x + i, player_minimap_y + j, 0xFF0000);  // Light red for player
        }
    }
}

void render_minimap(t_data *cub) {
    int x = 0, y = 0;
    int minimap_start_x = 901;  // Start at the left of the window
    int minimap_start_y = W_HEIGHT - (cub->map->y_size_max * MINI_TILE_SIZE);  // Position at the bottom of the window

    while (y < (int)cub->map->y_size_max) {
        x = 0;
        while (x < (int)cub->map->x_size_max) {
            draw_minimap_tile(cub, x, y, minimap_start_x, minimap_start_y);
            x++;
        }
        y++;
    }
    draw_player_minimap(cub, minimap_start_x, minimap_start_y);
}

void render_3d(t_data *cub)
{
    render_3d_view(cub);
    render_minimap(cub);
}



