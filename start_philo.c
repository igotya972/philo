/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:09:41 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/10 05:33:53 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_start_philo(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = malloc(sizeof (unsigned long));
	data->start_time[0] = ft_times();
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL
				, ft_routine, &data->philos[i]))
			ft_error(data, "start philo - pthread");
	}
	ft_supervise(data);
	if (data->end == 1)
		return ;
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_join(data->philos[i].thread, NULL))
			ft_error(data, "pthread_join");
}

int	ft_check_death(t_data *data, int i)
{
	if (ft_times() - data->philos[i].last_eat >= data->time_to_die)
	{
		data->end = 1;
		printf("%lu %d %s\n",
			ft_times() - data->start_time[0], data->philos[i].id, "died");
		return (1);
	}
	return (0);
}

void	ft_monitoring(t_philo *philo, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->mutex);
	time = ft_times() - philo->data->start_time[0];
	if (philo->data->end == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

int	ft_satiate(t_data *data, int i)
{
	static int	count_eat;

	if (data->nb_must_eat >= 0)
	{
		if (data->nb_must_eat <= data->philos[i].count_p_eat)
		{
			count_eat++;
		}
		if (count_eat >= data->nb_philo)
		{
			data->end = 1;
			return (1);
		}
		if (data->nb_philo == i + 1)
			count_eat = 0;
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (philo->data->end == 1)
		return ;
	pthread_mutex_lock(&philo->fork);
	ft_monitoring(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->philos[(philo->id)
		% philo->data->nb_philo].fork);
	ft_monitoring(philo, "has taken a fork");
	ft_monitoring(philo, "is eating");
	pthread_mutex_lock(&(philo->data->mutex));
	philo->last_eat = ft_times();
	philo->count_p_eat++;
	pthread_mutex_unlock(&(philo->data->mutex));
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->data->philos[(philo->id)
		% philo->data->nb_philo].fork);
}
