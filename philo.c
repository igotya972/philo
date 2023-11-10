/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:13:14 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/10 05:34:55 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_args(int ac, char **av, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (ac > 6 || ac < 5)
		ft_error(data, "ARGS");
	while (av[++i])
	{
		if (!av[i][0])
		{
			ft_error(data, "ARGS NULL");
		}
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				ft_error(data, "invalid nb");
	}
	if (av[1][0] < '1')
		ft_error(data, "invalid nb philo");
}

void	ft_supervise(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		usleep(25);
		pthread_mutex_lock(&data->mutex);
		while (++i < data->nb_philo)
		{
			if (ft_satiate(data, i) || ft_check_death(data, i))
			{
				pthread_mutex_unlock(&data->mutex);
				return ;
			}
		}
		pthread_mutex_unlock(&data->mutex);
	}
}

void	*ft_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	if ((philo->id % 2) == 0)
		ft_usleep(philo->data->time_to_eat / 2);
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
		if (philo->data->end == 1)
			return (NULL);
		ft_monitoring(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		ft_monitoring(philo, "is thinking");
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_check_args(ac, av, data);
	ft_init_data(av, data);
	ft_init_philo(data);
	ft_start_philo(data);
	ft_free(data);
	return (0);
}
