/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_null.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/08 18:37:00 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_array_set_null(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		arr[i] = NULL;
		i++;
	}
}

void	ft_color_set_null(t_rgb *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void	ft_init_null(t_data *cub)
{
	t_map	*ma;

	ma = ft_calloc(1, sizeof(t_map));
	ma->x_size_max = 0;
	ma->y_size_max = 0;
	ma->x_size_playable = 0;
	ma->y_size_playable = 0;
	ma->x_from = 0;
	ma->y_from = 0;
	ma->x_until = 0;
	ma->y_until = 0;
	ma->spawn_nb = 0;
	ma->spawn_angle = '\0';
	ma->spawn.x = -1;
	ma->spawn.y = -1;
	ma->map_cpy = NULL;
	ma->raw_map = NULL;
	cub->map = ma;
	cub->position.x = -1;
	cub->position.y = -1;
	ft_array_set_null(cub->path_texture, 5);
	cub->tmp_line = NULL;
	cub->mlx_ptr = NULL;
	cub->win_2d = NULL;
		cub->win_3d = NULL;

	cub->tmp_fd = -1;
	cub->end = false;
	cub->angle = 0;
	ft_color_set_null(&cub->ceiling_c);
	ft_color_set_null(&cub->floor_c);
}
