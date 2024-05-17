/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:35:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/17 11:48:31 by mbruyant         ###   ########.fr       */
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
        ft_err_ret("MLX initialization failed", NULL, false);
        exit_cleanup(cub);
        exit(EXIT_FAILURE);
    }
    if (!ft_open_images(cub))
    {
        exit_cleanup(cub);
        exit(EXIT_FAILURE);
    }
}


void init_windows(t_data *cub)
{
    cub->win_2d = mlx_new_window(cub->mlx_ptr, cub->map->x_size_max * \
    TILE_SIZE, cub->map->y_size_max * TILE_SIZE, "2D Map View");
    if (!cub->win_2d)
    {
        ft_err_ret("Window creation failed for 2D map view", NULL, false);
        exit_cleanup(cub);
    }

    int total_width = W_WIDTH;
    cub->win_3d = mlx_new_window(cub->mlx_ptr, total_width, W_HEIGHT, "3D View");
    if (!cub->win_3d)
    {
        ft_err_ret("Window creation failed for 3D map view", NULL, false);
        exit_cleanup(cub);
    }
    mlx_hook(cub->win_2d, 17, 0L, (int (*)())exit_cleanup, cub);
    mlx_hook(cub->win_3d, 17, 0L, (int (*)())exit_cleanup, cub);
}

void update_player_position(t_data *cub, t_point_d old, t_point_d new)
{
    draw_player(cub, old, C_WHITE);
    ft_draw_angle(cub, &old, cub->angle, C_WHITE);
    draw_player(cub, new, C_RED);
    ft_draw_angle(cub, &new, cub->angle, C_RED);
}

void move_player(t_data *cub, int keycode)
{
    t_point_d old;
    t_point_d new;

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
	if ((int)new.y / TILE_SIZE >= 0 && (int) new.y / TILE_SIZE < \
    (int) cub->map->y_size_max && (int)new.x / TILE_SIZE >= 0 && \
    (int) new.x / TILE_SIZE < \
    (int) ft_strlen(cub->map->raw_map[(int)new.y / TILE_SIZE])) 
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
	if (keycode == UP || keycode == DOWN || \
    keycode == LEFT || keycode == RIGHT)
	{	
        move_player(cub, keycode);
        render_3d(cub);

    }
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW || \
    keycode == CLIC || keycode == R_CLIC)
	{
		ft_handle_angle(cub, keycode);
		ft_seg_refresh(cub);
        render_3d(cub);

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
