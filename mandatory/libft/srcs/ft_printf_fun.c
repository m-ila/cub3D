/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:57:32 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 17:39:11 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_str(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printf_char(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
