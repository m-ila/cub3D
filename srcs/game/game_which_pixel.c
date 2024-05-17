/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_which_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:59:53 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 12:24:05 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_get_x_offset(t_data *cub, t_segment *seg, t_img_mlx *img)
{
	int		offset;
	t_point	pt;

	pt.y = (int) seg->from.y / TILE_SIZE;
	pt.x = (int) seg->from.x / TILE_SIZE;
	if (cub->map->raw_map[pt.y][pt.x] == '1')
		return (-1);
	if (seg->horizontal_hit)
		offset = ((int) seg->until.y % TILE_SIZE) * img->width / TILE_SIZE;
	else
		offset = ((int) seg->until.x % TILE_SIZE) * img->width / TILE_SIZE;
	if (offset >= img->width)
		offset = img->width - 1;
	if (seg->direction == WE || seg->direction == SO)
		return (TILE_SIZE - offset - 1);
	return (offset);
}

int	ft_get_y_offset(t_data *cub, t_segment *seg, t_img_mlx *img, int i)
{
	int		offset;
	t_point	pt;

	pt.y = (int) seg->from.y / TILE_SIZE;
	pt.x = (int) seg->from.x / TILE_SIZE;
	if (cub->map->raw_map[pt.y][pt.x] == '1')
		return (-1);
	offset = (i + ((seg->wall_height / 2) - (W_HEIGHT / 2))) * \
	(img->height / seg->wall_height);
	if (offset < 0)
		offset = 0;
	if (offset >= img->height)
		offset = img->height - 1;
	return (offset);
}

int	ft_get_pixel(t_data *cub, t_segment *seg, int i)
{
	t_point_d	pix;
	int			color;
	int			offset;

	pix.x = ft_get_x_offset(cub, seg, cub->imgs[seg->direction]);
	pix.y = ft_get_y_offset(cub, seg, cub->imgs[seg->direction], i);
	offset = pix.x * (cub->imgs[seg->direction]->bpp / 8) + \
	pix.y * cub->imgs[seg->direction]->s_line;
	if (offset >= 0 && offset < cub->imgs[seg->direction]->s_line * \
	cub->imgs[seg->direction]->height)
		color = ((unsigned char) \
		cub->imgs[seg->direction]->adress[offset] << 16) | \
		((unsigned char) cub->imgs[seg->direction]->adress[offset + 1] << 8) | \
		((unsigned char) cub->imgs[seg->direction]->adress[offset + 2]);
	else
		color = C_GREY;
	return (color);
}
