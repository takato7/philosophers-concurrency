/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:50:43 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 18:29:24 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_set_input(t_philos *philo, int argc, char *argv[])
{
	philo->size = ft_atoi(argv[1]);
	if (!philo->size)
		return (0);
	philo->tm_die = ft_atoi(argv[2]);
	if (!philo->tm_die && ft_strcmp(argv[2], "0"))
		return (0);
	philo->tm_eat = ft_atoi(argv[3]);
	if (!philo->tm_eat && ft_strcmp(argv[3], "0"))
		return (0);
	philo->tm_sleep = ft_atoi(argv[4]);
	if (!philo->tm_sleep && ft_strcmp(argv[4], "0"))
		return (0);
	if (argc == 5)
		philo->tms_must_eat = -1;
	else
	{
		philo->tms_must_eat = ft_atoi(argv[5]);
		if (!philo->tms_must_eat && ft_strcmp(argv[5], "0"))
			return (0);
	}
	return (1);
}

t_philos	*ft_init_philos(t_philos *philo, int argc, char *argv[])
{
	if (!ft_set_input(philo, argc, argv))
	{
		write(STDERR_FILENO, "Invalid Arguments\n", 18);
		return (NULL);
	}
	philo->status = ALIVE;
	philo->pid = (t_pid *)malloc(sizeof(t_pid) * philo->size);
	if (!philo->pid)
	{
		ft_simple_perror("malloc");
		return (NULL);
	}
	return (philo);
}
