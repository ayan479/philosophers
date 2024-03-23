/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayan <mayan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:43:24 by mayan             #+#    #+#             */
/*   Updated: 2024/03/23 15:32:54 by mayan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>   // mutex: init destroy lock unlock
# include <stdbool.h>   // bool
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free
# include <unistd.h>    // write, usleep
						//threads: create join detach
# include <limits.h>    // INT_MAX
# include <sys/time.h>  // gettimeofday
# define RST "\033[0m"  /* Reset to default color */
# define R "\033[1;31m" /* Bold Red */
# define G "\033[1;32m" /* Bold Green */
# define B "\033[1;34m" /* Bold Blue */
# define Y "\033[1;33m" /* Bold Yellow */
# define M "\033[1;35m" /* Bold Magenta */
# define C "\033[1;36m" /* Bold Cyan */
# define W "\033[1;37m" /* Bold White */

# define FORK "%ld %d has taken a fork\n"
# define EAT "%ld %d is eating\n"
# define SLEEP "%ld %d is sleeping\n"
# define THINK "%ld %d is thinking\n"
# define DEATH "%ld %d starved to death\n"

# ifndef MAXPHILO
#  define MAXPHILO 200
# endif

typedef enum e_status
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	TAKEFORK1,
	TAKEFORK2,
}						t_status;

/*
code for mutex and threads
*/

typedef enum e_mtcode
{
	INIT,
	CREATE,
	DESTROY,
	LOCK,
	UNLOCK,
	JOIN,
	DETACH,
}						t_mtcode;

typedef pthread_mutex_t	t_mtx;
typedef struct s_input	t_input;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx				fork;
	int					a;
	int					id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals;
	bool				full;
	t_data				*data;
	t_fork				*firstfork;
	t_fork				*secondfork;
	long				last_time_ate;
	pthread_t			thread_id;
	t_mtx				philo_mtx;
}						t_philo;

typedef struct s_data
{
	long				num_philos;
	long				ttd;
	long				tte;
	long				tts;
	long				meallimit;
	long				start_sim;
	long				runningthreads;
	bool				all_threads_ready;
	bool				deadphil;
	t_mtx				data_mtx;
	t_mtx				print_mtx;
	t_fork				*forks;
	t_philo				*philos;
	pthread_t			monitor;
	bool				errorflag;
}						t_data;

// a philo is a thread
/*
** - ttd: Time after which a philosopher will die if they haven't eaten.
** - tte: Time it takes for a philosopher to eat a meal.
** - tts: Time it takes for a philosopher to sleep.
** - meallimit: The number of meals limit, if < 0 no limits.
** - num_philos: Number of philos at table
** - start_sim: The starting time of the simulation.
** - deadphil: when a philo die, this flag ON
** - all_threads_ready: synchronises the start of simulation
*/

int						error_exit(const char *error);

int						parse_input(t_data *data, char **av);

void					data_init(t_data *data);

void					start_sim(t_data *data);
void					*safemlloc(size_t bytes);
void					safemtx(t_mtx *mutex, t_mtcode mtcode);
void					safethrd(pthread_t *thread, void *(*foo)(void *),
							void *arg, t_mtcode mtcode);

long					getlong(t_mtx *mutex, long *src);
void					setlong(t_mtx *mutex, long *dest, long value);
void					setbool(t_mtx *mutex, bool *dest, bool value);
bool					getbool(t_mtx *mutex, bool *src);

void					wait_for_thrds(t_data *data);
long					get_current_time(void);
void					ft_usleep(long time, t_data *data);

void					philoprint(t_status status, t_philo *philo);

bool					all_threads_running(t_mtx *mtx, long *threads,
							long num_philos);
void					increaselong(t_mtx *mtx, long *val);
void					*monitor_din(void *ptr);
void					clean(t_data *data);
void					thinking(t_philo *philo, bool presim);
void					syncphilo(t_philo *philo);

#endif
