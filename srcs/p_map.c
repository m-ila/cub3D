/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:08:24 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/29 17:25:46 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_find_end_line(char *str)
{
	size_t	from;
	size_t	len;

	if (!str)
		return (-1);
	len = (int) ft_strlen(str);
	from = len / 2;
	if (ft_has_only_after(str, from, ft_bool_endline))
		from = 0;
	while (from < len && !ft_has_only_after(str, from, ft_bool_endline))
		from++;
	return (from);
}

bool	ft_parse_line_p_line(t_map *map)
{
	size_t	j;
	size_t	from;
	int		until;

	j = map->y_from;
	map->x_from = ft_strlen(map->map_cpy[j]);
	from = 0;
	until = 0;
	while (j <= map->y_until)
	{
		from = ft_strlen_unbase(map->map_cpy[j], B_WHITESPACE, 0);
		until = ft_find_end_line(map->map_cpy[j]);
		if (from == ft_strlen(map->map_cpy[j]) || \
		map->map_cpy[j][from] != '1' || until == -1 || \
		(size_t) until == from)
			return (false);
		if (from < map->x_from)
			map->x_from = from;
		if ((size_t) until > map->x_until)
			map->x_until = until;
		j++;
	}
	return (true);
}

bool	ft_parse_flood_fill(t_map *map)
{
	int	j;

	if (!map || !map->raw_map || !map->map_cpy)
		return (false);
	j = 0;
	while (map->map_cpy[j] && !ft_strocc(map->map_cpy[j], 'V'))
		j++;
	map->y_from = j;
	while (map->map_cpy[j + 1] && ft_strocc(map->map_cpy[j + 1], 'V'))
		j++;
	map->y_until = j;
	if (map->y_from == 0 || map->y_until == (size_t) ft_2d_lines(map->map_cpy))
		return (false);
	ft_parse_line_p_line(map);
	return (true);
}

/* if char only has whitespace after has to be a 1 */
void	ft_flood_fill(t_point *position, t_map *map)
{
	if (!map || !map->raw_map || !map->map_cpy || \
	position->x < 0 || position->y < 0 \
	|| position->y >= ft_2d_lines(map->raw_map) || \
	position->x >= (int) ft_strlen(map->raw_map[position->y]) || \
	map->raw_map[position->y][position->x] == '1' || \
	ft_iswhitespace(map->raw_map[position->y][position->x]) || \
	ft_char_in_base(map->map_cpy[position->y][position->x], "V\n\0")) 
		return ;
	map->map_cpy[position->y][position->x] = 'V';
	ft_flood_fill(&(t_point){(position->x - 1), position->y}, map);
	ft_flood_fill(&(t_point){(position->x + 1), position->y}, map);
	ft_flood_fill(&(t_point){position->x, (position->y - 1)}, map);
	ft_flood_fill(&(t_point){position->x, (position->y + 1)}, map);
}
