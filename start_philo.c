/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:09:41 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/24 06:23:14 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_start_philo(t_data *data)
{
	int	i;

	i = -1;
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

void	*ft_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	if ((philo->id % 2) == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (42)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->data->end == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->mutex);
		ft_eat(philo);
		ft_monitoring(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		ft_monitoring(philo, "is thinking");
	}
	return (NULL);
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
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_unlock(&philo->data->mutex);
}
