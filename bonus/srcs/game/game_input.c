/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:42:26 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 17:15:06 by yuewang          ###   ########.fr       */
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

int	is_position_valid(t_data *cub, t_point_d new)
{
	int		map_x;
	int		map_y;
	int		i;
	double	check_points[4][2];

	check_points[0][0] = new.x - PLAYER_RADIUS;
	check_points[0][1] = new.y - PLAYER_RADIUS;
	check_points[1][0] = new.x + PLAYER_RADIUS;
	check_points[1][1] = new.y - PLAYER_RADIUS;
	check_points[2][0] = new.x - PLAYER_RADIUS;
	check_points[2][1] = new.y + PLAYER_RADIUS;
	check_points[3][0] = new.x + PLAYER_RADIUS;
	check_points[3][1] = new.y + PLAYER_RADIUS;
	i = -1;
	while (++i < 4)
	{
		map_x = (int)(check_points[i][0]) / TILE_SIZE;
		map_y = (int)(check_points[i][1]) / TILE_SIZE;
		if (map_y < 0 || (size_t)map_y >= cub->map->y_size_max || \
			map_x < 0 || map_x >= (int)ft_strlen(cub->map->raw_map[map_y]) \
			|| cub->map->raw_map[map_y][map_x] == '1')
			return (0);
	}
	return (1);
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
	if (is_position_valid(cub, new))
	{
		update_player_position(cub, old, new);
		cub->position = new;
		ft_seg_refresh(cub);
	}
}

void	move_player2(t_data *cub, int keycode)
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
	if ((int)new.y / TILE_SIZE > 0 && (int) new.y / TILE_SIZE < \
	(int) cub->map->y_size_max && (int)new.x / TILE_SIZE > 0 && \
	(int) new.x / TILE_SIZE < \
	(int) ft_strlen(cub->map->raw_map[(int)new.y / TILE_SIZE]) && \
	cub->map->raw_map[(int)new.y / TILE_SIZE][(int)new.x / TILE_SIZE] != '1')
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
