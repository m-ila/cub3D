/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_which_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:53:48 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/12 16:17:18 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	ft_is_corner(t_point until)
{
	return ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == TILE_SIZE - 1) \
		&& (until.y % TILE_SIZE == 0 || until.y % TILE_SIZE == TILE_SIZE - 1));
}

static t_compass	ft_corners(t_segment *seg, t_point until)
{
	if ((until.x % TILE_SIZE == 0 && until.y % TILE_SIZE == 0))
	{
		if (seg->vertical_hit)
			return (SO);
		return (EA);
	}
	else if ((until.x % TILE_SIZE == 0 && until.y % TILE_SIZE == TILE_SIZE - 1))
	{
		if (seg->vertical_hit)
			return (NO);
		return (EA);
	}
	else if ((until.x % TILE_SIZE == TILE_SIZE - 1 && until.y % TILE_SIZE == 0))
	{
		if (seg->horizontal_hit)
			return (WE);
		return (SO);
	}
	else if ((until.x % TILE_SIZE == TILE_SIZE - 1 && until.y % TILE_SIZE == TILE_SIZE - 1))
	{
		if (seg->horizontal_hit)
			return (WE);
		return (NO);
	}
	return (ERR);
}

static t_compass	ft_which_wall_down(t_segment *seg, double angle, t_point until)
{
	if (seg->vertical_hit)
		return (SO);
	if (angle > 180 && angle < 270)
	{	
		if (ft_is_corner(until))
			return (ft_corners(seg, until));
		return (WE);
	}
	else if (angle > 270 && angle < 360)
	{
		if (ft_is_corner(until))
			return (ft_corners(seg, until));
		return (EA);
	}
	return (ERR);
}

static t_compass	ft_which_wall_up(t_segment *seg, double angle, t_point until)
{
	if (seg->vertical_hit)
		return (NO);
	if (angle > 0 && angle < 90)
	{
		if (ft_is_corner(until))
			return (ft_corners(seg, until));
		return (EA);
	}
	else if (angle > 90 && angle < 180)
	{
		if (ft_is_corner(until))
			return (ft_corners(seg, until));
		return (WE);
	}
	return (ERR);
}

t_compass	ft_get_which_wall(t_segment *seg, double angle, t_point until)
{
	if (angle == 0 || angle == 360)
		return (EA);
	else if (angle == 90)
		return (NO);
	else if (angle == 180)
		return (WE);
	else if (angle == 270)
		return (SO);
	else if (angle > 0 && angle < 180 && until.y)
		return (ft_which_wall_up(seg, angle, until));
	else if (angle > 180 && angle < 360 && until.y)
		return (ft_which_wall_down(seg, angle, until));
	return (ERR);
}
