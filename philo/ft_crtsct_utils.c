/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crtsct_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:10:29 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:50:40 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checkout_crtsct_simulate(t_shared *info)
{
	int	simulate;

	ft_mutex_lock(&info->mutex_sim);
	simulate = info->sim;
	ft_mutex_unlock(&info->mutex_sim);
	return (simulate);
}

void	ft_set_crtsct_simulate(t_shared *info, t_sim sim)
{
	ft_mutex_lock(&info->mutex_sim);
	if (sim == END)
	{
		if (info->sim != ERROR)
			info->sim = sim;
	}
	else
		info->sim = sim;
	ft_mutex_unlock(&info->mutex_sim);
}
