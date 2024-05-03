/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ray_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:05:45 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/03 14:35:46 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_draw_square(t_data *cub, t_point square)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = square.x * TILE_SIZE;
	start_y = square.y * TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, start_x + i, start_y + j, C_RED);
			j++;
		}
		i++;
	}
}

/*
when used, has to put other condition in the loop or else it will be infinite
*/
bool	ft_is_wall(t_data *cub, t_point_d pt)
{
	t_point	translate;

	if (pt.x < 0 || pt.y < 0)
		return (false);
	translate.x = (int) floor(pt.x / TILE_SIZE);
	translate.y = (int) floor(pt.y / TILE_SIZE);
	if (translate.y >= (int) cub->map->y_size_max || translate.x >= (int) ft_strlen(cub->map->raw_map[translate.y]))
		return (false);
	if (cub->map->raw_map[translate.y] && translate.x < (int) ft_strlen(cub->map->raw_map[translate.y]))
		if (cub->map->raw_map[translate.y][translate.x] == '1')
			return (true);
	return (false);
}

/*
check if a point is withing the map without having to deal with TILE_SIZE beforehand
*/
bool	ft_is_within_map(t_data *cub, t_point_d pt)
{
	t_point	translate;
	
	if (pt.x < 0 || pt.y < 0)
		return (false);
	translate.x = (int) floor(pt.x / TILE_SIZE);
	translate.y = (int) floor(pt.y / TILE_SIZE);
	if (translate.y >= (int) cub->map->y_size_max || translate.x >= (int) ft_strlen(cub->map->raw_map[translate.y]))
		return (false);
	return (true);
}

/*
for horizontal intersection only
ensures that the step for the x axe is in the same direction of the angle
*/
void	ft_adjust_step_horizontal(t_data *cub, t_point_d *step)
{
	if ((cub->angle > 90 && cub->angle < 270) && step->x > 0)
		step->x *= -1;
	else if (!(cub->angle > 90 && cub->angle < 270) && step->x < 0)
		step->x *= -1;
}

/*
for vertical intersection only
ensures that the step for the y axe is in the same direction of the angle
*/
void	ft_adjust_step_vertical(t_data *cub, t_point_d *step)
{
	if ((cub->angle > 0 && cub->angle < 180) && step->y < 0)
		step->y *= -1;
	else if (!(cub->angle > 0 && cub->angle < 180) && step->y > 0)
		step->y *= -1;
}

/*
if angle included in ]0,180[, then looking for horizontal in the updward direction
else, must look in the downward direction, so the step.y has to be in the negatives
the variable buffer is here to take into account the current line we're in, depending on
the angle (direction + or -)
*/
double	ft_horizontal_intersection(t_data *cub)
{
	t_point_d	hor;
	t_point_d	step;
	double		buffer;

	if (cub->angle == 0 || cub->angle == 180)
		return (1000000.0);
	step.y = TILE_SIZE;
	step.x = TILE_SIZE / tan(cub->angle);
	hor.y = floor(cub->position.y / TILE_SIZE) * TILE_SIZE;
	if (cub->angle > 0 && cub->angle < 180)
	{
		hor.y += TILE_SIZE;
		buffer = -1;
	}
	else
	{
		step.y *= -1;
		buffer = 1;
	}
	hor.x = cub->position.x + (hor.y - cub->position.y) / tan(cub->angle);
	ft_adjust_step_horizontal(cub, &step);
	while (ft_is_within_map(cub, (t_point_d){hor.x, (hor.y - buffer)}) && \
	!ft_is_wall(cub, (t_point_d){hor.x, (hor.y - buffer)}))
	{
		hor.x += step.x;
		hor.y += step.y;
	}
	return (sqrt((pow(hor.y - cub->position.y, 2.0)) + (pow(hor.x - cub->position.x, 2.0))));
}

double	ft_vertical_intersection(t_data *cub)
{
	t_point_d	ver;
	t_point_d	step;
	double		buffer;

	if (cub->angle == 90 || cub->angle == 270)
		return (1000000.0);
	step.y = TILE_SIZE;
	step.x = TILE_SIZE / tan(cub->angle);
	ver.x = floor(cub->position.y / TILE_SIZE) * TILE_SIZE;
	if (!(cub->angle > 90 && cub->angle < 270))
	{
		ver.x += TILE_SIZE;
		buffer = -1;
	}
	else
	{
		step.x *= -1;
		buffer = 1;
	}
	ver.y = cub->position.y + (ver.x - cub->position.x) / tan(cub->angle);
	ft_adjust_step_vertical(cub, &step);
	while (ft_is_within_map(cub, (t_point_d){(ver.x - buffer), ver.y}) && \
	!ft_is_wall(cub, (t_point_d){(ver.x - buffer), ver.y}))
	{
		ver.x += step.x;
		ver.y += step.y;
	}
	return (sqrt((pow(ver.y - cub->position.y, 2.0)) + (pow(ver.x - cub->position.x, 2.0))));
}

/* NOT OK
void ft_find_end_point(t_data *cub, t_point *end) {
    double dx = cos(ft_deg_to_rad(cub->angle));
    double dy = sin(ft_deg_to_rad(cub->angle));

    // Normalize the direction vector
    double length = sqrt(dx * dx + dy * dy);
    dx /= length;
    dy /= length;

    // DDA loop
	printf("1\n");
    while (cub->map->raw_map[end->y / TILE_SIZE][end->x / TILE_SIZE] != '1') {
        end->x += (dx / 2); // Avance d'une unité dans la direction x
        end->y += (dy / 2); // Avance d'une unité dans la direction y
    }
	printf("2\n");
	end->x /= TILE_SIZE;
	end->y /= TILE_SIZE;
    printf("\nDDA\nAngle : %f\nend->x : %d\nend->y : %d\n", cub->angle, end->x, end->y);
	printf("position.x = %d\nposition.y = %d\n", cub->position.x / TILE_SIZE, cub->position.y / TILE_SIZE);
	ft_draw_square(cub, *end);
}
*/

void	ft_draw_angle_pos(t_data *cub, t_point *pos, double len, int color)
{
	double	dx;
	double	dy;
	int		x;
	int		y;
	double		i;

	dx = cos(ft_deg_to_rad(cub->angle));
	dy = sin(ft_deg_to_rad(cub->angle));
	i = 4.0;
	while (i < len)
	{
		x = pos->x + round(i * dx);
		y = pos->y + round(i * dy);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x, y, color);
		i += 1.0;
	}
}

void	ft_find_point_end_ray(t_data *cub)
{
	double	hor;
	double	vert;
//	t_point end;

//	end = cub->position;
//	ft_find_end_point(cub, &end);
	hor = ft_horizontal_intersection(cub);
	vert = ft_vertical_intersection(cub);
	printf("Angle : %f\nhor : %f\nvert : %f\n\n", cub->angle, hor, vert);
	if (hor < vert)
		ft_draw_angle_pos(cub, &cub->position, hor, C_RED);
	else
		ft_draw_angle_pos(cub, &cub->position, vert, C_RED);
}

double	ft_len_ray(t_data *cub, t_point *end)
{
	return (sqrt(pow(end->x - cub->position.x, 2) + pow(end->y - cub->position.y, 2)));
}
