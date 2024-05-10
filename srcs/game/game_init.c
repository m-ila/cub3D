/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:35:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/10 18:32:40 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void init_mlx(t_data *cub)
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

void init_windows(t_data *cub)
{
    // Print size information for debugging
    printf("x_size:%zu\n", cub->map->x_size_max);
    printf("y_size:%zu\n", cub->map->y_size_max);

    // Initialize window for the 2D map view
    cub->win_2d = mlx_new_window(cub->mlx_ptr, cub->map->x_size_max * TILE_SIZE, cub->map->y_size_max * TILE_SIZE, "2D Map View");
    if (!cub->win_2d)
    {
        fprintf(stderr, "Error: Window creation failed for 2D map view\n");
        exit_cleanup(cub); // Handle cleanup and exit
    }

    // Initialize window for the 3D view
    cub->win_3d = mlx_new_window(cub->mlx_ptr, 900, 600, "3D View"); // Assuming 900x600 for 3D view
    if (!cub->win_3d)
    {
        fprintf(stderr, "Error: Window creation failed for 3D view\n");
        exit_cleanup(cub); // Handle cleanup and exit
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
    t_point old;
    t_point new;

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
	{	
        move_player(cub, keycode);
        render_3d_view(cub);

    }
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW || keycode == CLIC || keycode == R_CLIC)
	{
		ft_handle_angle(cub, keycode);
		ft_seg_refresh(cub);
                render_3d_view(cub);

	}
	else if (keycode == ESC)
        exit_cleanup(cub); 
	return (0);
}

int ft_button_input(t_data *cub)
{
    mlx_destroy_window(cub->mlx_ptr, cub->win_2d);
    mlx_destroy_display(cub->mlx_ptr);
    free(cub->mlx_ptr);
    ft_free_map(cub->map);
    ft_safe_free(&(cub->tmp_line));
    ft_free_textures(cub);
    ft_close_fd(&(cub->tmp_fd));
    free(cub->seg);
    exit(EXIT_SUCCESS);
}
