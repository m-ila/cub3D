/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:19:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 10:19:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* needs to add malloc strdup prot */
void	ft_add_line_to_arr(char ***arr, char **line)
{
	char	**cpy;
	int		i;
	int		len;

	len = ft_2d_lines(*arr);
	cpy = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (i < len)
	{
		cpy[i] = ft_strdup((*arr)[i]);
		ft_safe_free(&(*arr)[i]);
		i++;
	}
	cpy[i] = ft_strdup(*line);
	free(*arr);
	*arr = cpy;
}
