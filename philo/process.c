/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:50:30 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/25 18:55:59 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	check_if_dead(t_philo *philo)
{
	int	indcateur;

	pthread_mutex_lock(&philo->mls_mtx);
	indcateur = get_time_def(philo->tm_lst_meal) >= philo->data->tm_dth;
	pthread_mutex_unlock(&philo->mls_mtx);
	return (indcateur);
}

void	*monitoring(void *phil)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)phil;
	while(1)
	{
		i = -1;
		if (philo->nbr_meals == 0)
			break ;
		while (++i < philo->data->nbr_ph)
		{	
			if (philo[i].nbr_meals && check_if_dead(&philo[i]))
			{
				philo->data->dead = 1;
				ft_printf(&philo[i], 0);
				return (NULL);
			}
		}
		i = 0;
		while ((i < philo->data->nbr_ph || philo->data->nbr_ph == -1) && !philo[i].nbr_meals)
			i++;
		if (i == philo->data->nbr_ph)
			return (NULL);
	}
	return (NULL);
}

void	*philosipher(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	philo->start = get_current_time();
	philo->tm_lst_meal = philo->start;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->tm_eat, philo);
	while (1)
	{
		if (philo->nbr_meals == 0)
			break ;
		if (philo->data->dead == 1)
			break;
		pthread_mutex_lock(philo->frst_frk);
		if (ft_printf(philo, 4))
			break ;
		pthread_mutex_lock(philo->scnd_frk);
		if (ft_printf(philo, 4))
			break ;
		if (ft_printf(philo, 1))
			break ;
		philo->tm_lst_meal = get_current_time();
		ft_usleep(philo->data->tm_eat, philo);
		pthread_mutex_unlock(philo->frst_frk);
		pthread_mutex_unlock(philo->scnd_frk);
		pthread_mutex_lock(&philo->mls_mtx);
		philo->nbr_meals--;
		pthread_mutex_unlock(&philo->mls_mtx);
		if (ft_printf(philo, 2))
			break ;
		ft_usleep(philo->data->tm_slp, philo);
		if (ft_printf(philo, 3))
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
		if (pthread_create(&philo[i].thread, NULL, &philosipher, &philo[i]) != 0)
			return (ft_putstr_fd("creation of threads failed\n", 2), 1);
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitoring,  philo) != 0)
		return (ft_putstr_fd("creation of threads failed\n", 2), 1);
	i = 0;
	while (i < philo[0].data->nbr_ph)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (ft_putstr_fd("detach of threads failed\n", 2), 1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (ft_putstr_fd("detach of threads failed\n", 2), 1);
	return (0);
}
