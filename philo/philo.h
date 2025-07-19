/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:19:13 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/23 19:11:46 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define ERRCOM ": Error\n"
# define BUFFER 5e3

typedef enum s_log
{
	THINKING,
	TAKEN,
	EAT,
	SLEEP,
	DIED,
	MONITOR,
}	t_log;

typedef enum s_sim
{
	NOTREADY,
	ALONE,
	START,
	END,
	ERROR,
}	t_sim;

typedef struct timeval		t_tv;
typedef struct timezone		t_tz;
typedef pthread_t			t_pth;
typedef pthread_attr_t		t_patt;
typedef pthread_mutex_t		t_pthmtx;
typedef pthread_mutexattr_t	t_pthmtxatt;

typedef struct s_shared
{
	size_t			size;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				tms_must_eat;	
	t_sim			sim;
	t_tv			tv_start;
	t_pthmtx		mutex_sim;
}					t_shared;

typedef struct s_philos
{
	size_t			num;
	t_pth			pthid;
	size_t			size;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				tms_must_eat;
	struct s_philos	*first_hand;
	struct s_philos	*second_hand;
	int				fork;
	int				full;
	t_tv			tv;
	t_pthmtx		mutex_fork;
	t_shared		*info;
}					t_philos;

t_shared	*ft_init_info(t_shared *info, int argc, char *argv[]);
t_philos	*ft_init_philos(t_shared *info);
void		ft_cleanup(t_philos *philo, t_shared *info);
size_t		ft_create_philos_threads(t_philos *philo);
void		ft_join_philos(t_philos *philo, size_t num_thread);
size_t		ft_create_monitor_thread(t_pth *pthid, t_philos *philo);
void		ft_join_monitor(t_pth pthid, size_t num_thread);
void		ft_destroy_philos_mutex(t_philos *philo, size_t size);
int			ft_start_simulate(t_philos *philo, t_shared *info);
void		*ft_start_routine(void *arg);
void		*ft_start_monitor(void *arg);
int			ft_eating(t_philos *philo);
int			ft_time_check_and_logging(t_philos *philo, t_log log);
int			ft_checkout_crtsct_simulate(t_shared *info);
void		ft_set_crtsct_simulate(t_shared *info, t_sim sim);
int			ft_pthcrt(t_pth *th, t_patt *at, void *(*fct) (void *), void *arg);
int			ft_pthjn(t_pth th, void **retval);
int			ft_mutex_init(t_pthmtx *restrict mtx, t_pthmtxatt *restrict attr);
int			ft_mutex_destroy(t_pthmtx *mtx);
int			ft_mutex_lock(t_pthmtx *mtx);
int			ft_mutex_unlock(t_pthmtx *mtx);
int			ft_gettimeofday(t_tv *tv, t_tz *tz);
int			ft_usleep(long usec);
int			ft_atoi(char *str);
int			ft_strcmp(char *s1, char *s2);
long		ft_usec_to_ms(suseconds_t time);
long		ft_ms_to_usec(long time);
long		ft_get_usec_time_diff(t_tv now, t_tv start);
int			ft_tmcmp(t_tv tv1, t_tv tv2);
void		ft_simple_perror(char *cmd);

#endif