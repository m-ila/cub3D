/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:10:35 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/08 13:13:16 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
#define POINT_H

#include "cub3d.h"

typedef struct s_point
{
	size_t	x;
	size_t	y;
}	t_point;

typedef struct s_map
{
	char	**rawMap;
	size_t	xSizeMax;
	size_t	ySizeMax;
	size_t	nbSpawnPoint;
}	t_map;

#endif