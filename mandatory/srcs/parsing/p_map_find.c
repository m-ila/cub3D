/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:05:37 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 15:41:12 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_find_end_line(char *str)
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

int	ft_find_start_line(char *str)
{
	return (ft_strlen_unbase(str, B_WHITESPACE, 0));
}

t_compass	ft_which_text(char *str)
{
	if (!ft_strncmp("NO", str, ft_strlen(str) + 1))
		return (NO);
	if (!ft_strncmp("SO", str, ft_strlen(str) + 1))
		return (SO);
	if (!ft_strncmp("WE", str, ft_strlen(str) + 1))
		return (WE);
	if (!ft_strncmp("EA", str, ft_strlen(str) + 1))
		return (EA);
	return (ERR);
}
