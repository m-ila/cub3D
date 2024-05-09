/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:36:34 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/09 18:07:27 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_safe_free(char **str)
{
	if (*str)
	{
		printf("about to free : (d)%s(f)\n", *str);
		free(*str);
		*str = NULL;
		if (!(*str))
			printf("line freed\n\n");
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

void exit_cleanup(t_data *cub)
{
    // Clean up resources and exit if window creation fails
    if (cub->win_2d)
        mlx_destroy_window(cub->mlx_ptr, cub->win_2d);
    if (cub->win_3d)
        mlx_destroy_window(cub->mlx_ptr, cub->win_3d);
    if (cub->mlx_ptr) {
        mlx_destroy_display(cub->mlx_ptr);
        free(cub->mlx_ptr);
    }
    ft_free_map(cub->map);
    ft_safe_free(&(cub->tmp_line));
    ft_free_textures(cub);
    ft_close_fd(&(cub->tmp_fd));
	free(cub->seg);
    exit(EXIT_FAILURE);
}

