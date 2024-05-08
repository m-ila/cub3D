/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ray_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:05:45 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/08 09:24:43 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_seg_refresh(t_data *cub)
{
	t_segment	old_seg;

	old_seg = cub->seg;
	ft_draw_angle_seg(cub, old_seg, C_WHITE);
	cub->seg = ft_segment(cub, cub->angle);
	ft_draw_angle_seg(cub, cub->seg, C_RED);
}

t_point ft_find_end_point(t_data *cub, t_point_d *end, double angle)
{
	t_point translate;
    double	dx;
    double	dy;
    double	length;

	dx = cos(ft_deg_to_rad(angle));
	dy = sin(ft_deg_to_rad(angle));
	length = sqrt(dx * dx + dy * dy);
    dx /= length;
    dy /= length;
    while (cub->map->raw_map[(int) end->y / TILE_SIZE][(int) end->x / TILE_SIZE] && \
	cub->map->raw_map[(int) end->y / TILE_SIZE][(int) end->x / TILE_SIZE] != '1')
	{
        end->x += dx;
		end->y -= dy;
    }
	translate.x = (int) end->x;
	translate.y = (int) end->y;
	return (translate);
}

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
	t_point_d	end_d;
	t_point 	end;
	t_point		tile_hit;

	end_d.x = (double) cub->position.x;
	end_d.y = (double) cub->position.y;
	end = ft_find_end_point(cub, &end_d, angle);
	seg.from = cub->position;
	seg.until = end;
	seg.slope_len = ft_len_ray(seg.from, seg.until);
	seg.angle = angle;
	tile_hit.x = seg.until.x / TILE_SIZE;
	tile_hit.y = seg.until.y / TILE_SIZE;
	seg.tile_hit = tile_hit;
	return (seg);
}

double	ft_len_ray(t_point start, t_point end)
{
	return (sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)));
}
