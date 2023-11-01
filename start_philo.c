/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:09:41 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/01 01:15:33 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_start_philo(t_data *data)
{
	int	i;

	i = -1;
	while(++i < data->nb_philo)
	{
		data->start_time = ft_times();
		if (pthread_create(&data->philos[i].thread, NULL, ft_routine, &data->philos[i]))
			ft_error(data, "pthread");
	}
	//printf("%p\n", &data->start_time);
	ft_supervise(data);
	i = -1;
	while(++i < data->nb_philo)
		if (pthread_join(data->philos[i].thread, NULL))
			ft_error(data, "pthread_join");
}

void	ft_supervise(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (ft_satiate(data, i) || ft_check_death(data, i))
			{
				//printf("%d\n", data->end);
				return ;
			}
		}
		//printf("COWBOW\n");
		//ft_usleep(50);
	}
}

int	ft_check_death(t_data *data, int i)
{
	if (ft_times() - data->philos[i].last_eat >= data->time_to_die)
	{
		//printf("%lu\n", data->time_to_die);
		ft_monitoring(&data->philos[i], "died");
		pthread_mutex_lock(&data->mutex);
		data->end = 1;
		pthread_mutex_unlock(&data->mutex);
		return (1);
	}
	return (0);
}

void	ft_monitoring(t_philo *philo, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->mutex);
	//printf("%p adresse\n", &philo->data->start_time);
	if (philo->data->end == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return ;
	}
	time = ft_times() - philo->data->start_time;
	printf("%lu %d %s\n", time, philo->id, str);

	pthread_mutex_unlock(&philo->data->mutex);
}

int	ft_satiate(t_data *data, int i)
{
	static int	count_eat;
	if (data->nb_must_eat <= data->philos[i].count_p_eat)
		count_eat++;
	if (count_eat >= data->nb_philo)
	{
		pthread_mutex_lock(&data->mutex);
		data->end = 1;
		pthread_mutex_unlock(&data->mutex);
		return (1);
	}
	if (data->nb_philo == i - 1)
		count_eat = 0;
	return (0);
/* 	pthread_mutex_lock(&data->mutex);
	if (data->nb_must_eat <= data->philos[i].count_p_eat)
	{
		//pthread_mutex_lock(&data->mutex);
		data->end = 1;
		pthread_mutex_unlock(&data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex);
	return (0); */
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_monitoring(philo, "has taken a fork");
	//printf("MDR\n");
	pthread_mutex_lock(&philo->data->philos[(philo->id) % philo->data->nb_philo].fork);
	ft_monitoring(philo, "has taken a fork");
	ft_monitoring(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	//pthread_mutex_lock(&philo->data->mutex);
	philo->count_p_eat++;
	philo->last_eat = ft_times();
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->data->philos[(philo->id) % philo->data->nb_philo].fork);
	//pthread_mutex_unlock(&philo->data->mutex);
}

void	*ft_routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *) p;
	if (philo->data->nb_philo == 1)
	{
		ft_monitoring(philo, "has taken a fork");
		return (NULL);
	}
	if ((philo->id % 2) == 0)
	{
		ft_usleep(philo->data->time_to_eat / 2);
	}
	while (1)
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
