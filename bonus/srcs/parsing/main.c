/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:54:11 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/28 15:16:03 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	ft_free_end(t_data *cub)
{
	ft_close_fd(&cub->tmp_fd);
	ft_free_textures(cub);
	if (cub->map->raw_map)
		ft_free_2d_array(cub->map->raw_map);
	if (cub->map->map_cpy)
		ft_free_2d_array(cub->map->map_cpy);
	if (cub->map)
	{
		free(cub->map);
		cub->map = NULL;
	}
	ft_safe_free(&cub->tmp_line);
	free(cub->seg);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	cub;

	(void)argc;
	if (!envp || !(*envp))
		return (ft_printf_fd(STDERR_FILENO, \
		"Error : needs an env to run MLX\n"), 1);
	if (argc >= 2 && !ft_strlen(argv[1]))
		return (ft_err_ret("enter valid path", NULL, 1));
	if (argc == 2)
	{
		if (!ft_init_struct(&cub, argv[1]))
			return (ft_safe_free(&cub.tmp_line), \
			ft_close_fd(&(cub.tmp_fd)), ft_free_textures(&cub), 1);
		ft_game(&cub);
		ft_free_end(&cub);
	}
	else
		return (ft_err_ret("proper use : ./cub3d *file_path*", NULL, 1));
	return (0);
}
