/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_null.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/24 19:48:13 by mbruyant         ###   ########.fr       */
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
	ma->map_cpy = NULL;
	ma->raw_map = NULL;
	cub->map = ma;
	cub->position = NULL;
	ft_array_set_null(cub->path_texture, 5);
	cub->tmp_line = NULL;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->tmp_fd = -1;
	ft_color_set_null(&cub->ceiling_c);
	ft_color_set_null(&cub->floor_c);
}
