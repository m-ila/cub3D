/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:36:34 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/24 19:51:56 by mbruyant         ###   ########.fr       */
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
	if (m->raw_map)
		ft_free_2d_array(m->raw_map);
	if (m->map_cpy)
		ft_free_2d_array(m->map_cpy);
	if (m)
		free(m);
}
