/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:08:24 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 17:10:35 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	ft_space_conditions(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (!str || len == 0)
		return (false);
	if (ft_strendswith(str, "\n"))
		len -= 1;
	while (i < len)
	{
		if (ft_iswhitespace(str[i]))
		{
			if (i > 1 && !ft_char_in_base(str[i - 1], B_WHTZEUN))
				return (false);
			if (i + 1 < len && !ft_char_in_base(str[i + 1], B_WHTZEUN))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	ft_check_adjacent(t_map *map, size_t j, size_t from, int until)
{
	if (j >= 1 && map->map_cpy[j - 1] && \
	ft_find_end_line(map->map_cpy[j - 1]) > until && \
	ft_strocc_delimiters(map->map_cpy[j - 1], "V", until, \
	ft_find_end_line(map->map_cpy[j - 1])))
		return (false);
	if (j >= 1 && map->map_cpy[j - 1] && \
	ft_find_end_line(map->map_cpy[j - 1]) < until && \
	ft_strocc_delimiters(map->map_cpy[j], "V", \
	ft_find_end_line(map->map_cpy[j - 1]), until))
		return (false);
	if (j >= 1 && map->map_cpy[j - 1] && \
	ft_find_start_line(map->map_cpy[j - 1]) > (int) from && \
	ft_strocc_delimiters(map->map_cpy[j], "V", 0, from))
		return (false);
	if (j >= 1 && map->map_cpy[j - 1] && \
	ft_find_start_line(map->map_cpy[j - 1]) < (int) from && \
	ft_strocc_delimiters(map->map_cpy[j - 1], "V", 0, from))
		return (false);
	return (true);
}

/* see readme for more instructions */
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
		from = ft_find_start_line(map->map_cpy[j]);
		until = ft_find_end_line(map->map_cpy[j]);
		if (from == ft_strlen(map->map_cpy[j]) || map->map_cpy[j][from] == 'V' \
		|| until == -1 || (size_t) until == from || \
		map->map_cpy[j][until] == 'V' || !ft_space_conditions(map->map_cpy[j]))
			return (false);
		if (from < map->x_from)
		{
			map->x_from = from;
		}
		if ((size_t) until > map->x_until)
			map->x_until = until;
		if (!ft_check_adjacent(map, j, from, until))
			return (false);
		j++;
	}
	return (true);
}

/* to add : strocc_delimiters */
bool	ft_parse_flood_fill(t_map *map)
{
	int	j;

	if (!map || !map->raw_map || !map->map_cpy || \
	ft_strocc(map->map_cpy[ft_2d_lines(map->map_cpy) - 1], 'V') || \
	ft_strocc(map->map_cpy[0], 'V'))
		return (false);
	j = 0;
	while (map->map_cpy[j] && !ft_strocc(map->map_cpy[j], 'V'))
		j++;
	map->y_from = j;
	while (map->map_cpy[j] && ft_strocc(map->map_cpy[j], 'V'))
		j++;
	map->y_until = j;
	if (map->y_until == (size_t) ft_2d_lines(map->map_cpy))
		return (false);
	if (!ft_parse_line_p_line(map))
		return (false);
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
