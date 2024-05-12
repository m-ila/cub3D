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

static bool	ft_is_corner(t_point until)
{
	return ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == TILE_SIZE - 1) \
		&& (until.y % TILE_SIZE == 0 || until.y % TILE_SIZE == TILE_SIZE - 1));
}


static t_compass	ft_corners(double angle, t_point from, t_point until)
{
	if (from.y && angle && (until.x % TILE_SIZE == 0 && until.y % TILE_SIZE == TILE_SIZE - 1))
		return (NO);
	if ((until.x % TILE_SIZE == 0 && until.y % TILE_SIZE == 0))
	{
		if (angle <= 90)
			return (SO);
		return (EA);
	}
	if ((until.x % TILE_SIZE == 0 && until.y % TILE_SIZE == TILE_SIZE - 1))
	{
		if (angle >= 270 && angle <= 360)
			return (NO);
		return (EA);
	}
	return (NO);
}

static t_compass	ft_which_wall_down(double angle, t_point from, t_point until)
{
	if (angle > 180 && angle < 270)
	{
		if ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == TILE_SIZE - 1) \
		&& (until.y % TILE_SIZE != 0 && until.y % TILE_SIZE != TILE_SIZE - 1))
			return (WE);
		if (ft_is_corner(until))
			return (ft_corners(angle, from, until));
		return (SO);
	}
	else if (angle > 270 && angle < 360)
	{
		if ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == TILE_SIZE - 1) \
		&& (until.y % TILE_SIZE != 0 && until.y % TILE_SIZE != TILE_SIZE - 1))
			return (EA);
		if (ft_is_corner(until))

			return (ft_corners(angle, from, until));

		return (SO);
	}
	return (ERR);
}

static t_compass	ft_which_wall_up(double angle, t_point from, t_point until)
{
	if (angle > 0 && angle < 90)
	{
		if ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == TILE_SIZE - 1) \
		&& (until.y % TILE_SIZE != 0 && until.y % TILE_SIZE != TILE_SIZE - 1))
			return (EA);
		if (ft_is_corner(until))
			return (ft_corners(angle, from, until));
		return (NO);
	}
	else if (angle > 90 && angle < 180)
	{
		if ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == TILE_SIZE - 1) \
		&& (until.y % TILE_SIZE != 0 && until.y % TILE_SIZE != TILE_SIZE - 1))
			return (WE);
		if (ft_is_corner(until))

			return (ft_corners(angle, from, until));
		return (NO);
	}
	return (ERR);
}

t_compass	ft_get_which_wall(double angle, t_point from, t_point until)
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
		return (ft_which_wall_up(angle, from, until));
	else if (angle > 180 && angle < 360)
		return (ft_which_wall_down(angle, from, until));
	return (ERR);
}
