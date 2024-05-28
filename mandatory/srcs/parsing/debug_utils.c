/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:17:15 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 12:57:50 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_display_2d(char **arr)
{
	int	i;

	i = 0;
	if (arr && *arr)
	{
		while (arr[i])
		{
			ft_printf_fd(1, "arr[%d] : %s\n", i, arr[i]);
			i++;
		}
	}
}
