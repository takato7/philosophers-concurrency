/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:03:45 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 18:16:36 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_close(t_sem sem)
{
	if (sem_close(sem.semd) == -1)
		ft_simple_perror("sem_close");
}

void	ft_clean_exit_sems(t_sem **semarr)
{
	ssize_t	i;

	i = -1;
	while (++i < MEM_T_SEMS)
	{
		if (semarr[i])
			ft_sem_close(*(semarr[i]));
	}
}

void	ft_clean_exit(t_philos *philo, int es)
{
	free(philo->pid);
	ft_clean_exit_sems(philo->semarr);
	exit(es);
}
