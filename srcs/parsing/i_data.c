/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/16 15:12:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
		return (ft_safe_free(&(cub->tmp_line)), \
		ft_err_ret("split error", NULL, false));
	//ft_display_2d(arr);
	if (ft_is_text(arr[0]) && ft_2d_lines(arr) == 2)
		cub->path_texture[ft_which_text(arr[0])] = ft_strdup(arr[1]);
	if (ft_is_text(arr[0]) && ft_2d_lines(arr) != 2)
		return (ft_free_2d_array(arr), ft_safe_free(&(cub->tmp_line)), \
		ft_err_ret(E_PATH, NULL, false));
	if (ft_is_color(arr[0]) && !ft_process_color(cub, arr))
		return (ft_free_2d_array(arr), ft_safe_free(&(cub->tmp_line)), \
		ft_free_map(cub->map), ft_err_ret("color in file not valid", NULL, false));
	ft_free_2d_array(arr);
	//ft_safe_free(&(cub->tmp_line));
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

/*
ici, faire en sorte que si la phase 2 est entree,
checke si les lignes suivantes sont uniquement des lignes vides avec
ft_has_only_after(*line, 0, ft_bool_endline)
si oui, on arrete le compte de ligne la
sinon (si dans la map il y a une ligne avec uniquement des espace/whitespaces)
laisse passer mais ce cas de parsing est cense renvoyer faux
*/
char **read_all_lines(int fd, int *line_count)
{
    char **lines = NULL;
    char *line;
    *line_count = 0;

    while ((line = get_next_line(fd)) != NULL)
	{
        lines = realloc(lines, sizeof(char *) * (*line_count + 1));
        if (lines == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        lines[*line_count] = line;
        (*line_count)++;
    }
    return lines;
}

bool check_line(t_data *cub, char **line, int *phase)
{
    if (*line && ft_strendswith(*line, "\n") && ft_strlen(*line) > 1)
	{
        char *cpy = ft_strdup(*line);
        free(*line);
        *line = ft_str_epur(cpy, '\n');
        free(cpy);
    }
    if (!(*line))
		return (false);
    if (ft_start_map_condition(*line))
        *phase = 2;
    if (*phase == 2 && ft_has_only_after(*line, 0, ft_bool_endline))
        return (ft_free_map(cub->map) ,ft_err_ret("map must not have empty lines", NULL, false));
    return ft_process_phase(cub, *phase, line);
}

/*
ici a un moment ca renvoie faux voir com au dessus de read_all_lines
*/
bool ft_process_file(t_data *cub)
{
    char **all_lines;
    
	int (line_count) = 0;
    bool (temoin) = true;
    int (phase) = 1;
    int (i) = 0;
    int (j) = 0;
	all_lines = read_all_lines(cub->tmp_fd, &line_count);
    while (temoin && i < line_count)
	{
        temoin = check_line(cub, &all_lines[i], &phase);
        i++;
    }
    while (j < line_count) 
	{
        ft_safe_free(&all_lines[j]);
		j++;
    }
    free(all_lines);
    return (temoin);
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
			return (ft_free_map(cub->map), ft_err_ret("missing path texture", NULL, false));
		tmp_op = open(cub->path_texture[i], O_RDONLY);
		if (tmp_op == -1)
			return (ft_free_map(cub->map), ft_err_ret("cannot open", cub->path_texture[i], false));
		ft_close_fd(&tmp_op);
		i++;
	}
	if (cub->floor_c.r == -1 || cub->floor_c.g == -1 || cub->floor_c.b == -1 || \
	cub->ceiling_c.r == -1 || cub->ceiling_c.g == -1 || cub->ceiling_c.b == -1)
		return (ft_free_map(cub->map), ft_err_ret("color not initialized", cub->path_texture[i], false));
	return (true);
}

/*
si free(cub->map) dans !ft_process_file, va causer pb, faire free map char** d'abord
*/
bool	ft_init_struct(t_data *cub, char *path_file)
{
	if (!cub || !path_file)
		return (false);
	ft_init_null(cub);
	if (!ft_open_file(cub, path_file))
		return (false);
	if (!ft_process_file(cub))
		return (ft_safe_free(&(cub->tmp_line)), ft_free_textures(cub), ft_close_fd(&(cub->tmp_fd)), false);
	printf("\nDisplay raw map\n");
	if (cub->map->raw_map)
		ft_display_2d(cub->map->raw_map);
	if (!ft_get_data_map(cub->map))
		return (ft_safe_free(&(cub->tmp_line)), ft_free_textures(cub), ft_close_fd(&(cub->tmp_fd)), ft_free_map(cub->map), ft_err_ret("wrong data map", NULL, false));
	cub->map->map_cpy = ft_copy_2d_array(cub->map->raw_map, 0, ft_2d_lines(cub->map->raw_map));
	if (cub->map && cub->map->map_cpy)
	{
		ft_flood_fill(&cub->map->spawn, cub->map);
		printf("\nDisplay map flood fill\n");
		if (cub->map->map_cpy)
			ft_display_2d(cub->map->map_cpy);
		if (!ft_parse_flood_fill(cub->map))
			return (ft_safe_free(&(cub->tmp_line)), ft_free_textures(cub), ft_close_fd(&(cub->tmp_fd)), ft_free_map(cub->map), ft_err_ret("wrong data map 2", NULL, false));
	}
	return (ft_final_check(cub));
}
