/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:00:24 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/17 12:07:52 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_err_ret(char *msg, char *name, int ret)
{
	if (name == NULL)
		ft_printf_fd(2, "Error : %s\n", msg);
	if (name)
		ft_printf_fd(2, "Error : %s : %s\n", name, msg);
	return (ret);
}
