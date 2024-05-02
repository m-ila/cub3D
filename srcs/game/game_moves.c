/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:54:29 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/02 17:30:00 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_up(t_data *cub, t_point *new)
{
	double	dx;
	double	dy;

	dx = INCR_STEP * cos(ft_deg_to_rad(cub->angle));
	dy = INCR_STEP * sin(ft_deg_to_rad(cub->angle));
	new->x = cub->position.x + round(dx);
	new->y = cub->position.y + round(dy);
}

void	ft_down(t_data *cub, t_point *new)
{
	double	dx;
	double	dy;

	dx = INCR_STEP * cos(ft_deg_to_rad(cub->angle));
	dy = INCR_STEP * sin(ft_deg_to_rad(cub->angle));
	new->x = cub->position.x - round(dx);
	new->y = cub->position.y - round(dy);
}

void	ft_left(t_data *cub, t_point *new)
{
	double	dx;
	double	dy;
	double	tmp_angle;

	tmp_angle = cub->angle - 90;
	if (tmp_angle < 0)
		tmp_angle += 360;
	dx = INCR_STEP * cos(ft_deg_to_rad(tmp_angle));
	dy = INCR_STEP * sin(ft_deg_to_rad(tmp_angle));
	new->x = cub->position.x + round(dx);
	new->y = cub->position.y + round(dy);
}

void	ft_right(t_data *cub, t_point *new)
{
	double	dx;
	double	dy;
	double	tmp_angle;

	tmp_angle = cub->angle + 90;
	if (tmp_angle > 360)
		tmp_angle -= 360;
	dx = INCR_STEP * cos(ft_deg_to_rad(tmp_angle));
	dy = INCR_STEP * sin(ft_deg_to_rad(tmp_angle));
	new->x = cub->position.x + round(dx);
	new->y = cub->position.y + round(dy);
}
