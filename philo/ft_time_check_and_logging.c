/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_check_and_logging.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:28:38 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 19:28:58 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	tmstamp = ft_get_usec_time_diff(current_tv, philo->info->tv_start);
	if (ft_print_status(philo->num + 1, tmstamp, log) < 0)
	{
		ft_simple_perror("printf");
		philo->info->sim = ERROR;
		return (1);
	}
	return (0);
}

static int	ft_time_check(t_philos *philo, t_tv *current_tv, t_log log)
{
	long	diff;

	if (ft_gettimeofday(current_tv, NULL) < 0)
	{
		philo->info->sim = ERROR;
		return (-1);
	}
	diff = ft_get_usec_time_diff(*current_tv, philo->tv);
	if (diff > ft_ms_to_usec(philo->tm_die))
		return (1);
	if (log == EAT)
		philo->tv = *current_tv;
	return (0);
}

static int	ft_is_stop_checking(t_philos *philo)
{
	if (philo->info->sim == END || philo->info->sim == ERROR)
	{
		ft_mutex_unlock(&philo->info->mutex_sim);
		return (1);
	}
	if (philo->full)
	{
		ft_mutex_unlock(&philo->info->mutex_sim);
		return (0);
	}
	else
		return (-1);
}

int	ft_time_check_and_logging(t_philos *philo, t_log log)
{
	int		stop_flag;
	int		dead_flag;
	t_tv	current_tv;

	ft_mutex_lock(&philo->info->mutex_sim);
	stop_flag = ft_is_stop_checking(philo);
	if (stop_flag != -1)
		return (stop_flag);
	dead_flag = ft_time_check(philo, &current_tv, log);
	if (log == MONITOR && dead_flag == 1)
	{
		if (philo->info->sim != ERROR)
			philo->info->sim = END;
		ft_logging_status(philo, current_tv, DIED);
	}
	else if (log != MONITOR && !dead_flag)
	{
		if (ft_logging_status(philo, current_tv, log))
			dead_flag = 1;
	}
	ft_mutex_unlock(&philo->info->mutex_sim);
	return (dead_flag);
}
