/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:36:34 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/28 21:02:57 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_safe_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_free_textures(t_data *cub)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		ft_safe_free(&cub->path_texture[i]);
		i++;
	}
}

void	ft_free_map(t_map *m)
{
	if (!m)
		return ;
	if (m->raw_map)
	{
		ft_free_2d_array(m->raw_map);
		m->raw_map = NULL;
	}
	if (m->map_cpy)
	{
		ft_free_2d_array(m->map_cpy);
		m->map_cpy = NULL;
	}
	if (m)
	{
		free(m);
		m = NULL;
	}
}

void	ft_free_img(t_data *cub)
{
	int	i;

	i = 0;
	if (!cub->imgs)
		return ;
	while (i < 4)
	{
		if (cub->imgs[i])
		{
			if (cub->imgs[i]->img)
				mlx_destroy_image(cub->mlx_ptr, cub->imgs[i]->img);
			free(cub->imgs[i]);
		}
		i++;
	}
	free(cub->imgs);
	cub->imgs = NULL;
}

int	exit_cleanup(t_data *cub)
{
	if (cub->win_3d)
	{
		mlx_destroy_window(cub->mlx_ptr, cub->win_3d);
	}
	ft_free_img(cub);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	ft_free_map(cub->map);
	ft_safe_free(&(cub->tmp_line));
	ft_free_textures(cub);
	ft_close_fd(&(cub->tmp_fd));
	free(cub->seg);
	exit(EXIT_FAILURE);
	return (0);
}
