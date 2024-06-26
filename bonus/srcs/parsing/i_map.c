/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:04:28 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/16 14:57:00 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	ft_get_data_map(t_map *m)
{
	size_t	i;

	m->y_size_max = (size_t) ft_2d_lines(m->raw_map);
	if (m->y_size_max < 3)
		return (false);
	i = 0;
	while (i < m->y_size_max)
	{
		if (ft_find_end_line(m->raw_map[i]) > (int) m->x_size_max)
			m->x_size_max = ft_find_end_line(m->raw_map[i]);
		m->spawn_nb += ft_strocc_base(m->raw_map[i], B_SPAWN);
		if (m->spawn_nb == 1 && (m->spawn.y == -1))
		{
			m->spawn.y = i;
			m->spawn.x = ft_strindex_base(m->raw_map[i], B_SPAWN);
			m->spawn_angle = m->raw_map[i][m->spawn.x];
		}
		i++;
	}
	if (m->spawn_nb != 1)
		return (false);
	return (true);
}

bool	ft_start_map_condition(char *str)
{
	return ((ft_only_sep_base(str, B_FIRSTLINE)) && (ft_strlen(str) > 1));
}
