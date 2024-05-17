/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:47:29 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 12:50:24 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	ft_open_file(t_data *cub, char *path_file)
{
	if (!ft_strendswith(path_file, ".cub"))
		return (ft_free_map(cub->map), \
				ft_err_ret("file has to be of .cub extension", NULL, false));
	cub->tmp_fd = open(path_file, O_DIRECTORY);
	if (cub->tmp_fd != -1)
		return (ft_close_fd(&(cub->tmp_fd)), \
		ft_err_ret("has to be a file", path_file, false));
	cub->tmp_fd = open(path_file, O_RDONLY);
	if (cub->tmp_fd == -1)
		return (ft_err_ret("failed to open", path_file, false));
	return (true);
}

/*
ici, faire en sorte que si la phase 2 est entree,
checke si les lignes suivantes sont uniquement des lignes vides avec
ft_has_only_after(*line, 0, ft_bool_endline)
si oui, on arrete le compte de ligne la
sinon (si dans la map il y a une ligne avec uniquement des espace/whitespaces)
laisse passer mais ce cas de parsing est cense renvoyer faux
*/
char	**read_all_lines(int fd, int *line_count)
{
	char	**lines;
	char	*line;

	lines = NULL;
	*line_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_add_line_to_arr(&lines, &line);
		free(line);
		(*line_count)++;
	}
	return (lines);
}

bool	check_line(t_data *cub, char **line, int *phase)
{
	char	*cpy;

	if (*line && ft_strendswith(*line, "\n") && ft_strlen(*line) > 1)
	{
		cpy = ft_strdup(*line);
		free(*line);
		*line = ft_str_epur(cpy, '\n');
		free(cpy);
	}
	if (!(*line))
		return (false);
	if (ft_start_map_condition(*line))
		*phase = 2;
	if (*phase == 2 && ft_has_only_after(*line, 0, ft_bool_endline))
		return (ft_free_map(cub->map), \
				ft_err_ret("map must not have empty lines", NULL, false));
	return (ft_process_phase(cub, *phase, line));
}

bool	ft_process_file(t_data *cub)
{
	char	**lines;
	int		line_count;
	bool	temoin;
	int		phase;
	int		i;

	line_count = 0;
	temoin = true;
	phase = 1;
	i = 0;
	lines = read_all_lines(cub->tmp_fd, &line_count);
	while (temoin && i < line_count)
	{
		temoin = check_line(cub, &lines[i], &phase);
		i++;
	}
	ft_free_2d_array(lines);
	return (temoin);
}
