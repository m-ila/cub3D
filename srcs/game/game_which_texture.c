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

static bool	ft_is_corner(t_point_d until)
{
	return (((int) until.x % TILE_SIZE == 0 ||(int) until.x % TILE_SIZE == TILE_SIZE - 1) \
		&& ((int) until.y % TILE_SIZE == 0 || (int) until.y % TILE_SIZE == TILE_SIZE - 1));
}


static t_compass	ft_corners(t_segment *seg)
{
	if (seg->angle > 0 && seg->angle < 180)
	{
		if (seg->vertical_hit)
			return (NO);
		if (seg->angle >= 90)
			return (WE);
		return (EA);
	}
	else if (seg->vertical_hit)
		return (SO);
	else if (seg->angle > 270 && seg->angle < 360)
		return (EA);
	return (WE);
}

static t_compass	ft_which_wall_down(t_segment *seg, double angle, t_point_d until)
{
	if (angle > 180 && angle < 270)
	{
		if (ft_is_corner(until))
			return (ft_corners(seg));
		if (seg->horizontal_hit)
			return (WE);
		return (SO);
	}
	else if (angle > 270 && angle < 360)
	{
		if (ft_is_corner(until))
			return (ft_corners(seg));
		if (seg->horizontal_hit)
			return (EA);
		return (SO);
	}
	return (ERR);
}

static t_compass	ft_which_wall_up(t_segment *seg, double angle, t_point_d until)
{
	if (angle > 0 && angle < 90)
	{
		if (ft_is_corner(until))
			return (ft_corners(seg));
		if (seg->horizontal_hit)
			return (EA);
		return (NO);
	}
	else if (angle > 90 && angle < 180)
	{
		if (ft_is_corner(until))
			return (ft_corners(seg));
		if (seg->horizontal_hit)
			return (WE);
		return (NO);
	}
	return (ERR);
}

t_compass	ft_get_which_wall(t_segment *seg, double angle, t_point_d until)
{
	if (angle == 0 || angle == 360)
		return (EA);
	else if (angle == 90)
		return (NO);
	else if (angle == 180)
		return (WE);
	else if (angle == 270)
		return (SO);
	else if (angle > 0 && angle < 180)
		return (ft_which_wall_up(seg, angle, until));
	else if (angle > 180 && angle < 360)
		return (ft_which_wall_down(seg, angle, until));
	return (ERR);
}
