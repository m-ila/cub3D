/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_which_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:59:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/11 20:08:46 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_get_x_offset(t_segment *seg, t_img_mlx *img)
{
	int	offset;

	if (seg->horizontal_hit)
		offset = (seg->until.y % TILE_SIZE) * img->width / 64;
	else
		offset = (seg->until.x % TILE_SIZE) * img->width / 64;
	if (offset >= img->width)
		offset = img->width - 1;
	return (offset);
}

int	ft_get_y_offset(t_segment *seg, t_img_mlx *img, int i)
{
	int	offset;

	offset = (i + ((seg->wall_height / 2) - (W_HEIGHT / 2))) * (img->height / seg->wall_height);
	if (offset < 0)
		offset = 0;
	if (offset >= img->height)
		offset = img->height - 1;
	return (offset);
}

int	ft_get_pixel(t_data *cub, t_segment *seg, int i)
{
	t_point	pix;
	int		color;
	int		offset;
	//int		scale;


	pix.x = ft_get_x_offset(seg, cub->imgs[seg->direction]);
	pix.y = ft_get_y_offset(seg, cub->imgs[seg->direction], i);
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
