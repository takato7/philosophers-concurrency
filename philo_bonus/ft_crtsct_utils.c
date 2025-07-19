/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crtsct_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:10:29 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:50:24 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_set_crtsct_status(t_philos *philo, t_status sts)
{
	ft_sem_wait(philo->sems.sim.semd);
	if (sts == FULL)
	{
		if (philo->status == ALIVE)
			philo->status = sts;
	}
	else
		philo->status = sts;
	ft_sem_post(philo->sems.sim.semd);
}
