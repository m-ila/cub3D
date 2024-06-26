/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:48:46 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 17:39:56 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_str_add(char **str1, char **to_add)
{
	char	*tmp;

	if (!str1 || !to_add)
		return (false);
	tmp = NULL;
	tmp = ft_strjoin(*str1, *to_add);
	if (!tmp)
		return (false);
	free(*str1);
	*str1 = tmp;
	ft_multiple_free(to_add, NULL, NULL);
	return (true);
}

int	ft_strendswith(char *str, char *end)
{
	int	str_len;
	int	end_len;
	int	i;

	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	i = 0;
	while (str[str_len - end_len + i])
	{
		if (str[str_len - end_len + i] != end[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strindex(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || *str == 0)
		return (-1);
	while (i < (int) ft_strlen(str))
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/* looks if all char of str are in a set base */
int	ft_strbase(char *str, const char *base)
{
	int	i;
	int	j;

	i = 0;
	if (!str || !base || *base == 0 || *str == 0)
		return (0);
	while (str[i])
	{
		j = 0;
		while (base[j])
		{
			if (base[j] == str[i])
				break ;
			if (base[j + 1] == '\0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* check if the str is only filled w sep char, used to prot splits var */
int	ft_str_only_sep(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != sep)
			return (0);
		i++;
	}
	return (1);
}
