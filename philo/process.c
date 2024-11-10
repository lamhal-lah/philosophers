/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:50:30 by lamhal            #+#    #+#             */
/*   Updated: 2024/11/08 20:32:58 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_printf(t_philo *philo, char *str)
{
	int	i;

	pthread_mutex_lock(&philo->data->prnt_mtx);
	pthread_mutex_lock(&philo->data->dead_mtx);
	i = philo->data->dead;
	pthread_mutex_unlock(&philo->data->dead_mtx);
	if (i)
		return (pthread_mutex_unlock(&philo->data->prnt_mtx),
			pthread_mutex_unlock(philo->frst_frk), 1);
	printf("%zu %d %s", get_time_def(philo->start), philo->id, str);
	pthread_mutex_unlock(&philo->data->prnt_mtx);
	return (0);
}

void	*monitoring(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	while (1)
	{
		if (check_if_dead(philo) || check_full(philo))
			return (NULL);
	}
	return (NULL);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mtx);
	if (philo->data->dead == 1)
		return (pthread_mutex_unlock(&philo->data->dead_mtx), 1);
	pthread_mutex_unlock(&philo->data->dead_mtx);
	pthread_mutex_lock(philo->frst_frk);
	if (ft_printf(philo, "has taken a fork\n"))
		return (1);
	if (philo->data->nbr_ph == 1)
		return (1);
	pthread_mutex_lock(philo->scnd_frk);
	if (ft_printf(philo, "has taken a fork\n"))
		return (1);
	if (ft_printf(philo, "is eating\n"))
		return (1);
	pthread_mutex_lock(&philo->mls_mtx);
	philo->tm_lst_meal = get_current_time();
	philo->nbr_meals++;
	pthread_mutex_unlock(&philo->mls_mtx);
	ft_usleep(philo->data->tm_eat, philo);
	pthread_mutex_unlock(philo->frst_frk);
	pthread_mutex_unlock(philo->scnd_frk);
	return (0);
}

void	*philosipher(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->tm_eat, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->mls_mtx);
		if (philo->nbr_meals == philo->data->nbr_to_eat)
		{
			philo->full = 1;
			pthread_mutex_unlock(&philo->mls_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->mls_mtx);
		if (eat(philo))
			break ;
		if (ft_printf(philo, "is sleeping\n"))
			break ;
		ft_usleep(philo->data->tm_slp, philo);
		if (ft_printf(philo, "is thinking\n"))
			break ;
	}
	return (NULL);
}

int	philos(t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < philo[0].data->nbr_ph)
	{
		if (pthread_create(&philo[i].thread, NULL, &philosipher, &philo[i]))
			return (ft_putstr_fd("creation of threads failed\n", 2), 1);
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitoring, philo))
		return (ft_putstr_fd("creation of threads failed\n", 2), 1);
	i = 0;
	while (i < philo[0].data->nbr_ph)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (ft_putstr_fd("join of threads failed\n", 2), 1);
		i++;
	}
	if (pthread_join(monitor, NULL))
		return (ft_putstr_fd("join of threads failed\n", 2), 1);
	return (0);
}
