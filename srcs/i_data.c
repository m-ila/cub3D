/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/29 13:44:09 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_display_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf_fd(1, "arr[%d] : %s\n", i, arr[i]);
		i++;
	}
}

bool	ft_open_file(t_data *cub, char *path_file)
{
	if (!ft_strendswith(path_file, ".cub"))
		return (ft_err_ret("file has to be of .cub extension", NULL, false));
	cub->tmp_fd = open(path_file, O_DIRECTORY);
	if (cub->tmp_fd != -1)
		return (ft_close_fd(&(cub->tmp_fd)), \
		ft_err_ret("has to be a file", path_file, false));
	cub->tmp_fd = open(path_file, O_RDONLY);
	if (cub->tmp_fd == -1)
		return (ft_err_ret("failed to open", path_file, false));
	return (true);
}

t_path_txt	ft_which_text(char *str)
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

/* needs to add malloc strdup prot */
void	ft_add_line_to_arr(char ***arr, char **line)
{
	char	**cpy;
	int		i;
	int		len;

	len = ft_2d_lines(*arr);
	cpy = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (i < len)
	{
		cpy[i] = ft_strdup((*arr)[i]);
		ft_safe_free(&(*arr)[i]);
		i++;
	}
	cpy[i] = ft_strdup(*line);
	free(*arr);
	*arr = cpy;
}

/* split & strdup to protect */
bool	ft_process_phase(t_data *cub, int phase, char **line)
{
	if (phase == 1)
	{
		char	**arr;

		arr = ft_split_base(*line, " \n");
		if (!arr)
			return (ft_safe_free(&(cub->tmp_line)), ft_err_ret("split error", NULL, false));
		//ft_display_2d(arr);
		if (ft_is_text(arr[0]) && ft_2d_lines(arr) == 2)
			cub->path_texture[ft_which_text(arr[0])] = ft_strdup(arr[1]);
		if (ft_is_text(arr[0]) && ft_2d_lines(arr) != 2)
			return (ft_free_2d_array(arr), ft_safe_free(&(cub->tmp_line)), ft_err_ret(E_PATH, NULL, false));
		if (ft_is_color(arr[0]) && !ft_process_color(cub, arr))
			return (ft_free_2d_array(arr), ft_safe_free(&(cub->tmp_line)), ft_err_ret("color in file not valid", NULL, false));
		ft_free_2d_array(arr);
		//ft_safe_free(&(cub->tmp_line));
	}
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
			ft_add_line_to_arr(&cub->map->raw_map, line);
			//return (ft_free_2d_array(cub->map->raw_map), ft_err_ret("map get", NULL, false));
		}
	}
	return (true);
}

/*
LEAK : gnl lorsque temoin == false (????)
laissé message de debug en attendant
*/
bool	ft_process_file(t_data *cub)
{
	bool	temoin;
	int		phase;

	temoin = true;
	phase = 1;
	while (temoin)
	{
		printf("\nNEWLINE\n");
		ft_safe_free(&(cub->tmp_line));
		cub->tmp_line = get_next_line(cub->tmp_fd);
		printf("line = (d1)%s(f1)", cub->tmp_line);
		if (!cub->tmp_line)
			return (ft_safe_free(&(cub->tmp_line)), printf("1 : !cub->tmp_line\n"), true);
		if (ft_start_map_condition(cub->tmp_line))
			phase = 2;
		temoin = ft_process_phase(cub, phase, &cub->tmp_line);
		printf("line = %s", cub->tmp_line);
		ft_safe_free(&(cub->tmp_line));
		//printf("temoin = %d\nphase = %d\n", temoin, phase);
		if (!temoin)
			return (ft_safe_free(&(cub->tmp_line)), printf("2 : !temoin\n"), false);
	}
	return (ft_safe_free(&(cub->tmp_line)), true);
}

/*
mit le free texture
ici en attendant puisque c'est la première partie

si free(cub->map) dans !ft_process_file, va causer pb, faire free map char** d'abord
*/
bool	ft_init_struct(t_data *cub, char *path_file)
{
	if (!cub || !path_file)
		return (false);
	if (ft_strlen(path_file) == 0)
		return (ft_err_ret("enter valid path", NULL, false));
	ft_init_null(cub);
	if (!ft_open_file(cub, path_file))
		return (false);
	printf("opened\nfd = %d\n", cub->tmp_fd);
	if (!ft_process_file(cub))
		return (free(cub->map), ft_safe_free(&(cub->tmp_line)), ft_free_textures(cub), ft_close_fd(&(cub->tmp_fd)), false);
	printf("\nDisplay raw map\n");
	ft_display_2d(cub->map->raw_map);
	if (!ft_get_data_map(cub->map))
		return (ft_free_2d_array(cub->map->raw_map), free(cub->map), ft_safe_free(&(cub->tmp_line)), ft_free_textures(cub), ft_close_fd(&(cub->tmp_fd)), ft_err_ret("wrong data map", NULL, false));
	cub->map->map_cpy = ft_copy_2d_array(cub->map->raw_map, 0, ft_2d_lines(cub->map->raw_map));
	if (cub->map && cub->map->map_cpy)
	{
		ft_flood_fill(&cub->map->spawn, cub->map);
		printf("\nDisplay map flood fill\n");
		ft_display_2d(cub->map->map_cpy);
	}
	ft_close_fd(&(cub->tmp_fd));
	ft_free_textures(cub);
	ft_free_map(cub->map);
	ft_safe_free(&(cub->tmp_line));
	return (true);
}
