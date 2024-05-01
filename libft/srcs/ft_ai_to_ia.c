/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ai_to_ia.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:18:19 by mbruyant          #+#    #+#             */
/*   Updated: 2024/05/01 17:38:30 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	result;

	i = 0;
	neg = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -neg;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (neg * result);
}

static size_t	ft_count_digits(int nb)
{
	size_t	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb == -2147483648 || nb == 2147483647)
		return (10);
	if (nb < 0)
		nb = -nb;
	while (nb > 1)
	{
		nb = nb / 10;
		count++;
	}
	if (nb == 1)
		count++;
	return (count);
}

static size_t	ft_def_len(int nb)
{
	if (nb >= 0)
		return (ft_count_digits(nb) + 1);
	else
		return (ft_count_digits(nb) + 2);
}

static char	*ft_fill_the_array(char *ret, int i, int n)
{
	int	buff;

	buff = n;
	while (i >= 0)
	{
		if (n >= 0)
			ret[i] = '0' + (n % 10);
		else
			ret[i] = '0' - (n % 10);
		n /= 10;
		i--;
		if (i == 0 && buff < 0)
			break ;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	ret = (char *) ft_calloc(ft_def_len(n), sizeof(char));
	if (!ret)
		return (NULL);
	i = ft_def_len(n) - 2;
	if (n < 0)
		ret[0] = '-';
	ft_fill_the_array(ret, i, n);
	return (ret);
}
