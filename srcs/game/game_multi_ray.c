/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_multi_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:50:40 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/09 21:20:53 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* exit à revoir */
void	ft_malloc_rays(t_data *cub)
{
	int	i;

	i = -44;
	cub->seg = ft_calloc(91, sizeof(t_segment));
	if (cub->seg == NULL)
		exit(1);
	while (i <= 45)
	{
		cub->seg[i + 44] = ft_segment(cub, cub->angle + i);
		i++;
	}
}

void	ft_print_all_rays(t_data *cub)
{
	int	i;

	i = 0;
	while (i < 91)
	{
		ft_draw_angle_seg(cub, cub->seg[i], C_RED);
		i++;
	}
}

void	ft_free_rays(t_data *cub)
{
	if (cub->seg)
		free(cub->seg);
}
