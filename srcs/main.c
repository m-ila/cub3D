/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:54:11 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 16:05:16 by yuewang          ###   ########.fr       */
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
			return (ft_safe_free(&cub.tmp_line), 1);
		ft_game(&cub);
		ft_close_fd(&(cub.tmp_fd));
		ft_free_textures(&cub);
		ft_free_map(cub.map);
		ft_safe_free(&cub.tmp_line);
	}
	else
		return (ft_err_ret("proper use : ./cub3d *file_path*", NULL, 1));
	return (0);
}
