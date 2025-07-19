/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_simulate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:22:31 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 11:56:49 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_kill_chdproc(t_pid *pids, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!pids[i].flag)
			ft_kill(pids[i].num, SIGKILL);
		i++;
	}
}

static int	ft_create_philos(t_philos *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->size)
	{
		philo->pid[i].flag = 0;
		philo->pid[i].num = ft_fork();
		if (philo->pid[i].num == -1)
		{
			ft_kill_chdproc(philo->pid, i);
			return (0);
		}
		if (philo->pid[i].num == 0)
			ft_start_routine(i, philo);
		i++;
	}
	return (1);
}

static void	ft_set_return_flag(pid_t return_pid, t_pid *pids, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (pids[i].num == return_pid)
		{
			pids[i].flag = 1;
			return ;
		}
		i++;
	}
}

static int	ft_wait_chdproc(t_philos *philo, size_t num)
{
	pid_t	pid;
	int		wstatus;

	while (num-- > 0)
	{
		pid = ft_waitpid(-1, &wstatus, 0);
		ft_set_return_flag(pid, philo->pid, philo->size);
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
		{
			ft_kill_chdproc(philo->pid, philo->size);
			if (WEXITSTATUS(wstatus) == EXIT_DEAD)
				return (0);
			if (WEXITSTATUS(wstatus) == EXIT_FAILURE)
				return (1);
		}
	}
	return (0);
}

void	ft_start_simulate(t_philos *philo)
{
	if (ft_gettimeofday(&philo->start_tv, NULL) < 0)
	{
		ft_cleanup(philo);
		exit(EXIT_FAILURE);
	}
	philo->tv = philo->start_tv;
	if (!ft_create_philos(philo))
	{
		ft_cleanup(philo);
		exit(EXIT_FAILURE);
	}
	if (ft_wait_chdproc(philo, philo->size))
	{
		ft_cleanup(philo);
		exit(EXIT_FAILURE);
	}
	ft_cleanup(philo);
}
