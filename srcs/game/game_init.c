/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:35:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/02 10:38:37 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
must exit if fails
*/
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
		exit(EXIT_FAILURE);
	}
}

/*
must exit if fails
should mlx_destroy_display should be there, or the free would be enough ?
*/
void	init_window(t_data *cub)
{
	printf("x_size:%zu\n", cub->map->x_size_max);
		printf("y_size:%zu\n", cub->map->y_size_max);

	cub->win_ptr = mlx_new_window(cub->mlx_ptr, \
	cub->map->x_size_max * 65, cub->map->y_size_max * 65, "minicarte");
	if (!cub->win_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
		ft_free_map(cub->map);
		ft_safe_free(&(cub->tmp_line));
		ft_free_textures(cub);
		ft_close_fd(&(cub->tmp_fd));
		ft_printf_fd(2, "Error : Window creation failded\n");
		exit(EXIT_FAILURE);
	}
}

void put_map_cell_to_window(t_data *cub, int x, int y, int color)
{
	int i = 0;
	int j;
	while (i < 65) 
	{
		j = 0;
		while (j < 65)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x * 65 + i, \
			y * 65 + j, color);
			j++;
		}
		i++;
	}
}

/*
start_x = pos.x - 2;
start_y = pos.y - 2;

Allows us to center the player dot
*/
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
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, start_x + i, start_y + j, color);
			j++;
		}
		i++;
	}
}

void render_map(t_data *cub)
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
				put_map_cell_to_window(cub, x, y, 0xAAAAAA); //draw wall 
			else
				put_map_cell_to_window(cub, x, y, 0xF5F5F5); // draw ground
			if (x == cub->map->spawn.x && y == cub->map->spawn.y)
				draw_player(cub, cub->position, 0xFF0000); // draw player
			x++;
		}
		while (x < (int)cub->map->x_size_max)
		{
			put_map_cell_to_window(cub, x, y, 0xF5F5F5);
			x++;
		}
		y++;
	}
}

void	ft_get_starting_angle(t_data *cub)
{
	if (cub->map->spawn_angle == 'N')
		cub->angle = PI / 2;
	if (cub->map->spawn_angle == 'S')
		cub->angle = (3 * PI) / 2;
	if (cub->map->spawn_angle == 'E')
		cub->angle = 0;
	if (cub->map->spawn_angle == 'W')
		cub->angle = PI;
}

void update_player_position(t_data *cub, t_point old, t_point new)
{
	draw_player(cub, old, 0xF5F5F5); // Draw old position with ground color
	draw_player(cub, new, 0xFF0000); // Draw new position with red color for player
}


void move_player(t_data *cub, int keycode)
{
	t_point	old;
	t_point	new;

	old = cub->position;
	new = old;
	if (keycode == UP)
		new.y -= 5;
	else if (keycode == DOWN)
		new.y += 5;
	else if (keycode == LEFT)
		new.x -= 5;
	else if (keycode == RIGHT)
		new.x += 5;
	if (cub->map->raw_map[new.y / 65][new.x / 65] != '1') 
	{
		update_player_position(cub, old, new);
		cub->position = new;
	}
}

int key_hook(int keycode, void *param)
{
	t_data *cub;
	
	cub = (t_data *)param;
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		move_player(cub, keycode);
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
		ft_free_map(cub->map);
		ft_safe_free(&(cub->tmp_line));
		ft_free_textures(cub);
		ft_close_fd(&(cub->tmp_fd));
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void ft_game(t_data *cub)
{
	init_mlx(cub);
	init_window(cub);
	cub->position.x = cub->map->spawn.x * 65 + 32;
	cub->position.y = cub->map->spawn.y * 65 + 32;
	ft_get_starting_angle(cub);
	render_map(cub);
	mlx_key_hook(cub->win_ptr, key_hook, cub);
	mlx_loop(cub->mlx_ptr);
}
