/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:54:11 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 15:14:21 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* if no env ? */
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	if (argc == 2)
	{
		t_data	cub;

		if (!ft_init_struct(&cub, argv[1]))
			return (ft_safe_free(&cub.tmp_line), ft_free_map(cub.map), 1);
		ft_close_fd(&(cub.tmp_fd));
		ft_free_textures(&cub);
		ft_free_map(cub.map);
		ft_safe_free(&cub.tmp_line);
	}
	else
		return (ft_err_ret("proper use : ./cub3d *file_path*", NULL, 1));
	return (0);
}
