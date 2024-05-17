/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:32:37 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 16:58:53 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	rgb_to_int(t_rgb color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	ft_game(t_data *cub)
{
	init_mlx(cub);
	init_windows(cub);
	cub->position.x = cub->map->spawn.x * TILE_SIZE + 32;
	cub->position.y = cub->map->spawn.y * TILE_SIZE + 32;
	ft_get_starting_angle(cub);
	ft_malloc_rays(cub);
	render_2d_map(cub);
	render_3d(cub);
	mlx_hook(cub->win_3d, 2, 1L << 0, key_hook, cub);
	mlx_hook(cub->win_3d, 3, 1L << 1, key_hook, cub);
	mlx_mouse_hook(cub->win_3d, ft_handle_clic, cub);
	mlx_loop(cub->mlx_ptr);
}
