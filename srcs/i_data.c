/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/18 17:30:30 by mbruyant         ###   ########.fr       */
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
}

/* split & strdup to protect */
void	ft_process_phase(t_data *cub, int phase, char **line)
{
	if (phase == 1)
	{
		char	**arr;

		arr = ft_split(*line, ' ');
		if (!arr)
		{
			free(*line);
			*line = NULL;
			return ;
		}
		ft_display_2d(arr);
		if (ft_is_text(arr[0]))
			cub->path_texture[ft_which_text(arr[0])] = ft_strdup(arr[1]);
		if (ft_is_color(arr[0]))
			ft_process_color(cub, arr);
		ft_free_2d_array(arr);
	}
	if (phase == 2)
	{
		
	}
}

void	ft_process_file(t_data *cub)
{
	char	*line;
	char	**arr;

	line = "start";
	while (line)
	{
		line = get_next_line(cub->tmp_fd);
		if (!line)
			return ;
		ft_process_file(cub);
		printf("line = %s", line);
		free(line);
	}
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
	ft_process_file(cub);
	ft_close_fd(&(cub->tmp_fd));
	return (true);
}
