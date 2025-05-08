/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:15:41 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/08 13:02:29 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_max/libft.h"
#include "push_swap.h"

static int	is_duplicate(const long *a, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (a[i] == a[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	str_isdigit(const char *s)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if ((s[i] == '-' || s[i] == '+') && ft_strlen(s) > 1)
	{
		len++;
		i++;
	}
	while (s[i])
		if (ft_isdigit(s[i++]) == 0)
			return (0);
	if (ft_strlen(s) - len < 13)
		return (1);
	return (0);
}

static long	*fill_a(int ac, char **av)
{
	long	*a;
	int		i;

	a = malloc(sizeof(long) * ac);
	i = 0;
	if (!a)
		print_error_and_exit(NULL, NULL);
	while (i < ac)
	{
		if (str_isdigit(av[i]))
		{
			a[i] = ft_atoi(av[i]);
			if (a[i] > 2147483647 || a[i] < -2147483648)
			{
				print_error_and_exit(a, NULL);
			}
		}
		else
			print_error_and_exit(a, NULL);
		i++;
	}
	if (is_duplicate(a, ac))
		print_error_and_exit(a, NULL);
	return (a);
}

int	main(int ac, char **argv)
{
	long	*a;
	long	*b;
	int		i;

	i = 0;
	if (ac < 2)
		return (0);
	a = fill_a(ac - 1, &argv[1]);
	b = malloc(sizeof(a) * (ac - 1));
	while (i < ac - 1)
		ft_printf("num: %i\n", a[i++]);
	free(a);
	free(b);
}
