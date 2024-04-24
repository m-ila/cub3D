/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/24 16:20:49 by mbruyant         ###   ########.fr       */
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

bool	ft_is_valid_file_component(char *str)
{
	if (!ft_strncmp("NO", str, ft_strlen(str) + 1) || \
	!ft_strncmp("SO", str, ft_strlen(str) + 1) || \
	!ft_strncmp("WE", str, ft_strlen(str) + 1) || \
	!ft_strncmp("EA", str, ft_strlen(str) + 1) || \
	!ft_strncmp("C", str, ft_strlen(str) + 1) || \
	!ft_strncmp("F", str, ft_strlen(str) + 1))
		return (true);
	return (false);
}

bool	ft_is_text(char *str)
{
	return (!ft_strncmp("NO", str, ft_strlen(str) + 1) || \
	!ft_strncmp("SO", str, ft_strlen(str) + 1) || \
	!ft_strncmp("WE", str, ft_strlen(str) + 1) || \
	!ft_strncmp("EA", str, ft_strlen(str) + 1));
}

bool	ft_is_color(char *str)
{
	return (!ft_strncmp("C", str, ft_strlen(str) + 1) || \
	!ft_strncmp("F", str, ft_strlen(str) + 1));
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

void	ft_safe_free(char **str)
{
	if (*str)
	{
		printf("about to free : (d)%s(f)\n", *str);
		free(*str);
		*str = NULL;
	}
}

/* split & strdup to protect */
bool	ft_process_phase(t_data *cub, int phase, char **line)
{
	if (phase == 1)
	{
		char	**arr;

		arr = ft_split_base(*line, " \n");
		if (!arr)
		{
			free(*line);
			*line = NULL;
			return (ft_err_ret("split error", NULL, false));
		}
		ft_display_2d(arr);
		if (ft_is_text(arr[0]))
			printf("texture path will be : (d)%s(f)\nindex will be : (d)%d(f)\n", arr[1], ft_which_text(arr[0]));
			//cub->path_texture[ft_which_text(arr[0])] = ft_strdup(arr[1]);
		if (ft_is_color(arr[0]) && !ft_process_color(cub, arr))
			return (ft_free_2d_array(arr), ft_err_ret("color in file not valid", NULL, false));
		ft_free_2d_array(arr);
	}
	if (phase == 2)
	{
		return (true);
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
	char	*line;
	bool	temoin;
	int		phase;

	line = NULL;
	temoin = true;
	phase = 1;
	while (temoin)
	{
		printf("\nNEWLINE\n");
		line = get_next_line(cub->tmp_fd);
		if (!line)
			return (ft_safe_free(&line), printf("1\n"), true);
		if (ft_start_map_condition(line))
			phase = 2;
		temoin = ft_process_phase(cub, phase, &line);
		printf("line = %s", line);
		ft_safe_free(&line);
		printf("line freed\ntemoin = %d\nphase = %d\n", temoin, phase);
		if (!temoin)
			return (ft_safe_free(&line), printf("2\n"), false);
	}
	return (ft_safe_free(&line), true);
}

bool	ft_init_struct(t_data *cub, char *path_file)
{
	if (!cub || !path_file)
		return (false);
	if (ft_strlen(path_file) == 0)
		return (ft_err_ret("enter valid path", NULL, false));
	if (!ft_open_file(cub, path_file))
		return (false);
	printf("opened\nfd = %d\n", cub->tmp_fd);
	if (!ft_process_file(cub))
		return (ft_close_fd(&(cub->tmp_fd)), false);
	ft_close_fd(&(cub->tmp_fd));
	return (true);
}
