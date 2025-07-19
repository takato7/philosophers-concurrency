/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:02:29 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 19:06:49 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_set_first_second_hand(t_philos *philo, size_t n)
{
	if (n != philo->size - 1)
	{
		philo->first_hand = philo;
		philo->second_hand = philo + 1;
	}
	else
	{
		philo->first_hand = philo - n;
		philo->second_hand = philo;
	}
	return (philo);
}

static int	ft_set_values(t_philos *philo, size_t i, t_shared *info)
{
	philo[i].num = i;
	philo[i].size = info->size;
	philo[i].tm_die = info->tm_die;
	philo[i].tm_eat = info->tm_eat;
	philo[i].tm_sleep = info->tm_sleep;
	philo[i].tms_must_eat = info->tms_must_eat;
	philo[i].fork = 1;
	philo[i].full = 0;
	philo[i].info = info;
	if (ft_mutex_init(&philo[i].mutex_fork, NULL))
		return (-1);
	return (0);
}

t_philos	*ft_init_philos(t_shared *info)
{
	t_philos	*philo;
	size_t		i;

	philo = (t_philos *)malloc(sizeof(t_philos) * info->size);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < info->size)
	{
		if (ft_set_values(philo, i, info) == -1)
		{
			ft_destroy_philos_mutex(philo, i);
			free(philo);
			return (NULL);
		}
		ft_set_first_second_hand(&philo[i], i);
		i++;
	}
	return (philo);
}
