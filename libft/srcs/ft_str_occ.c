/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_occ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:13:58 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 13:23:14 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strocc_from(char *str, char c, int from)
{
	int	occ;

	if (!str || from >= (int) ft_strlen(str))
		return (0);
	occ = 0;
	while (str[from])
	{
		if (str[from] == c)
			occ++;
		from++;
	}
	return (occ);
}

int	ft_strocc(char *str, char c)
{
	int	i;
	int	occ;

	i = 0;
	occ = 0;
	while ((size_t) i < ft_strlen(str))
	{
		if (str[i] == c)
			occ++;
		i++;
	}
	return (occ);
}

/* returns the number of occurence that fits in a base */
int	ft_strocc_base(char *str, const char *base)
{
	int	i;
	int	occ;
	int	len;

	i = 0;
	occ = 0;
	len = (int) ft_strlen(str);
	if (!str || !base)
		return (-1);
	while (i < len)
	{
		if (ft_char_in_base(str[i], base))
			occ++;
		i++;
	}
	return (occ);
}

/* returns the number of occurence that doesn't fit in a base */
int	ft_strocc_unbase(char *str, char *base)
{
	int	i;
	int	occ;
	int	len;

	i = 0;
	occ = 0;
	len = (int) ft_strlen(str);
	if (!str || !base)
		return (-1);
	while (i < len)
	{
		if (!ft_char_in_base(str[i], base))
			occ++;
		i++;
	}
	return (occ);
}

/*
returns the number of occurence that fits in a base
between two delimiters
*/
int	ft_strocc_delimiters(char *str, const char *base, int from, int until)
{
	int	occ;
	int	len;

	occ = 0;
	len = (int) ft_strlen(str);
	if (!str || !base || from < 0 || until >= len)
		return (-1);
	while (from < until && from < len)
	{
		if (ft_char_in_base(str[from], base))
			occ++;
		from++;
	}
	return (occ);
}
