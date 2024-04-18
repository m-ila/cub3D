/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_null.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/18 13:23:18 by mbruyant         ###   ########.fr       */
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

void	ft_init_null(t_data *cub)
{
	cub->map = NULL;
	cub->position = NULL;
	ft_array_set_null(cub->path_texture, 5);
	cub->ceiling_c = NULL;
	cub->floor_c = NULL;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
}
