/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:58:07 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/23 19:58:07 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_monitoring(philo, COLOR_RED "has taken a fork" NO_COLOR);
	pthread_mutex_lock(&philo->data->philos[(philo->id)
		% philo->data->nb_philo].fork);
	ft_monitoring(philo, COLOR_RED "has taken a fork" NO_COLOR);
	ft_monitoring(philo, COLOR_DARK_GRAY "is eating" NO_COLOR);
	pthread_mutex_lock(&(philo->data->mutex));
	philo->last_eat = ft_times();
	philo->count_p_eat++;
	pthread_mutex_unlock(&(philo->data->mutex));
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->data->philos[(philo->id)
		% philo->data->nb_philo].fork);
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
