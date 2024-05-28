/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_angle_math.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:12:02 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/09 13:53:51 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	ft_deg_to_rad(double deg)
{
	return ((deg * PI) / 180.0);
}

double	ft_norm_angle(double angle)
{
	if (angle > 360)
		return (angle - 360.0);
	if (angle < 0)
		return (angle + 360.0);
	return (angle);
}

double	ft_abs(double val)
{
	if (val < 0)
		return (-val);
	return (val);
}
