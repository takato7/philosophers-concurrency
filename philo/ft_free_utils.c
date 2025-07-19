/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:08:17 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 19:20:29 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_philos_mutex(t_philos *philo, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_mutex_destroy(&philo[i].mutex_fork);
		i++;
	}
}

void	ft_cleanup(t_philos *philo, t_shared *info)
{
	ft_mutex_destroy(&info->mutex_sim);
	ft_destroy_philos_mutex(philo, philo->size);
	free(philo);
}
