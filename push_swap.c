/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:15:41 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/12 10:42:23 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_pss	fill_a(int ac, char **av)
{
	t_pss	a;
	int		i;

	a.stack = malloc(sizeof(long) * (ac));
	a.size = ac;
	i = 0;
	if (!a.stack)
		print_error_and_exit(NULL, NULL);
	while (i < ac)
	{
		if (str_isdigit(av[i]))
		{
			a.stack[i] = ft_atoi(av[i]);
			if (a.stack[i] > 2147483647 || a.stack[i] < -2147483648)
			{
				print_error_and_exit(a.stack, NULL);
			}
		}
		else
			print_error_and_exit(a.stack, NULL);
		i++;
	}
	if (is_duplicate(a.stack, ac))
		print_error_and_exit(a.stack, NULL);
	return (a);
}

size_t	find_b_target_idx(t_pss b, long num_to_push)
{
	size_t	i;
	size_t	target_idx;
	long	best_fit_val;

	if (b.size == 0)
		return (0);
	if (num_to_push > ft_max(b) || num_to_push < ft_min(b))
		return (find_index(b, ft_max(b)));
	target_idx = find_index(b, ft_max(b));
	best_fit_val = LONG_MIN;
	i = 0;
	while (i < b.size)
	{
		if (b.stack[i] < num_to_push && b.stack[i] > best_fit_val)
		{
			best_fit_val = b.stack[i];
			target_idx = i;
		}
		i++;
	}
	return (target_idx);
}

int	main(int ac, char **argv)
{
	t_pss	a;
	t_pss	b;
	size_t	min_pos;

	if (ac < 2)
		return (0);
	a = fill_a(ac - 1, &argv[1]);
	if (ft_is_sort(a))
		return (free(a.stack), 0);
	b.stack = ft_calloc(ac - 1, sizeof(long));
	if (!b.stack)
		print_error_and_exit(a.stack, NULL);
	b.size = 0;
	if (a.size <= 5)
		small_turk(&a, &b);
	else
		turk_sort(&a, &b);
	if (a.size > 0 && !ft_is_sort(a))
	{
		min_pos = find_index(a, ft_min(a));
		rotate_to_top(&a, min_pos, 1);
	}
	free(a.stack);
	free(b.stack);
}
