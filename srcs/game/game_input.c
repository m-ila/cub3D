/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:42:26 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/12 17:25:11 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_handle_clic(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	if (button == CLIC)
		key_hook(CLIC, param);
	if (button == R_CLIC)
		key_hook(R_CLIC, param);
	return (0);
}
