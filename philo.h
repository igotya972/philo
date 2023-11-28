/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:12:52 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/28 01:14:03 by dferjul          ###   ########.fr       */
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

/*Color*/

# define COLOR_BLACK			"\033[0;30m"
# define COLOR_RED				"\033[0;31m"
# define COLOR_GREEN			"\033[0;32m"
# define COLOR_ORANGE			"\033[0;33m"
# define COLOR_BLUE				"\033[0;34m"
# define COLOR_PURPLE			"\033[0;35m"
# define COLOR_CYAN				"\033[0;36m"
# define COLOR_LIGHT_GRAY		"\033[0;37m"
# define COLOR_DARK_GRAY		"\033[1;30m"
# define COLOR_LIGHT_RED		"\033[1;31m"
# define COLOR_LIGHT_GREEN		"\033[1;32m"
# define COLOR_YELLOW			"\033[1;33m"
# define COLOR_LIGHT_BLUE		"\033[1;34m"
# define COLOR_LIGHT_PURPLE		"\033[1;35m"
# define COLOR_LIGHT_CYAN		"\033[1;36m"
# define COLOR_WHITE			"\033[1;37m"
# define NO_COLOR				"\033[0m"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	t_philo				*philos;
	unsigned long		*start_time;
	int					nb_philo;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					nb_must_eat;
	pthread_mutex_t		mutex;
	pthread_mutex_t		mutex_print;
	int					end;
}				t_data;

typedef struct s_philo
{
	t_data				*data;
	pthread_t			thread;
	pthread_mutex_t		fork;
	int					id;
	unsigned long		last_eat;
	int					count_p_eat;
}				t_philo;

/*	check.c	*/
void			ft_check_args(int ac, char **av, t_data *data);
int				ft_check_death(t_data *data, int i);
void			ft_supervise(t_data *data);
/*	eat.c	*/
void			ft_eat(t_philo *philo);
int				ft_satiate(t_data *data, int i);
/*	exit.c	*/
void			ft_free(t_data *data);
void			ft_error(t_data *data, char *str);
/*	init.c	*/
unsigned int	ft_atoi(const char *str);
int				ft_init_data(char **av, t_data *data);
void			ft_init_philo(t_data *data);
/*	start_philo.c	*/
void			ft_start_philo(t_data *data);
void			*ft_routine(void *p);
void			ft_monitoring(t_philo *philo, char *str);
/*	time.c	*/
unsigned long	ft_times(void);
void			ft_usleep(unsigned long time);

#endif
