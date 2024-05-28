/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:35:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/28 20:59:01 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_mlx(t_data *cub)
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

void	init_windows(t_data *cub)
{
	int	total_width;

	total_width = W_WIDTH + (cub->map->x_size_max * MINI_TILE_SIZE);
	cub->win_3d = mlx_new_window(cub->mlx_ptr, total_width, \
	W_HEIGHT, "3D View");
	if (!cub->win_3d)
	{
		ft_err_ret("Window creation failed for 3D map view", NULL, false);
		exit_cleanup(cub);
	}
	mlx_hook(cub->win_3d, 17, 0L, (int (*)())exit_cleanup, cub);
}

int	key_hook(int keycode, void *param)
{
	t_data	*cub;

	cub = (t_data *)param;
	if (keycode == UP || keycode == DOWN || \
	keycode == LEFT || keycode == RIGHT)
	{	
		move_player(cub, keycode);
		render_3d(cub);
	}
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW \
		|| keycode == CLIC || keycode == R_CLIC)
	{
		ft_handle_angle(cub, keycode);
		ft_seg_refresh(cub);
		render_3d(cub);
	}
	else if (keycode == ESC)
		exit_cleanup(cub);
	return (0);
}

int	ft_button_input(t_data *cub)
{
	mlx_destroy_window(cub->mlx_ptr, cub->win_3d);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	ft_free_map(cub->map);
	ft_safe_free(&(cub->tmp_line));
	ft_free_textures(cub);
	ft_close_fd(&(cub->tmp_fd));
	free(cub->seg);
	exit(EXIT_SUCCESS);
}
