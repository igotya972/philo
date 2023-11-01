/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:12:52 by dferjul           #+#    #+#             */
/*   Updated: 2023/10/30 17:49:41 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h>

# define LOPHI	0

#define TRUE = 1
#define FALSE = 0

typedef int bool;

typedef struct	s_philo	t_philo;

typedef struct	s_data
{
	unsigned long	start_time;
	int				nb_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				nb_must_eat;
	t_philo			*philos;
	pthread_mutex_t	mutex;
	int			end;
}				t_data;

struct	s_philo
{
	t_data				*data;
	int					count_p_eat;
	unsigned long		last_eat;
	int					id;
	pthread_mutex_t		fork;
	pthread_mutex_t		l_fork;
	pthread_t			thread;
};

/*	philo.c	*/
void	ft_check_args(int ac, char **av, t_data *data);

/*	init.c	*/
unsigned int	ft_atoi(const char *str);
void			ft_init_data(int ac, char **av, t_data *data);
void			ft_init_philo(t_data *data);

/*	error.c	*/
void	ft_free(t_data *data);
void	ft_error(t_data *data, char *str);

/*	utils.c	*/
unsigned long	ft_times(void);
void			ft_usleep(unsigned long time);

/*	start_philo.c	*/
void	ft_start_philo(t_data *data);
void	ft_supervise(t_data *data);
int		ft_check_death(t_data *data, int i);
void	ft_monitoring(t_philo *philo, char *str);
int		ft_satiate(t_data *data, int i);
void	ft_eat(t_philo *philo);
void	*ft_routine(void *p);

#endif
