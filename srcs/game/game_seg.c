/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_seg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:44:23 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 11:45:30 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
BOTH are pixel position
t_point	from
t_point	end

Is a tile position (/ TILE_SIZE), map coordinates
t_point	tile_hit
*/
t_segment	ft_segment(t_data *cub, double angle)
{
	t_segment	seg;
	static t_point_d	end_d;
	t_point_d 	end;
	t_point		tile_hit;

	end_d.x = (double) cub->position.x;
	end_d.y = (double) cub->position.y;
	seg.angle = angle;
	seg.horizontal_hit = false;
	seg.vertical_hit = false;
	seg.from = cub->position;
	seg.hrz_slope = 0.0;
	seg.vrt_slope = 0.0;
	ft_get_hor_vert(cub, &seg);
	end = ft_find_end_point(cub, &end_d, angle);
	seg.until = end;
	tile_hit.x = seg.until.x / TILE_SIZE;
	tile_hit.y = seg.until.y / TILE_SIZE;
	seg.tile_hit = tile_hit;
	seg.len_processed = seg.slope_len * \
	cos(ft_deg_to_rad(seg.angle) - ft_deg_to_rad(cub->angle));
	seg.direction = ft_get_which_wall(&seg ,seg.angle);
	seg.wall_height = (TILE_SIZE * W_WIDTH / 2) / seg.len_processed;
	return (seg);
}

void	ft_seg_refresh(t_data *cub)
{
	int	i;

	i = 0;
	while (i < (W_WIDTH / COLUMN_W) - 1)
	{
		ft_draw_angle_seg(cub, cub->seg[i], C_WHITE);
		i++;
	}
	ft_free_rays(cub);
	ft_malloc_rays(cub);
	ft_print_all_rays(cub);
}
