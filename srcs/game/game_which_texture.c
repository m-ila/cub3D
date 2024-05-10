/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_which_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:53:48 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/10 16:11:56 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_compass	ft_which_wall_down(double angle, t_point until)
{
	if (angle > 180 && angle < 270)
	{
		if ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == 64) \
		&& (until.y % TILE_SIZE != 0 && until.y % TILE_SIZE != 64))
			return (WE);
		return (SO);
	}
	else if (angle > 270 && angle < 360)
	{
		if ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == 64) \
		&& (until.y % TILE_SIZE != 0 && until.y % TILE_SIZE != 64))
			return (EA);
		return (SO);
	}
	return (ERR);
}

static t_compass	ft_which_wall_up(double angle, t_point until)
{
	if (angle > 0 && angle < 90)
	{
		if ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == 64) \
		&& (until.y % TILE_SIZE != 0 && until.y % TILE_SIZE != 64))
			return (EA);
		return (NO);
	}
	else if (angle > 90 && angle < 180)
	{
		if ((until.x % TILE_SIZE == 0 || until.x % TILE_SIZE == 64) \
		&& (until.y % TILE_SIZE != 0 && until.y % TILE_SIZE != 64))
			return (WE);
		return (NO);
	}
	return (ERR);
}

t_compass	ft_get_which_wall(double angle, t_point until)
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
		return (ft_which_wall_up(angle, until));
	else if (angle > 180 && angle < 360)
		return (ft_which_wall_down(angle, until));
	return (ERR);
}
