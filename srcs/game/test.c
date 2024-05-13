/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:56:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/12 17:03:28 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	ft_hor_inter(t_data *cub, t_segment *seg)
{
	t_point_d hor;

	hor.y = (double) floor(seg->from.y / TILE_SIZE) + TILE_SIZE;
	if (!(seg->angle > 0 && seg->angle < 180))
		hor.y = (double) floor(seg->from.y / TILE_SIZE) - 1;
}
