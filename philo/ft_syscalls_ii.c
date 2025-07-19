/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscalls_ii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:15:47 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/10 18:41:16 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_mutex_init(t_pthmtx *restrict mtx, t_pthmtxatt *restrict attr)
{
	int	val;

	val = pthread_mutex_init(mtx, attr);
	if (val)
		ft_simple_perror("pthread_mutex_init");
	return (val);
}

int	ft_mutex_destroy(t_pthmtx *mtx)
{
	int	val;

	val = pthread_mutex_destroy(mtx);
	if (val)
		ft_simple_perror("pthread_mutex_destroy");
	return (val);
}

int	ft_mutex_lock(t_pthmtx *mtx)
{
	int	val;

	val = pthread_mutex_lock(mtx);
	if (val)
		ft_simple_perror("pthread_mutex_lock");
	return (val);
}

int	ft_mutex_unlock(t_pthmtx *mtx)
{
	int	val;

	val = pthread_mutex_unlock(mtx);
	if (val)
		ft_simple_perror("pthread_mutex_unlock");
	return (val);
}
