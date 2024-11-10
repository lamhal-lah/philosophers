/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:55:42 by lamhal            #+#    #+#             */
/*   Updated: 2024/11/08 21:00:25 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	intailse_data(t_data *data, int *input, int ac)
{
	data->nbr_ph = input[0];
	data->tm_dth = input[1];
	data->tm_eat = input[2];
	data->tm_slp = input[3];
	if (ac == 6)
		data->nbr_to_eat = input[4];
	else
		data->nbr_to_eat = -1;
	free(input);
	data->frk = malloc(sizeof(pthread_mutex_t) * data->nbr_ph);
	if (!data->frk)
		return (ft_putstr_fd("failled alocation", 2), 1);
	if (pthread_mutex_init(&data->prnt_mtx, NULL) != 0)
		return (free(data->frk),
			ft_putstr_fd("failled to intialse mutex\n", 2), 1);
	if (pthread_mutex_init(&data->dead_mtx, NULL) != 0)
		return (free(data->frk), pthread_mutex_destroy(&data->prnt_mtx),
			ft_putstr_fd("failled to intialse mutex\n", 2), 1);
	data->dead = 0;
	return (0);
}

void	ft_destroy(t_philo *philo, int index, int status)
{
	if (status == 0)
		pthread_mutex_destroy(philo[index].frst_frk);
	while (index--)
	{
		pthread_mutex_destroy(philo[index].frst_frk);
		pthread_mutex_destroy(&philo[index].mls_mtx);
	}
}

int	intailse_philos(t_data *data, t_philo *philo)
{
	int		i;
	size_t	time;

	i = -1;
	time = get_current_time();
	while (++i < data->nbr_ph)
	{
		philo[i].start = time;
		philo[i].tm_lst_meal = time;
		philo[i].id = i + 1;
		philo[i].frst_frk = &data->frk[i];
		philo[i].nbr_meals = 0;
		philo[i].full = 0;
		if (pthread_mutex_init(philo[i].frst_frk, NULL) != 0)
			return (ft_putstr_fd("mutex failled to intailise\n", 2),
				ft_destroy(philo, i, 0), 1);
		if (pthread_mutex_init(&philo[i].mls_mtx, NULL) != 0)
			return (ft_putstr_fd("mutex failled to intailise\n", 2),
				ft_destroy(philo, i + 1, 1), 1);
		philo[i].scnd_frk = &data->frk[(i + 1) % data->nbr_ph];
		philo[i].data = data;
	}
	return (0);
}
