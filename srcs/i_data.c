/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/18 13:50:17 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* fonction access non autorisée */
int		ft_err_ret(char *msg, char *name, int ret)
{
	if (name = NULL)
		ft_printf_fd(2, "Error : %s\n", msg);
	if (name)
		ft_printf_fd(2, "Error : %s : %s\n", name, msg);
	return (ret);
}

bool	ft_check_file_rights(char *path_file)
{
	if (access(path_file, O_RDONLY))
		return (ft_err_ret("rights to read not allowed", path_file, false));
}

bool	ft_init_struct(t_data *cub, char *path_file)
{
	
}
