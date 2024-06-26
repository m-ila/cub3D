/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:37:49 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 13:06:33 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_MLX_H
# define DEF_MLX_H

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define CLIC 1
# define R_CLIC 3
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

typedef struct s_img_mlx
{
	void	*img;
	int		width;
	int		height;
	char	*adress;
	int		bpp;
	int		s_line;
	int		endian;
}	t_img_mlx;

#endif