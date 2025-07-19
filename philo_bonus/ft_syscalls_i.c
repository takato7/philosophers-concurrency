/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscalls_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:52:32 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:12:21 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_pthcrt(t_pth *th, t_patt *at, void *(*fct) (void *), void *arg)
{
	int	val;

	val = pthread_create(th, at, fct, arg);
	if (val)
		ft_simple_perror("pthread_create");
	return (val);
}

int	ft_pthjn(t_pth th, void **retval)
{
	int	val;

	val = pthread_join(th, retval);
	if (val)
		ft_simple_perror("pthread_join");
	return (val);
}

int	ft_gettimeofday(t_tv *tv, t_tz *tz)
{
	int	val;

	val = gettimeofday(tv, tz);
	if (val < 0)
		ft_simple_perror("gettimeofday");
	return (val);
}

static int	ft_usleep_util(t_tv start, long usec)
{
	long	time;
	t_tv	current;
	long	diff;
	long	rest;
	int		val;

	if (usec > 1e3)
		time = usec / 4;
	else
		time = usec;
	val = usleep(time);
	if (val < 0)
		ft_simple_perror("usleep");
	if (ft_gettimeofday(&current, NULL) < 0)
		return (-1);
	diff = ft_get_usec_time_diff(current, start);
	rest = usec - diff;
	if (rest > 0)
		return (ft_usleep_util(current, rest));
	return (val);
}

int	ft_usleep(long usec)
{
	t_tv	start;

	if (ft_gettimeofday(&start, NULL) < 0)
		return (-1);
	return (ft_usleep_util(start, usec));
}
