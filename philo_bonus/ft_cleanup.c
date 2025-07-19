/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:58:15 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/22 15:39:11 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_unlink(char *name)
{
	if (sem_unlink(name) == -1)
		ft_simple_perror("sem_unlink");
}

void	ft_sem_destroy(t_sem sem)
{
	ft_sem_close(sem);
	ft_sem_unlink(sem.name);
}

void	ft_cleanup_sems(t_sem **semarr)
{
	ssize_t	i;

	i = -1;
	while (++i < MEM_T_SEMS)
	{
		if (semarr[i])
			ft_sem_destroy(*(semarr[i]));
	}
}

void	ft_cleanup(t_philos *philo)
{
	free(philo->pid);
	ft_cleanup_sems(philo->semarr);
}
