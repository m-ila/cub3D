/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:43:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/15 23:45:33 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool ft_free_imgs(t_data *cub, int count, bool return_val)
{
	int j;
	
	j = 0;
    while (j < count)
	{
        if (cub->imgs[j]) {
            if (cub->imgs[j]->img)
                mlx_destroy_image(cub->mlx_ptr, cub->imgs[j]->img);
            free(cub->imgs[j]);
        }
		j++;
    }
    free(cub->imgs);
    cub->imgs = NULL;
    return return_val;
}


bool ft_open_images(t_data *cub) {
    int i = 0;

    cub->imgs = ft_calloc(4, sizeof(t_img_mlx *));
    if (!cub->imgs)
        return (ft_free_imgs(cub, i, true)); // Make sure ft_free_imgs can handle `i == 0`.

    while (i < 4) {
        cub->imgs[i] = ft_calloc(1, sizeof(t_img_mlx));
        if (!cub->imgs[i]) {
            return (ft_free_imgs(cub, i, true)); // Free previously allocated images
        }
        cub->imgs[i]->img = mlx_xpm_file_to_image(cub->mlx_ptr, cub->path_texture[i], &cub->imgs[i]->width, &cub->imgs[i]->height);
        if (!cub->imgs[i]->img) {
            return (ft_free_imgs(cub, i + 1, true)); // Free all allocated images including the failed one
        }
        // Directly assign the address returned by mlx_get_data_addr
        cub->imgs[i]->adress = mlx_get_data_addr(cub->imgs[i]->img, &cub->imgs[i]->bpp, &cub->imgs[i]->s_line, &cub->imgs[i]->endian);
        i++;
    }
    return (true);
}

