/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:05:52 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/03/28 17:32:13 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	size_t	ft_get_sign(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static	size_t	ft_get_nmdgt(int n)
{
	int		div;
	size_t	nmdgt;

	div = n / 10;
	nmdgt = 1;
	while (div != 0)
	{
		div /= 10;
		nmdgt++;
	}
	return (nmdgt);
}

static	void	ft_assign_arr(char *arr, int n, size_t nmdgt)
{
	int	mod;

	if (nmdgt - 1 > 0)
		ft_assign_arr(arr, n / 10, nmdgt - 1);
	mod = n % 10;
	if (mod < 0)
		mod = -mod;
	arr[nmdgt - 1] = mod + '0';
}

char	*ft_itoa(int n)
{
	char	*arr;
	size_t	nmdgt;
	size_t	sign;

	nmdgt = ft_get_nmdgt(n);
	sign = ft_get_sign(n);
	arr = (char *)malloc(sign + nmdgt + 1);
	if (arr == NULL)
	{
		ft_simple_perror("malloc");
		return (NULL);
	}
	if (sign == 1)
		arr[0] = '-';
	ft_assign_arr(&arr[sign], n, nmdgt);
	arr[sign + nmdgt] = '\0';
	return (arr);
}
