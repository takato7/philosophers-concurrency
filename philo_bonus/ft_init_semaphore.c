/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_semaphore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:16:00 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 11:57:00 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_sem	*ft_sem_open(t_sem *sem, char *name, size_t value)
{
	int		flag;
	mode_t	mode;

	flag = O_RDWR | O_CREAT | O_EXCL;
	mode = S_IRWXU | S_IRWXG;
	sem->name = name;
	sem->semd = sem_open(sem->name, flag, mode, value);
	if (sem->semd == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			ft_sem_unlink(sem->name);
			if (!ft_sem_open(sem, name, value))
				return (NULL);
		}
		else
		{
			ft_simple_perror("sem_open");
			return (NULL);
		}
	}
	return (sem);
}

static void	ft_set_semarr(size_t i, t_sems *sem, size_t size, t_sem **semarr)
{
	if (i == E_SEMFORK)
		semarr[i] = ft_sem_open(&sem->fork, SEMFORK, size);
	else if (i == E_SEMTABLE)
		semarr[i] = ft_sem_open(&sem->table, SEMTABLE, 1);
	else if (i == E_SEMLOG)
		semarr[i] = ft_sem_open(&sem->log, SEMLOG, 1);
	else if (i == E_SEMSIM)
		semarr[i] = ft_sem_open(&sem->sim, SEMSIM, 1);
	else
		semarr[i] = NULL;
}

static int	ft_sem_open_err(t_sem **semarr)
{
	ssize_t	i;

	i = -1;
	while (++i < MEM_T_SEMS)
	{
		if (!semarr[i])
			return (1);
	}
	return (0);
}

t_sems	*ft_init_semaphore(t_sems *sem, t_sem **semarr, size_t size)
{
	ssize_t	i;

	i = -1;
	while (++i < MEM_T_SEMS)
		ft_set_semarr(i, sem, size, semarr);
	if (ft_sem_open_err(semarr))
	{
		ft_cleanup_sems(semarr);
		return (NULL);
	}
	return (sem);
}
