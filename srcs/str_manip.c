/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:19:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 15:25:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	ft_add_line_to_arr(char ***arr, char **line)
{
	char	**cpy;
	int		i;
	int		len;

	len = ft_2d_lines(*arr);
	cpy = ft_calloc(len + 2, sizeof(char *));
	if (!cpy)
		return (false);
	i = 0;
	while (i < len)
	{
		cpy[i] = ft_strdup((*arr)[i]);
		if (!cpy[i])
			return (ft_free_2d_array(cpy), false);
		ft_safe_free(&(*arr)[i]);
		i++;
	}
	cpy[i] = ft_strdup(*line);
	if (!cpy[i])
		return (ft_free_2d_array(cpy), false);
	free(*arr);
	*arr = cpy;
	return (true);
}
