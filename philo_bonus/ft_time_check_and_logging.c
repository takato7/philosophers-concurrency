/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_check_and_logging.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:35:03 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:52:10 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_set_sems_free(t_philos *philo)
{
	size_t	i;

	i = philo->size * 5;
	while (i-- > 0)
		ft_sem_post(philo->sems.sim.semd);
	i = philo->size;
	while (i-- > 0)
	{
		ft_sem_post(philo->sems.fork.semd);
		ft_sem_post(philo->sems.table.semd);
	}
}

static int	ft_print_status(size_t num, long tmsp, t_log log)
{
	if (log == EAT)
		return (printf("%ld %zu is eating\n", ft_usec_to_ms(tmsp), num));
	else if (log == TAKEN)
		return (printf("%ld %zu has taken a fork\n", ft_usec_to_ms(tmsp), num));
	else if (log == SLEEP)
		return (printf("%ld %zu is sleeping\n", ft_usec_to_ms(tmsp), num));
	else if (log == THINKING)
		return (printf("%ld %zu is thinking\n", ft_usec_to_ms(tmsp), num));
	else if (log == DIED)
		return (printf("%ld %zu died\n", ft_usec_to_ms(tmsp), num));
	else
		return (printf("Wrong log value\n"));
}

static int	ft_logging_status(t_philos *philo, t_tv current_tv, t_log log)
{
	long	tmstamp;

	tmstamp = ft_get_usec_time_diff(current_tv, philo->start_tv);
	ft_sem_wait(philo->sems.log.semd);
	if (ft_print_status(philo->num + 1, tmstamp, log) < 0)
	{
		ft_simple_perror("printf");
		philo->status = ERROR;
		ft_sem_post(philo->sems.log.semd);
		return (1);
	}
	if (log != DIED)
		ft_sem_post(philo->sems.log.semd);
	else
		ft_set_sems_free(philo);
	return (0);
}

static int	ft_time_check(t_philos *philo, t_tv *current_tv, t_log log)
{
	long	diff;

	if (ft_gettimeofday(current_tv, NULL) < 0)
	{
		philo->status = ERROR;
		return (-1);
	}
	diff = ft_get_usec_time_diff(*current_tv, philo->tv);
	if (diff > ft_ms_to_usec(philo->tm_die))
		return (1);
	if (log == EAT)
		philo->tv = *current_tv;
	return (0);
}

int	ft_time_check_and_logging(t_philos *philo, t_log log)
{
	t_status	sts;
	int			dead_flag;
	t_tv		current_tv;

	ft_sem_wait(philo->sems.sim.semd);
	sts = philo->status;
	if (sts == ERROR || sts == DEAD || sts == FULL)
	{
		ft_sem_post(philo->sems.sim.semd);
		return (1);
	}
	dead_flag = ft_time_check(philo, &current_tv, log);
	if (log == MONITOR && dead_flag == 1)
	{
		if (philo->status != ERROR)
			philo->status = DEAD;
		ft_logging_status(philo, current_tv, DIED);
	}
	else if (log != MONITOR && !dead_flag)
	{
		if (ft_logging_status(philo, current_tv, log))
			dead_flag = 1;
	}
	ft_sem_post(philo->sems.sim.semd);
	return (dead_flag);
}
