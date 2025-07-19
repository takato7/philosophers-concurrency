/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmitsuya <tmitsuya@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:31:12 by tmitsuya          #+#    #+#             */
/*   Updated: 2025/04/24 12:22:10 by tmitsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <errno.h>
# define BUFFER 5e3
# define ERRCOM ": Error\n"
# define SEMTV "/sem_tv"
# define SEMSTS "/sem_sts"
# define SEMFORK "/sem_fork"
# define SEMTABLE "/sem_table"
# define SEMLOG "/sem_log"
# define SEMSIM "/sem_sim"
# define MEM_T_SEMS 4
# define EXIT_DEAD 2

typedef enum s_enumsems
{
	E_SEMFORK,
	E_SEMTABLE,
	E_SEMLOG,
	E_SEMSIM,
}	t_enumsems;

typedef enum s_log
{
	THINKING,
	TAKEN,
	EAT,
	SLEEP,
	DIED,
	MONITOR,
}	t_log;

typedef enum s_status
{
	ALIVE,
	FULL,
	DEAD,
	ERROR,
}	t_status;

typedef struct timeval	t_tv;
typedef struct timezone	t_tz;
typedef pthread_t		t_pth;
typedef pthread_attr_t	t_patt;

typedef struct s_sem
{
	sem_t	*semd;
	char	*name;
}			t_sem;

typedef struct s_sems
{
	t_sem	table;
	t_sem	fork;
	t_sem	log;
	t_sem	sim;
}			t_sems;

typedef struct s_pid
{
	pid_t	num;
	int		flag;
}			t_pid;

typedef struct s_philos
{
	size_t		num;
	size_t		size;
	int			tm_die;
	int			tm_eat;
	int			tm_sleep;
	int			tms_must_eat;
	t_sems		sems;
	t_tv		start_tv;
	t_tv		tv;
	t_status	status;
	t_pid		*pid;
	t_sem		*semarr[MEM_T_SEMS];
	t_pth		monitorid;
}				t_philos;

t_philos	*ft_init_philos(t_philos *philo, int argc, char *argv[]);
t_sems		*ft_init_semaphore(t_sems *sem, t_sem **reval, size_t size);
void		ft_start_simulate(t_philos *philo);
void		ft_start_routine(size_t num, t_philos *philo);
int			ft_create_monitor_thread(t_philos *philo);
int			ft_eating(t_philos *philo);
int			ft_time_check_and_logging(t_philos *philo, t_log log);
void		ft_cleanup(t_philos *philo);
void		ft_cleanup_sems(t_sem **reval);
void		ft_clean_exit(t_philos *philo, int es);
int			ft_gettimeofday(t_tv *tv, t_tz *tz);
int			ft_usleep(long usec);
pid_t		ft_fork(void);
int			ft_kill(pid_t pid, int sig);
pid_t		ft_waitpid(pid_t pid, int *wstatus, int options);
t_sem		*ft_sem_open(t_sem *sem, char *name, size_t value);
void		ft_sem_close(t_sem sem);
void		ft_sem_unlink(char *name);
int			ft_sem_wait(sem_t *sem);
int			ft_sem_post(sem_t *sem);
void		ft_sem_destroy(t_sem sem);
void		ft_set_crtsct_status(t_philos *philo, t_status sts);
int			ft_pthcrt(t_pth *th, t_patt *at, void *(*fct) (void *), void *arg);
int			ft_pthjn(t_pth th, void **retval);
int			ft_atoi(char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int n);
long		ft_usec_to_ms(suseconds_t time);
long		ft_ms_to_usec(long time);
long		ft_get_usec_time_diff(t_tv now, t_tv from);
void		ft_simple_perror(char *cmd);

#endif