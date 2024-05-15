/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ray_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:05:45 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/15 20:29:29 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_seg_refresh(t_data *cub)
{
	int	i;

	i = 0;
	while (i < 91)
	{
		ft_draw_angle_seg(cub, cub->seg[i], C_WHITE);
		i++;
	}
	ft_free_rays(cub);
	ft_malloc_rays(cub);
	ft_print_all_rays(cub);
}

static bool	ft_check_diag_wall(t_data *cub, t_point_d *end)
{
	if (((int) end->x % TILE_SIZE == 0.0 || (int) end->x % TILE_SIZE == TILE_SIZE - 1) && \
		((int) end->y % TILE_SIZE == 0.0 || (int) end->y % TILE_SIZE == TILE_SIZE - 1) && \
		((cub->map->raw_map[(int) end->y / TILE_SIZE][(int) (end->x - 1) / TILE_SIZE] && \
		cub->map->raw_map[(int) end->y / TILE_SIZE][(int) (end->x - 1) / TILE_SIZE] == '1') || \
		(cub->map->raw_map[(int) end->y / TILE_SIZE][(int) (end->x + 1) / TILE_SIZE] && \
		cub->map->raw_map[(int) end->y / TILE_SIZE][(int) (end->x + 1) / TILE_SIZE] == '1')))
		return (true);
	return (false);
}

t_point_d ft_find_end_point(t_data *cub, t_point_d *end, double angle)
{
	t_point_d translate;
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
		if (ft_check_diag_wall(cub, end))
			break ;
        end->x += dx;
		end->y -= dy;
    }
	translate.x = (int) end->x;
	translate.y = (int) end->y;
	return (translate);
}

void	ft_get_hor_vert(t_data *cub, t_segment *seg)
{
	double	hor;
	double	vert;

	hor = ft_hzt_intersections(cub, seg);
	vert = ft_vrt_intersections(cub, seg);
	if (hor > vert)
		seg->horizontal_hit = true;
	if (hor <= vert)
		seg->vertical_hit = true;
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
	static t_point_d	end_d;
	t_point_d 	end;
	t_point		tile_hit;

	end_d.x = (double) cub->position.x;
	end_d.y = (double) cub->position.y;
	seg.horizontal_hit = false;
	seg.vertical_hit = false;
	seg.from = cub->position;
	end = ft_find_end_point(cub, &end_d, angle);
	seg.until = end;
	seg.slope_len = ft_len_ray(seg.from, seg.until);
	seg.angle = angle;
	tile_hit.x = seg.until.x / TILE_SIZE;
	tile_hit.y = seg.until.y / TILE_SIZE;
	seg.tile_hit = tile_hit;
	seg.len_processed = seg.slope_len * \
	cos(ft_deg_to_rad(seg.angle) - ft_deg_to_rad(cub->angle));
	ft_get_hor_vert(cub, &seg);
	seg.direction = ft_get_which_wall(&seg ,seg.angle, seg.until);
	seg.wall_height = (TILE_SIZE * W_WIDTH / 2) / seg.len_processed;
	if (seg.vertical_hit)
		seg.len_debug = ft_vrt_intersections(cub, &seg);
	if (seg.horizontal_hit)
		seg.len_debug = ft_hzt_intersections(cub, &seg);
	return (seg);
}

double	ft_len_ray(t_point_d start, t_point_d end)
{
	return (sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)));
}
