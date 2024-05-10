/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_multi_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:50:40 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/10 13:22:30 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	print_debug(t_data *cub, int i)
{
	char	*str;

	if (cub->seg[i + 44].direction == SO)
		str = "SOUTH";
	if (cub->seg[i + 44].direction == NO)
		str = "NORTH";
	if (cub->seg[i + 44].direction == EA)
		str = "EAST";
	if (cub->seg[i + 44].direction == WE)
		str = "WEST";
	if (cub->seg[i + 44].direction == ERR)
		str = "ERR";
	if (i + 44 == 0)
		printf("\n\nAngle RED : %f\nWall hit : %s\n\n", cub->seg[i + 44].angle, str);
	if (i + 44 == 45)
		printf("Angle YELLOW : %f\nWall hit : %s\n\n", cub->seg[i + 44].angle, str);
	if (i + 44 == 90)
		printf("Angle GREY : %f\nWall hit : %s\n\n", cub->seg[i + 44].angle, str);
}

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
		print_debug(cub, i);
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
		else if (i == 90)
			ft_draw_angle_seg(cub, cub->seg[i], C_GREY);
		i++;
	}
}

void	ft_free_rays(t_data *cub)
{
	if (cub->seg)
		free(cub->seg);
}
