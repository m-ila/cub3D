/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/24 21:42:51 by mbruyant         ###   ########.fr       */
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

void	ft_close_fd(int *fd)
{
	if (*fd > -1)
	{
		close(*fd);
		*fd = -1;
	}
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

/* check if everything is between 0 and 255 and is only digits */
bool	ft_color_range(char **arr)
{
	int	i;
	int	curr;

	if (!arr || !(*arr))
		return (false);
	i = 0;
	while (i < 3)
	{
		curr = ft_atoi(arr[i]);
		if (curr < 0 || curr > 255 || !ft_only_sep_base(arr[i], B_DIGIT))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_process_color(t_data *cub, char **arr)
{
	char	**parse;
	t_rgb	color;

	if ((ft_strlen(arr[1]) < 5) || (ft_strlen(arr[1]) > 11))
		return (false);
	parse = ft_split(arr[1], ',');
	if (!parse)
		return (false);
	if (ft_2d_lines(parse) != 3 || !ft_color_range(parse))
		return (ft_free_2d_array(parse), false);
	if (!ft_strncmp(arr[0], "F", 2))
		cub->floor_c = color;
	if (!ft_strncmp(arr[0], "C", 2))
		cub->ceiling_c = color;
	color.r = ft_atoi(parse[0]);
	color.g = ft_atoi(parse[1]);
	color.b = ft_atoi(parse[2]);
	ft_free_2d_array(parse);
	return (true);
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
			return (ft_safe_free(&cub->tmp_line), ft_err_ret("split error", NULL, false));
		ft_display_2d(arr);
		if (ft_is_text(arr[0]))
			cub->path_texture[ft_which_text(arr[0])] = ft_strdup(arr[1]);
		if (ft_is_color(arr[0]) && !ft_process_color(cub, arr))
			return (ft_free_2d_array(arr), ft_safe_free(&cub->tmp_line), ft_err_ret("color in file not valid", NULL, false));
		ft_free_2d_array(arr);
	}
	if (phase == 2)
	{
		if (!cub->map->raw_map)
		{
			cub->map->raw_map = ft_calloc(2, sizeof(char *));
			cub->map->raw_map[0] = ft_strdup(*line);
		}
		if (cub->map->raw_map)
		{
			ft_add_line_to_arr(&cub->map->raw_map, line);
			//return (ft_free_2d_array(cub->map->raw_map), ft_err_ret("map get", NULL, false));
		}
	}
	return (true);
}

bool	ft_start_map_condition(char *str)
{
	return ((ft_only_sep_base(str, B_FIRSTLINE)) && (ft_strlen(str) > 1));
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
		cub->tmp_line = get_next_line(cub->tmp_fd);
		if (!cub->tmp_line)
			return (ft_safe_free(&cub->tmp_line), printf("1\n"), true);
		if (ft_start_map_condition(cub->tmp_line))
			phase = 2;
		temoin = ft_process_phase(cub, phase, &cub->tmp_line);
		//printf("line = %s", cub->tmp_line);
		ft_safe_free(&cub->tmp_line);
		//printf("temoin = %d\nphase = %d\n", temoin, phase);
		if (!temoin)
			return (ft_safe_free(&cub->tmp_line), printf("2\n"), false);
	}
	return (ft_safe_free(&cub->tmp_line), true);
}

/*
mit le free texture
ici en attendant puisque c'est la première partie
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
		return (free(cub->map), ft_safe_free(&cub->tmp_line), ft_free_textures(cub), ft_close_fd(&(cub->tmp_fd)), false);
	ft_close_fd(&(cub->tmp_fd));
	ft_free_textures(cub);
	ft_free_map(cub->map);
	ft_safe_free(&cub->tmp_line);
	return (true);
}
