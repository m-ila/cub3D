/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emb_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:40:24 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 12:45:12 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	ft_emb_free(int c, t_data *cub)
{
	if (c == 1)
	{
		ft_safe_free(&(cub->tmp_line));
		ft_free_textures(cub);
		ft_close_fd(&(cub->tmp_fd));
		return (false);
	}
	else if (c == 2)
	{
		ft_safe_free(&(cub->tmp_line));
		ft_free_textures(cub);
		ft_close_fd(&(cub->tmp_fd));
		ft_free_map(cub->map);
		return (ft_err_ret("wrong data map", NULL, false));
	}
	else if (c == 3)
	{
		ft_safe_free(&(cub->tmp_line));
		ft_free_textures(cub);
		ft_close_fd(&(cub->tmp_fd));
		ft_free_map(cub->map);
		return (ft_err_ret("wrong data map 2", NULL, false));
	}
	return (false);
}
