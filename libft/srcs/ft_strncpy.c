/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:59:52 by yuewang           #+#    #+#             */
/*   Updated: 2024/05/01 13:23:28 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j] && i < n)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}
