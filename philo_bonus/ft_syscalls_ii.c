/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscalls_ii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:38:22 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/03 18:22:25 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

pid_t	ft_waitpid(pid_t pid, int *wstatus, int options)
{
	pid_t	return_pid;

	return_pid = waitpid(pid, wstatus, options);
	if (return_pid == -1)
		ft_simple_perror("waitpid");
	return (return_pid);
}

int	ft_sem_wait(sem_t *sem)
{
	int	val;

	val = sem_wait(sem);
	if (val == -1)
		ft_simple_perror("sem_wait");
	return (val);
}

int	ft_sem_post(sem_t *sem)
{
	int	val;

	val = sem_post(sem);
	if (val == -1)
		ft_simple_perror("sem_post");
	return (val);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_simple_perror("fork");
	return (pid);
}

int	ft_kill(pid_t pid, int sig)
{
	int	val;

	val = kill(pid, sig);
	if (val == -1)
		ft_simple_perror("fork");
	return (val);
}
