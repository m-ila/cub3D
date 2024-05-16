/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_which_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:53:48 by mbruyant          #+#    #+#             */

/*   Updated: 2024/05/12 13:51:40 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_compass	ft_which_wall_down(t_segment *seg, double angle)
{
	if (angle > 180.0 && angle < 270.0)
	{
		if (seg->horizontal_hit)
			return (WE);
		return (SO);
	}
	else if (angle > 270.0 && angle < 360.0)
	{
		if (seg->horizontal_hit)
			return (EA);
		return (SO);
	}
	return (ERR);
}

static t_compass	ft_which_wall_up(t_segment *seg, double angle)
{
	if (angle > 0.0 && angle < 90.0)
	{
		if (seg->horizontal_hit)
			return (EA);
		return (NO);
	}
	else if (angle > 90.0 && angle < 180.0)
	{
		if (seg->horizontal_hit)
			return (WE);
		return (NO);
	}
	return (ERR);
}

t_compass	ft_get_which_wall(t_segment *seg, double angle)
{
	if (angle == 0.0 || angle == 360.0)
		return (EA);
	else if (angle == 90.0)
		return (NO);
	else if (angle == 180.0)
		return (WE);
	else if (angle == 270.0)
		return (SO);
	else if (angle > 0.0 && angle < 180.0)
		return (ft_which_wall_up(seg, angle));
	else if (angle > 180.0 && angle < 360.0)
		return (ft_which_wall_down(seg, angle));
	return (ERR);
}
