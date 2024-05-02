/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:15:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/02 17:02:05 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_get_starting_angle(t_data *cub)
{
	if (cub->map->spawn_angle == 'N')
		cub->angle = 270;
	if (cub->map->spawn_angle == 'S')
		cub->angle = 90;
	if (cub->map->spawn_angle == 'E')
		cub->angle = 0;
	if (cub->map->spawn_angle == 'W')
		cub->angle = 180;
}

/*
i starts at 4 so the angle ray doesn't go over the player
*/
void	ft_draw_angle(t_data *cub, t_point *pos, double angle, int color)
{
	double	dx;
	double	dy;
	int		x;
	int		y;
	int		i;

	dx = cos(ft_deg_to_rad(angle));
	dy = sin(ft_deg_to_rad(angle));
	i = 4;
	while (i < 15)
	{
		x = pos->x + round(i * dx);
		y = pos->y + round(i * dy);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, x, y, color);
		i++;
	}
}

void	ft_handle_angle(t_data *cub, int keycode)
{
	if (keycode == LEFT_ARROW || keycode == CLIC)
		cub->angle -= INCR_DEG;
	if (keycode == RIGHT_ARROW || keycode == R_CLIC)
		cub->angle += INCR_DEG;
	if (cub->angle < 0)
		cub->angle += 360;
	else if (cub->angle > 360)
		cub->angle -= 360;
}
