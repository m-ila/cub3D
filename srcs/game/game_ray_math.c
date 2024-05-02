/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ray_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:05:45 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/02 20:36:50 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_draw_square(t_data *cub, t_point square)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = square.x * 65;
	start_y = square.y * 65;
	i = 0;
	while (i < 65)
	{
		j = 0;
		while (j < 65)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, start_x + i, start_y + j, C_RED);
			j++;
		}
		i++;
	}
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
    while (cub->map->raw_map[end->y / 65][end->x / 65] != '1') {
        end->x += (dx / 2); // Avance d'une unité dans la direction x
        end->y += (dy / 2); // Avance d'une unité dans la direction y
    }
	printf("2\n");
	end->x /= 65;
	end->y /= 65;
    printf("\nDDA\nAngle : %f\nend->x : %d\nend->y : %d\n", cub->angle, end->x, end->y);
	printf("position.x = %d\nposition.y = %d\n", cub->position.x / 65, cub->position.y / 65);
	ft_draw_square(cub, *end);
}
*/

void	ft_find_point_end_ray(t_data *cub)
{
	t_point end;

	end = cub->position;
	ft_find_end_point(cub, &end);
}

double	ft_len_ray(t_data *cub, t_point *end)
{
	return (sqrt(pow(end->x - cub->position.x, 2) + pow(end->y - cub->position.y, 2)));
}
