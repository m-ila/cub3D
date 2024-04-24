/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:01:27 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/24 23:01:49 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* check if everything is between 0 and 255 and is only digits */
bool	ft_color_range(char **arr)
{
	int	i;
	int	curr;

	if (!arr || !(*arr))
		return (false);
	i = 0;
	while (i < 3)
	{
		curr = ft_atoi(arr[i]);
		if (curr < 0 || curr > 255 || !ft_only_sep_base(arr[i], B_DIGIT))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_process_color(t_data *cub, char **arr)
{
	char	**parse;
	t_rgb	color;

	if ((ft_strlen(arr[1]) < 5) || (ft_strlen(arr[1]) > 11))
		return (false);
	parse = ft_split(arr[1], ',');
	if (!parse)
		return (false);
	if (ft_2d_lines(parse) != 3 || !ft_color_range(parse))
		return (ft_free_2d_array(parse), false);
	if (!ft_strncmp(arr[0], "F", 2))
		cub->floor_c = color;
	if (!ft_strncmp(arr[0], "C", 2))
		cub->ceiling_c = color;
	color.r = ft_atoi(parse[0]);
	color.g = ft_atoi(parse[1]);
	color.b = ft_atoi(parse[2]);
	ft_free_2d_array(parse);
	return (true);
}
