/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:47:51 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/09 21:18:37 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


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


void draw_colored_vertical_slice(t_data *cub, int x_start, int top, int bottom, double distance)
{
    int shade;
    int x;
    int y;
    uint32_t wall_color;

    shade = 255 - (int)(distance * 0.5);
    if (shade < 0)
        shade = 0;
    wall_color = (shade << 16) | (0 << 8) | shade;
    x = x_start;
    while (x < x_start + 10)
    {
        y = 0;
        while (y < top)
        {
            mlx_pixel_put(cub->mlx_ptr, cub->win_3d, x, y, CEILING_COLOR);
            y++;
        }
        while (y <= bottom)
        {
            mlx_pixel_put(cub->mlx_ptr, cub->win_3d, x, y, wall_color);
            y++;
        }
        while (y < 600)
        {
            mlx_pixel_put(cub->mlx_ptr, cub->win_3d, x, y, FLOOR_COLOR);
            y++;
        }
        x++;
    }
}

double calculate_ray_angle(double player_angle, int column)
{
    double fov = M_PI / 3;
    return player_angle - fov / 2 + column * (fov / 90);
}

void render_3d_view(t_data *cub)
{
    double wall_height, distance, corrected_distance;
    double player_angle = cub->seg->angle;
    double ray_angle;
    int column, top_pixel, bottom_pixel;

    for (column = 0; column < 90; column++)
    {
        t_segment *seg = &cub->seg[column];
        distance = seg->slope_len;

        ray_angle = calculate_ray_angle(player_angle, column);
        corrected_distance = distance * cos(ray_angle - player_angle);
        wall_height = (TILE_SIZE * cub->map->y_size_max * TILE_SIZE) / corrected_distance;
        top_pixel = (cub->map->y_size_max * TILE_SIZE - wall_height) / 2;
        bottom_pixel = top_pixel + wall_height;
        bottom_pixel = bottom_pixel > (int)(cub->map->y_size_max * TILE_SIZE) ? (int)(cub->map->y_size_max * TILE_SIZE) : bottom_pixel;
        draw_colored_vertical_slice(cub, column * 10, top_pixel, bottom_pixel, corrected_distance);
		
    }
}




