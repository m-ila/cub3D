/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_which_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:59:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/11 17:47:56 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_get_pixel(t_data *cub, t_segment *seg, int i)
{
	t_point	pix;
	int		color;
	int		offset;

	pix.x = seg->until.x % TILE_SIZE;
	pix.y = seg->until.y % TILE_SIZE;
	if (seg->horizontal_hit && seg->direction == EA)
		pix.x -= 1;
	if (seg->horizontal_hit && seg->direction == WE)
		pix.x += 1;
	offset = (pix.y * cub->imgs[seg->direction]->width + pix.x) * \
	(pix.y * cub->imgs[seg->direction]->bpp / 8);
	if (offset >= 0 && offset < cub->imgs[seg->direction]->s_line * cub->imgs[seg->direction]->height)
		color = ((unsigned char) cub->imgs[seg->direction]->adress[offset] << 16) |\
	 ((unsigned char) cub->imgs[seg->direction]->adress[offset + 1] << 8) | \
	 ((unsigned char) cub->imgs[seg->direction]->adress[offset + 2]);
	else
		color = C_BROWN;
	if (i)
		return (color);
	return (color);
}
