/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_misc_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:28:37 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 17:39:54 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strindex_base(char *str, const char *base)
{
	int	i;

	i = 0;
	if (!str || *str == 0 || !base || !*base || !ft_strocc_base(str, base))
		return (-1);
	while (i < (int) ft_strlen(str))
	{
		if (ft_char_in_base(str[i], base))
			return (i);
		i++;
	}
	return (-1);
}
