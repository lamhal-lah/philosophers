/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:30:41 by lamhal            #+#    #+#             */
/*   Updated: 2024/11/08 21:01:13 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nbr_ph;
	size_t			tm_dth;
	size_t			tm_slp;
	size_t			tm_eat;
	int				nbr_to_eat;
	int				dead;
	pthread_mutex_t	*frk;
	pthread_mutex_t	prnt_mtx;
	pthread_mutex_t	dead_mtx;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	size_t			start;
	size_t			tm_lst_meal;
	int				nbr_meals;
	int				full;
	pthread_t		thread;
	pthread_mutex_t	*frst_frk;
	pthread_mutex_t	*scnd_frk;
	pthread_mutex_t	mls_mtx;
	t_data			*data;
}	t_philo;

void	ft_putstr_fd(char *s, int fd);
int		parsing(int ac, char **av, int *input);
int		intailse_data(t_data *data, int *input, int ac);
int		intailse_philos(t_data *data, t_philo *philo);
size_t	get_current_time(void);
size_t	get_time_def(size_t time);
int		ft_usleep(size_t time, t_philo *philo);
int		check_if_dead(t_philo *philo);
int		check_full(t_philo *philo);
void	ft_destroy(t_philo *philo, int index, int status);
int		philos(t_philo *philo);

#endif