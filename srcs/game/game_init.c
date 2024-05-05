/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:35:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/05 14:10:22 by mbruyant         ###   ########.fr       */
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
	cub->map->x_size_max * TILE_SIZE, cub->map->y_size_max * TILE_SIZE, "minicarte");
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
/*
void print_border(t_data *cub, int x, int y, int color)
{
    int i = 0;
    int j = 0;

    // Print top border
    while (j < TILE_SIZE) {
        mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
        j++;
    }

    j = 0;

    // Print left border
    while (i < TILE_SIZE) {
        mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
        i++;
    }

    i = TILE_SIZE - 1;
    j = 0;

    // Print right border
    while (j < TILE_SIZE) {
        mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
        j++;
    }

    i = 0;
    j = TILE_SIZE - 1;

    // Print bottom border
    while (i < TILE_SIZE) {
        mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
        i++;
    }
}
*/

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
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x * TILE_SIZE + i, \
			y * TILE_SIZE + j, color);
			j++;
		}
		//print_border(cub, x, y, C_BLACK);
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
				put_map_cell_to_window(cub, x, y, C_GREY);
			else
				put_map_cell_to_window(cub, x, y, C_WHITE);
			if (x == cub->map->spawn.x && y == cub->map->spawn.y)
			{
				draw_player(cub, cub->position, C_RED);
				ft_draw_angle_seg(cub, cub->seg, C_RED);
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

void update_player_position(t_data *cub, t_point old, t_point new)
{
	draw_player(cub, old, C_WHITE); // Draw old position with ground color
	ft_draw_angle(cub, &old, cub->angle, C_WHITE);
	draw_player(cub, new, C_RED); // Draw new position with red color for player
	ft_draw_angle(cub, &new, cub->angle, C_RED);
}

/*
For easier future debug (wall collision and angles)
I allowed myself to put a define here (INCR_STEP)
*/
void move_player(t_data *cub, int keycode)
{
	t_point	old;
	t_point	new;

	old = cub->position;
	new = old;
	if (keycode == UP)
		ft_up(cub, &new);
	else if (keycode == DOWN)
		ft_down(cub, &new);
	else if (keycode == LEFT)
		ft_left(cub, &new);
	else if (keycode == RIGHT)
		ft_right(cub, &new);
	if (cub->map->raw_map[new.y / TILE_SIZE][new.x / TILE_SIZE] != '1') 
	{
		update_player_position(cub, old, new);
		cub->position = new;
		ft_seg_refresh(cub);
	}
}

int key_hook(int keycode, void *param)
{
	t_data	*cub;
	
	cub = (t_data *)param;
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		move_player(cub, keycode);
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW || keycode == CLIC || keycode == R_CLIC)
	{
		ft_handle_angle(cub, keycode);
		ft_seg_refresh(cub);
	}
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

int	ft_button_input(t_data *cub)
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

void ft_game(t_data *cub)
{
	init_mlx(cub);
	init_window(cub);
	cub->position.x = cub->map->spawn.x * TILE_SIZE + 32;
	cub->position.y = cub->map->spawn.y * TILE_SIZE + 32;
	ft_get_starting_angle(cub);
	cub->seg = ft_segment(cub, cub->angle);
	render_map(cub);
	mlx_key_hook(cub->win_ptr, key_hook, cub);
	mlx_hook(cub->win_ptr, 17, 0, ft_button_input, cub);
	mlx_mouse_hook(cub->win_ptr, ft_handle_clic, cub);
	mlx_loop(cub->mlx_ptr);
}
