/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:20:42 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 17:38:49 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_has_only_before(char *s, int i, int (*fun)(char))
{
	int	from;

	if (i >= (int) ft_strlen(s) || i < 0)
		return (false);
	from = 0;
	while (from < i)
	{
		if (!fun(s[from]))
			return (false);
		from++;
	}
	return (true);
}

bool	ft_has_only_after(char *s, int i, int (*fun)(char))
{
	int	from;
	int	len_max;

	len_max = (int) ft_strlen(s);
	if (i >= len_max || i < 0)
		return (false);
	from = i;
	while (from < len_max)
	{
		if (!fun(s[from]))
			return (false);
		from++;
	}
	return (true);
}
