/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/18 15:47:31 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

bool	ft_open_file(t_data *cub, char *path_file)
{
	cub->tmp_fd = open(path_file, O_RDONLY);
	if (cub->tmp_fd == -1)
		return (ft_err_ret("failed to open", path_file, false));
	return (true);
}

bool	ft_init_struct(t_data *cub, char *path_file)
{
	if (cub && path_file)
		return (true);
	return (false);
}
