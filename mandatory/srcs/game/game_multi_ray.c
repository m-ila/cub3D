/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_multi_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:50:40 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/28 21:06:24 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
		ind += 1.0;
	}
}

void	ft_free_rays(t_data *cub)
{
	if (cub->seg)
		free(cub->seg);
}
