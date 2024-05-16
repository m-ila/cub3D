/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_coord_hor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:41:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/16 10:34:25 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	ft_pos_y_inc(t_point_d pos, t_point_d d, double angle)
{
	if (ft_facing_up(angle))
		return (pos.y - d.y);
	return (pos.y + d.y);
}

double	ft_get_dx_hrz(double angle)
{
	if (angle <= 90.0)
		return (TILE_SIZE * tan(ft_deg_to_rad(90.0 - angle)));
	else if (angle > 90.0 && angle < 180.0)
		return (TILE_SIZE * tan(ft_deg_to_rad(angle - 90.0)));
	else if (angle < 270.0)
		return (TILE_SIZE * tan(ft_deg_to_rad(270.0 - angle)));
	return (TILE_SIZE * tan(ft_deg_to_rad(angle - 270.0)));
}

double	ft_get_y_hrz(t_point_d from, double angle)
{
	if (ft_facing_up(angle))
		return ((floor(from.y / TILE_SIZE) * TILE_SIZE) - 0.00001);
	return ((floor(from.y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE);
}

double	ft_get_x_hrz(t_point_d from, t_point_d pos, double angle)
{
	if (angle < 90.0)
		return (from.x + ((from.y - pos.y) * tan(ft_deg_to_rad(90.0 - angle))));
	else if (angle < 180.0)
		return (from.x - ((from.y - pos.y) * tan(ft_deg_to_rad(angle - 90.0))));
	else if (angle < 270.0)
		return (from.x - ((pos.y - from.y) * tan(ft_deg_to_rad(270.0 - angle))));
	return (from.x + ((pos.y - from.y) * tan(ft_deg_to_rad(angle - 270.0))));
}
