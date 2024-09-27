/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:44:50 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/25 18:38:41 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_putstr_fd("git time of day\n", 2), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t time, t_philo *philo)
{
	int		start;
	size_t	tmp;
	(void)philo;

	start = get_current_time();
	if (start == -1)
		return (1);
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
		if (start == -1)
			return (1);
		usleep(100);
	}
	return (0);
}

int	get_time_def(int time)
{
	return (get_current_time() - time);
}

int	ft_printf(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->data->prnt_mtx);
	if (n == 0)
	{
		printf("%d %d is dead\n", get_time_def(philo->start), philo->id);
		pthread_mutex_unlock(&philo->data->prnt_mtx);
		return (0);
	}
	if (philo->data->dead)
		return (pthread_mutex_unlock(&philo->data->prnt_mtx), pthread_mutex_unlock(philo->frst_frk), 1);
	if (n == 1)
		printf("%d %d is eating\n", get_time_def(philo->start), philo->id);
	else if (n == 2)
		printf("%d %d is sleeping\n", get_time_def(philo->start), philo->id);
	else if (n == 3)
		printf("%d %d is thinking\n", get_time_def(philo->start), philo->id);
	else if (n == 4)
		printf("%d %d has taking a fork\n",
			get_time_def(philo->start), philo->id);
	pthread_mutex_unlock(&philo->data->prnt_mtx);
	return (0);
}