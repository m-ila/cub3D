/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_multi_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:50:40 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/09 19:02:34 by mbruyant         ###   ########.fr       */
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
		cub->seg[i + 44] = ft_segment(cub, ft_norm_angle(cub->angle + i));
		if (i == -44 || i == 0 || i == 45)
			printf("Angle : %f\nWall hit : %d\n\n", cub->seg[i + 44].angle, cub->seg[i + 44].direction);
		if (cub->seg[i + 44].angle == 90 || cub->seg[i + 44].angle == 270)
			printf("Angle : %f\nlen : %f\nlen_h : %f\n", cub->seg[i + 44].angle, cub->seg[i + 44].slope_len, cub->seg[i + 44].horizontal_hit);
		i++;
	}
}

void	ft_print_all_rays(t_data *cub)
{
	int	i;

	i = 0;
	while (i < 91)
	{
		if (i == 0)
			ft_draw_angle_seg(cub, cub->seg[i], C_RED);
		else if (i == 45)
			ft_draw_angle_seg(cub, cub->seg[i], C_YELLOW);
		else if (i == 89)
			ft_draw_angle_seg(cub, cub->seg[i], C_GREY);
		i++;
	}
}

void	ft_free_rays(t_data *cub)
{
	if (cub->seg)
		free(cub->seg);
}
