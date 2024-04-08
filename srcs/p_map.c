/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:08:24 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/08 16:08:58 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_flood_fill(t_point *position, t_map *map)
{
	if (position->x < 0 || position->y < 0 ||
	position->y >= ft_2d_lines(map->rawMap) || \
	position->x >= (int) ft_strlen(map->rawMap[position->y]))
		return (0);
	map->mapCpy[position->y][position->x] = 'V';
	ft_flood_fill(&(t_point){(position->x - 1), position->y}, map);
	ft_flood_fill(&(t_point){(position->x + 1), position->y}, map);
	ft_flood_fill(&(t_point){position->x, (position->y - 1)}, map);
	ft_flood_fill(&(t_point){position->x, (position->y + 1)}, map);
	return (1);
}
