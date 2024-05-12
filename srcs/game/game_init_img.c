/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:43:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/11 16:55:10 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	ft_free_imgs(t_data *cub, int i, bool err)
{
	if (!err)
		i = 3;
	while (i >= 0)
	{
		if (cub->imgs[i]->img)
			mlx_destroy_image(cub->mlx_ptr, cub->imgs[i]->img);
		if (cub->imgs[i]->adress)
			ft_safe_free(&cub->imgs[i]->adress);
		if (cub->imgs[i])
			free(cub->imgs[i]);
		i--;
	}
	if (cub->imgs)
		free(cub->imgs);
	if (err)
		return (ft_err_ret("failed to gen imgs", NULL, false));
	return (true);
}

bool	ft_open_images(t_data *cub)
{
	int	i;

	i = 0;
	cub->imgs = ft_calloc(4, sizeof(t_img_mlx *));
	if (!cub->imgs)
		return (ft_free_imgs(cub, i, true));
	while (i < 4)
	{
		cub->imgs[i] = ft_calloc(1, sizeof(t_img_mlx));
		cub->imgs[i]->img = mlx_xpm_file_to_image(cub->mlx_ptr, \
		cub->path_texture[i], &cub->imgs[i]->width, &cub->imgs[i]->height);
		if (!cub->imgs[i]->img)
			return (ft_free_imgs(cub, i, true));
		cub->imgs[i]->adress = ft_calloc(1, sizeof(char *));
		if (!cub->imgs[i]->adress)
			return (ft_free_imgs(cub, i, true));
		cub->imgs[i]->adress = mlx_get_data_addr(cub->imgs[i]->img, \
		&cub->imgs[i]->bpp, &cub->imgs[i]->s_line, &cub->imgs[i]->endian);
		i++;
	}
	return (true);
}
