/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:43:43 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 19:08:00 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_set_input(t_shared *info, int argc, char *argv[])
{
	info->size = ft_atoi(argv[1]);
	if (!info->size)
		return (0);
	info->tm_die = ft_atoi(argv[2]);
	if (!info->tm_die && ft_strcmp(argv[2], "0"))
		return (0);
	info->tm_eat = ft_atoi(argv[3]);
	if (!info->tm_eat && ft_strcmp(argv[3], "0"))
		return (0);
	info->tm_sleep = ft_atoi(argv[4]);
	if (!info->tm_sleep && ft_strcmp(argv[4], "0"))
		return (0);
	if (argc == 5)
		info->tms_must_eat = -1;
	else
	{
		info->tms_must_eat = ft_atoi(argv[5]);
		if (!info->tms_must_eat && ft_strcmp(argv[5], "0"))
			return (0);
	}
	return (1);
}

t_shared	*ft_init_info(t_shared *info, int argc, char *argv[])
{
	if (!ft_set_input(info, argc, argv))
	{
		write(STDERR_FILENO, "Invalid Arguments\n", 18);
		return (NULL);
	}
	info->sim = NOTREADY;
	if (ft_mutex_init(&info->mutex_sim, NULL))
		return (NULL);
	return (info);
}
