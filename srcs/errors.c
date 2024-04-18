/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:00:24 by mbruyant          #+#    #+#             */
/*   Updated: 2024/04/18 15:36:41 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_err_ret(char *msg, char *name, int ret)
{
	if (name == NULL)
		ft_printf_fd(2, "Error : %s\n", msg);
	if (name)
		ft_printf_fd(2, "Error : %s : %s\n", name, msg);
	return (ret);
}
