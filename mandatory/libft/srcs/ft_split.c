/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:03:30 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 17:39:44 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*ft_free(char **s, size_t j)
{
	while (j > 0)
	{
		j--;
		free(s[j]);
	}
	free(s);
	return (NULL);
}

static size_t	ft_wrd_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static int	ft_wrd_nb(const char *s, char c)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i] != '\0')
	{	
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (nb);
}

static char	*ft_wrd(char const *s, char c)
{
	char	*ret;
	int		index;

	if (!s)
		return (NULL);
	ret = (char *) malloc((ft_wrd_len(s, c) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (s[index] != c && index < (int) ft_strlen(s))
	{
		ret[index] = s[index];
		index++;
	}
	ret[index] = '\0';
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char		**ret;
	int			j;

	j = 0;
	if (!s || ft_str_only_sep((char *) s, c))
		return (ft_split_entry_exit((char *) s));
	ret = (char **)ft_calloc((ft_wrd_nb(s, c) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			ret[j] = ft_wrd(s, c);
			if (!ret[j])
				return (ft_free(ret, j));
			j++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	return (ret);
}
