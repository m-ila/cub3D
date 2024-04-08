/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:08:24 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/08 17:14:27 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"



int	ft_flood_fill(t_point *position, t_map *map)
{
	if (position->x < 0 || position->y < 0 \
	|| position->y >= ft_2d_lines(map->raw_map) || \
	position->x >= (int) ft_strlen(map->raw_map[position->y]) || \
	map->raw_map[position->y][position->x] == '1' || \
	ft_iswhitespace(map->raw_map[position->y][position->x]))
		return (0);
	map->map_cpy[position->y][position->x] = 'V';
	ft_flood_fill(&(t_point){(position->x - 1), position->y}, map);
	ft_flood_fill(&(t_point){(position->x + 1), position->y}, map);
	ft_flood_fill(&(t_point){position->x, (position->y - 1)}, map);
	ft_flood_fill(&(t_point){position->x, (position->y + 1)}, map);
	return (1);
}
