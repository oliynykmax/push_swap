/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:15:41 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/05 18:55:59 by maoliiny         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_max/libft.h"

int	str_isdigit(const char *s)
{
	int	len;

	len = 0;
	if (*s == '-' || *s == '+')
	{
		len++;
		s++;
	}
	while (*s)
		if (ft_isdigit(*s++) == 0)
			return (0);
	if (ft_strlen(s) - len < 11)
		return (1);
	return (0);
}

void	print_error_and_exit(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

long	*fill_a(int ac, char **av)
{
	long	*a;
	int		i;

	a = malloc(sizeof(int) * ac);
	i = 0;
	if (!a)
		return (NULL);
	while (i < ac)
	{
		if (str_isdigit(av[i]))
		{
			a[i] = ft_atoi(av[i]);
			if (a[i] > 2147483647 || a[i] < -2147483648)
				print_error_and_exit();
		}
		i++;
	}
	return (a);
}

int	main(int ac, char **argv)
{
	long	*a;

	if (ac < 2)
		return (0);
	a = fill_a(ac - 1, &argv[1]);
	for (int i = 0; i < ac - 1; i++)
		ft_printf("num: %i\n", a[i]);
	free(a);
}
