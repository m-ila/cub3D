/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:35:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/01 18:05:47 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// typedef struct s_data
// {
// 	t_map	*map;
// 	t_point	*position;
// 	char	*path_texture[5];
// 	t_rgb	floor_c;
// 	t_rgb	ceiling_c;
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	int		tmp_fd;
// 	char	*tmp_line;
// }	t_data;

// typedef struct s_map
// {
// 	char	**raw_map;
// 	char	**map_cpy;
// 	size_t	x_size_max;
// 	size_t	y_size_max;
// 	size_t	x_size_playable;
// 	size_t	y_size_playable;
// 	size_t	x_from;
// 	size_t	x_until;
// 	size_t	y_from;
// 	size_t	y_until;
// 	int		spawn_nb;
// 	char	spawn_angle;
// 	t_point	spawn;
// }	t_map;

void	init_mlx(t_data *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
	{
        ft_free_map(cub->map);
        ft_safe_free(&(cub->tmp_line));
        ft_free_textures(cub);
        ft_close_fd(&(cub->tmp_fd));
		ft_printf_fd(2, "Error : MLX init failded\n");
    }
}

void	init_window(t_data *cub)
{
    printf("x_size:%zu\n", cub->map->x_size_max);
        printf("y_size:%zu\n", cub->map->y_size_max);

	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->map->x_size_max * 65, cub->map->y_size_max * 65, "minicarte");
	if (!cub->win_ptr)
    {
        ft_free_map(cub->map);
        ft_safe_free(&(cub->tmp_line));
        ft_free_textures(cub);
        ft_close_fd(&(cub->tmp_fd));
		ft_printf_fd(2, "Error : Window creation failded\n");
    }
}

void put_map_cell_to_window(t_data *cub, int x, int y, int color) {
    int pixel_x, pixel_y;

    // Calculate starting pixel coordinates for the tile (each tile is represented by a square of size mapS)
    pixel_x = x * 65;
    pixel_y = y * 65;

    // Loop through each pixel in the tile to set its color based on the map data
    for (int i = 0; i < 65; i++) {
        for (int j = 0; j < 65; j++) {
            mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, pixel_x + i, pixel_y + j, color);
        }
    }
}

void render_map(t_data *cub) {
    int x, y, color;

    for (y = 0; y < (int)cub->map->y_size_max; y++) {
        for (x = 0; x < (int)cub->map->x_size_max; x++) {
            // Determine color based on map content
            if (cub->map->raw_map[y][x] == '1') {
                color = 0xAAAAAA; // Grey for walls
            } else {
                color = 0xF5F5F5; // Off-white for open space
            }

            // Render the basic cell
            put_map_cell_to_window(cub, x, y, color);

            // Check if we need to highlight the spawn point
            if (x == cub->map->spawn.x && y == cub->map->spawn.y) {
                int pixel_x = x * 65;
                int pixel_y = y * 65;
                // Highlight the spawn point with a 5x5 red square
                for (int i = 30; i < 35; i++) { // Centered square
                    for (int j = 30; j < 35; j++) {
                        mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, pixel_x + i, pixel_y + j, 0xFF0000);
                    }
                }
            }
        }
    }
}

// # define UP 119
// # define DOWN 115
// # define LEFT 97
// # define RIGHT 100
// # define ESC 65307
// # define CLIC 1

void move_player(t_data *cub, int keycode) {
    t_point old;
    t_point new;

    old.x = cub->map->spawn.x;
    old.y = cub->map->spawn.y;
    new.x = old.x;
    new.y = old.y;

    switch (keycode)
    {
        case UP:
            new.y -= 1; // Move up in the map
            break;
        case DOWN:
            new.y += 1; // Move down in the map
            break;
        case LEFT:
            new.x -= 1; // Move left in the map
            break;
        case RIGHT:
            new.x += 1; // Move right in the map
            break;
    }

    // Check boundaries and obstacles here (assuming '1' represents an obstacle or wall)
    if (new.x >= 0 && new.x < (int)cub->map->x_size_max &&
        new.y >= 0 && new.y < (int)cub->map->y_size_max &&
        cub->map->raw_map[new.y][new.x] != '1') {
        // Update spawn point position if new position is valid
        cub->map->spawn.x = new.x;
        cub->map->spawn.y = new.y;
        render_map(cub);  // Redraw the map with the new player position
    }
}


int key_hook(int keycode, void *param)
{
    t_data *cub = (t_data *)param;

    if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
        move_player(cub, keycode);
    else if (keycode == ESC) {
        // Assuming cleanup functions are correctly defined
        ft_free_map(cub->map);
        ft_safe_free(&(cub->tmp_line));
        ft_free_textures(cub);
        ft_close_fd(&(cub->tmp_fd));
        exit(EXIT_SUCCESS);
    }
    return (0);
}

void	ft_game(t_data *cub)
{
	init_mlx(cub);
	init_window(cub);
	render_map(cub);
    mlx_key_hook(cub->win_ptr, key_hook, &cub);

    mlx_loop(cub->mlx_ptr); 
}
