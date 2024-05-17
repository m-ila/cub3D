/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_multi_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:50:40 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 11:45:08 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_debug(t_data *cub, int i)
{
	char	*str;

	if (cub->seg[i].direction == SO)
		str = "SOUTH";
	if (cub->seg[i].direction == NO)
		str = "NORTH";
	if (cub->seg[i].direction == EA)
		str = "EAST";
	if (cub->seg[i].direction == WE)
		str = "WEST";
	if (cub->seg[i].direction == ERR)
		str = "ERR";
	if (i == 0)
		printf("\n\nAngle RED : %f\nWall hit : %s\n\n", cub->seg[i].angle, str);
	if (i == (W_WIDTH - 1) / (COLUMN_W * 2))
		printf("Angle YELLOW : %f\nWall hit : %s\n\n", cub->seg[i].angle, str);
	if (i == (W_WIDTH - 1) / COLUMN_W)
		printf("Angle GREY : %f\nWall hit : %s\n\n", cub->seg[i].angle, str);
}

void	ft_malloc_rays(t_data *cub)
{
	double	start_angle;
	double	tot;
	double	ind;
	double	angle_incr;

	tot = W_WIDTH / COLUMN_W;
	angle_incr = FOV / tot;
	 if (angle_incr == 0)
	 	angle_incr = 0.5;
	start_angle = ft_norm_angle(cub->angle - (FOV / 2));
	ind = 0;
	cub->seg = ft_calloc(tot + 1, sizeof(t_segment));
	if (cub->seg == NULL)
		exit_cleanup(cub);
	while (ind < tot - 1)
	{
		cub->seg[(int) ind] = ft_segment(cub, \
		ft_norm_angle(start_angle + (ind * angle_incr)));
		print_debug(cub, ind);
		ind += 1.0;
	}
}

void	ft_print_all_rays(t_data *cub)
{
	int	i;

	i = 0;
	while (i < (W_WIDTH / COLUMN_W) - 1)
	{
		if (i == 0)
			ft_draw_angle_seg(cub, cub->seg[i], C_RED);
		else if (i == (W_WIDTH - 1) / (COLUMN_W * 2))
			ft_draw_angle_seg(cub, cub->seg[i], C_YELLOW);
		else if (i == (W_WIDTH - 2) / COLUMN_W)
			ft_draw_angle_seg(cub, cub->seg[i], C_GREY);
		else
			ft_draw_angle_seg(cub, cub->seg[i], C_CYAN);
		i++;
	}
}

void	ft_free_rays(t_data *cub)
{
	if (cub->seg)
		free(cub->seg);
}
