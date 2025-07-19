/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_ii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:29:30 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/03/19 18:37:42 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_usec_to_ms(suseconds_t time)
{
	return (time / 1e3);
}

long	ft_ms_to_usec(long time)
{
	return (time * 1e3);
}

long	ft_get_usec_time_diff(t_tv now, t_tv from)
{
	long	usec_now;
	long	usec_from;

	usec_now = now.tv_sec * 1e6 + now.tv_usec;
	usec_from = from.tv_sec * 1e6 + from.tv_usec;
	return (usec_now - usec_from);
}

int	ft_tmcmp(t_tv tv1, t_tv tv2)
{
	long	diff;

	diff = ft_get_usec_time_diff(tv1, tv2);
	if (diff > 0)
		return (1);
	else
		return (0);
}
