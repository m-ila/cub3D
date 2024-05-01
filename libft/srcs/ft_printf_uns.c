/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:18:19 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 13:22:31 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_uns_count_digits(unsigned int nb)
{
	size_t	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

int	ft_printf_uns(unsigned int nb, int fd)
{
	if (nb >= 10)
	{
		ft_printf_uns(nb / 10, fd);
	}
	ft_putchar_fd(((nb % 10) + '0'), fd);
	return (ft_uns_count_digits(nb));
}
