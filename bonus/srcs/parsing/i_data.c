/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 13:21:46 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_compass	ft_which_text(char *str)
{
	if (!ft_strncmp("NO", str, ft_strlen(str) + 1))
		return (NO);
	if (!ft_strncmp("SO", str, ft_strlen(str) + 1))
		return (SO);
	if (!ft_strncmp("WE", str, ft_strlen(str) + 1))
		return (WE);
	if (!ft_strncmp("EA", str, ft_strlen(str) + 1))
		return (EA);
	return (ERR);
}

bool	ft_phase_one(t_data *cub, char **line)
{
	char	**arr;

	arr = ft_split_base(*line, " \n");
	if (!arr)
		return (ft_free_map(cub->map), ft_safe_free(&(cub->tmp_line)), \
		ft_err_ret("split error", NULL, false));
	if (ft_is_text(arr[0]) && ft_2d_lines(arr) == 2)
		cub->path_texture[ft_which_text(arr[0])] = ft_strdup(arr[1]);
	if (ft_is_text(arr[0]) && ft_2d_lines(arr) != 2)
		return (ft_free_2d_array(arr), ft_safe_free(&(cub->tmp_line)), \
		ft_free_map(cub->map), ft_err_ret(E_PATH, NULL, false));
	if (ft_is_color(arr[0]) && !ft_process_color(cub, arr))
		return (ft_free_2d_array(arr), ft_safe_free(&(cub->tmp_line)), \
		ft_free_map(cub->map), \
					ft_err_ret("color in file not valid", NULL, false));
	ft_free_2d_array(arr);
	return (true);
}

bool	ft_process_phase(t_data *cub, int phase, char **line)
{
	if (phase == 1)
		return (ft_phase_one(cub, line));
	if (phase == 2)
	{
		if (!cub->map->raw_map)
		{
			cub->map->raw_map = ft_calloc(1, sizeof(char *));
			if (!cub->map->raw_map)
				return (ft_err_ret("malloc error raw_map", NULL, false));
		}
		if (cub->map->raw_map)
		{
			if (ft_strocc_unbase(*line, ALLOWED_BASE))
				return (ft_free_map(cub->map), ft_safe_free(&(cub->tmp_line)), \
				ft_err_ret("map with unhautorized char", NULL, false));
			if (!ft_add_line_to_arr(&cub->map->raw_map, line))
				return (ft_free_map(cub->map), ft_safe_free(&(cub->tmp_line)), \
				ft_err_ret("map malloc", NULL, false));
		}
	}
	return (true);
}

bool	ft_final_check(t_data *cub)
{
	int	i;
	int	tmp_op;

	i = 0;
	tmp_op = -1;
	while (i < 4)
	{
		if (cub->path_texture[i] == NULL)
			return (ft_free_map(cub->map), \
					ft_err_ret("missing path texture", NULL, false));
		tmp_op = open(cub->path_texture[i], O_RDONLY);
		if (tmp_op == -1)
			return (ft_free_map(cub->map), \
					ft_err_ret("cannot open", cub->path_texture[i], false));
		ft_close_fd(&tmp_op);
		i++;
	}
	if (cub->floor_c.r == -1 || cub->floor_c.g == -1 || cub->floor_c.b == -1 || \
	cub->ceiling_c.r == -1 || cub->ceiling_c.g == -1 || cub->ceiling_c.b == -1)
		return (ft_free_map(cub->map), \
			ft_err_ret("color not initialized", cub->path_texture[i], false));
	return (true);
}

bool	ft_init_struct(t_data *cub, char *path_file)
{
	if (!cub || !path_file)
		return (false);
	ft_init_null(cub);
	if (!ft_open_file(cub, path_file))
		return (false);
	if (!ft_process_file(cub))
		return (ft_emb_free(1, cub));
	if (!ft_get_data_map(cub->map))
		return (ft_emb_free(2, cub));
	cub->map->map_cpy = ft_copy_2d_array(cub->map->raw_map, 0, \
	ft_2d_lines(cub->map->raw_map));
	if (cub->map && cub->map->map_cpy)
	{
		ft_flood_fill(&cub->map->spawn, cub->map);
		if (!ft_parse_flood_fill(cub->map))
			return (ft_emb_free(3, cub));
	}
	return (ft_final_check(cub));
}
