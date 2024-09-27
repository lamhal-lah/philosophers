/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:54:50 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/25 14:44:12 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	
	if (fd < 0 || !s)
		return ;
	i = 0;
	while (s && s[i])
		write(fd, &s[i++], 1);
}

int	ft_atoi(char *str, int *invalid)
{
	long	nbr;

	nbr = 0;
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (*invalid = 1, 0);
		nbr = nbr * 10 + *str - 48;
		str++;
	}
	return (nbr);
}

int	parsing(int ac, char **av, int *input)
{
	int		i;
	int		invalid;

	invalid = 0;
	i = -1;
	if (ac < 5 || ac > 6)
		return (1);
	while (++i + 1 < ac)
	{
		input[i] = ft_atoi(av[1 + i], &invalid);
		if (invalid)
			return (1);
	}
	if (input[0] > 200)
		return (1);
	if (input[1] < 60 || input[2] < 60 || input[3] < 60)
		return (1);
	return (0);
}