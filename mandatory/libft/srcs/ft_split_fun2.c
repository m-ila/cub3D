/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fun2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:40 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 17:39:37 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_split_do(char *s, int *i, bool (*fun)(char*, int), int which)
{
	if (which == 1)
	{
		while (s[*i] != '\0' && fun(s, *i))
			(*i)++;
	}
	if (which == 2)
	{
		while (s[*i] != '\0' && !fun(s, *i))
			(*i)++;
	}
}
