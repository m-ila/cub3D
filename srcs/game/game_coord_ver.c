/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_coord_ver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:41:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 11:34:28 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	ft_get_dy_vrt(double angle)
{
	if (angle <= 90.0)
		return (TILE_SIZE * tan(ft_deg_to_rad(angle)));
	else if (angle > 90.0 && angle < 180.0)
		return (TILE_SIZE * tan(ft_deg_to_rad(ft_norm_angle(180.0 - angle))));
	else if (angle < 270.0)
		return (TILE_SIZE * tan(ft_deg_to_rad(ft_norm_angle(angle - 180.0))));
	return (TILE_SIZE * tan(ft_deg_to_rad(ft_norm_angle(360.0 - angle))));
}

double	ft_get_x_vrt(t_point_d pos, double angle)
{
	if (!ft_pointing_left(angle))
		return ((floor(pos.x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE);
	return ((floor(pos.x / TILE_SIZE) * TILE_SIZE) - 0.00001);
}

double	ft_get_y_vrt(t_point_d from, t_point_d pos, double angle)
{
	if (angle < 90.0)
		return (from.y - ((pos.x - from.x) * tan(ft_deg_to_rad(angle))));
	else if (angle < 180.0)
		return (from.y - ((from.x - pos.x) * \
		tan(ft_deg_to_rad(ft_norm_angle(180.0 - angle)))));
	else if (angle < 270.0)
		return  (from.y + ((from.x - pos.x) * \
		tan(ft_deg_to_rad(ft_norm_angle(angle - 180.0)))));
	return (from.y + ((pos.x - from.x) * \
	tan(ft_deg_to_rad(ft_norm_angle(360.0 - angle)))));
}
