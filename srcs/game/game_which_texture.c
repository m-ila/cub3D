/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_which_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:53:48 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/10 15:55:17 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_compass	ft_which_wall_down(t_segment *seg)
{
	if (seg->angle > 180 && seg->angle < 270)
	{
		if ((seg->until.x % TILE_SIZE == 0 || seg->until.x % TILE_SIZE == 64) \
		&& (seg->until.y % TILE_SIZE != 0 && seg->until.y % TILE_SIZE != 64))
			return (WE);
		return (SO);
	}
	else if (seg->angle > 270 && seg->angle < 360)
	{
		if ((seg->until.x % TILE_SIZE == 0 || seg->until.x % TILE_SIZE == 64) \
		&& (seg->until.y % TILE_SIZE != 0 && seg->until.y % TILE_SIZE != 64))
			return (EA);
		return (SO);
	}
	return (ERR);
}

static t_compass	ft_which_wall_up(t_segment *seg)
{
	if (seg->angle > 0 && seg->angle < 90)
	{
		if ((seg->until.x % TILE_SIZE == 0 || seg->until.x % TILE_SIZE == 64) \
		&& (seg->until.y % TILE_SIZE != 0 && seg->until.y % TILE_SIZE != 64))
			return (EA);
		return (NO);
	}
	else if (seg->angle > 90 && seg->angle < 180)
	{
		if ((seg->until.x % TILE_SIZE == 0 || seg->until.x % TILE_SIZE == 64) \
		&& (seg->until.y % TILE_SIZE != 0 && seg->until.y % TILE_SIZE != 64))
			return (WE);
		return (NO);
	}
	return (ERR);
}

t_compass	ft_get_which_wall(t_segment *seg)
{
	if (seg->angle == 0 || seg->angle == 360)
		return (EA);
	else if (seg->angle == 90)
		return (NO);
	else if (seg->angle == 180)
		return (WE);
	else if (seg->angle == 270)
		return (SO);
	else if (seg->angle > 0 && seg->angle < 180)
		return (ft_which_wall_up(seg));
	else if (seg->angle > 180 && seg->angle < 360)
		return (ft_which_wall_down(seg));
	return (ERR);
}
