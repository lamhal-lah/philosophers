/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:44:50 by lamhal            #+#    #+#             */
/*   Updated: 2024/11/08 21:12:44 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_putstr_fd("git time of day\n", 2), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;
	size_t	tmp;

	start = get_current_time();
	tmp = start;
	while (tmp - start < time)
	{
		pthread_mutex_lock(&philo->data->dead_mtx);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_mtx);
		tmp = get_current_time();
		usleep(100);
	}
	return (0);
}

size_t	get_time_def(size_t time)
{
	return (get_current_time() - time);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr_ph)
	{
		pthread_mutex_lock(&philo[i].mls_mtx);
		if (get_current_time() - philo[i].tm_lst_meal
			>= philo[i].data->tm_dth && !philo[i].full)
		{
			pthread_mutex_lock(&philo[i].data->dead_mtx);
			philo->data->dead = 1;
			pthread_mutex_lock(&philo[i].data->prnt_mtx);
			printf("%zu %d is dead\n", get_time_def(philo->start), i + 1);
			pthread_mutex_unlock(&philo[i].data->prnt_mtx);
			pthread_mutex_unlock(&philo[i].data->dead_mtx);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].mls_mtx);
		i++;
	}
	return (0);
}

int	check_full(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr_ph)
	{
		pthread_mutex_lock(&philo[i].mls_mtx);
		if (!philo[i].full)
			return (pthread_mutex_unlock(&philo[i].mls_mtx), 0);
		pthread_mutex_unlock(&philo[i].mls_mtx);
		i++;
	}
	return (1);
}
