/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:42:26 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 12:07:42 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	update_player_position(t_data *cub, t_point_d old, t_point_d new)
{
	draw_player(cub, old, C_WHITE);
	ft_draw_angle(cub, &old, cub->angle, C_WHITE);
	draw_player(cub, new, C_RED);
	ft_draw_angle(cub, &new, cub->angle, C_RED);
}

void	move_player(t_data *cub, int keycode)
{
	t_point_d	old;
	t_point_d	new;

	old = cub->position;
	new = old;
	if (keycode == UP)
		ft_up(cub, &new);
	else if (keycode == DOWN)
		ft_down(cub, &new);
	else if (keycode == LEFT)
		ft_left(cub, &new);
	else if (keycode == RIGHT)
		ft_right(cub, &new);
	if ((int)new.y / TILE_SIZE >= 0 && (int) new.y / TILE_SIZE < \
	(int) cub->map->y_size_max && (int)new.x / TILE_SIZE >= 0 && \
	(int) new.x / TILE_SIZE < \
	(int) ft_strlen(cub->map->raw_map[(int)new.y / TILE_SIZE]))
	{
		update_player_position(cub, old, new);
		cub->position = new;
		ft_seg_refresh(cub);
	}
}

int	ft_handle_clic(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	if (button == CLIC)
		key_hook(CLIC, param);
	if (button == R_CLIC)
		key_hook(R_CLIC, param);
	return (0);
}
