/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:15:41 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/09 15:39:23 by maoliiny         ###   ########.fr       */
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

void	sort_five(t_pss *a, t_pss *b)
{
	while (a->stack[0] != ft_min(*a))
		rotate(RA, a);
	pp(PB, a, b);
	while (a->stack[0] != ft_max(*a))
		rotate(RA, a);
	pp(PB, a, b);
	if (a->size > 0)
	{
		while (a->stack[a->size - 1] != ft_max(*a))
			rotate(RA, a);
		if (a->stack[0] != ft_min(*a))
			swap_op(SA, a);
	}
	pp(PA, b, a);
	rotate(RA, a);
	pp(PA, b, a);
}

long	ft_max(t_pss a)
{
	size_t	i;
	long	max;

	i = 1;
	if (a.size == 0)
		return (-2147483649);
	max = a.stack[0];
	while (i < a.size)
	{
		if (a.stack[i] > max)
			max = a.stack[i];
		i++;
	}
	return (max);
}

long	ft_min(t_pss a)
{
	size_t	i;
	long	min;

	i = 1;
	min = a.stack[0];
	if (a.size == 0)
		return (2147483649);
	while (i < a.size)
	{
		if (a.stack[i] < min)
			min = a.stack[i];
		i++;
	}
	return (min);
}

size_t	find_pos(t_pss b, long num)
{
	size_t	pos;
	size_t	i;

	pos = 0;
	i = 0;
	if (b.size == 0)
		return (0);
	while (i < b.size)
	{
		if (num < b.stack[i])
			pos++;
		i++;
	}
	return (pos);
}

void	turk_sort(t_pss *a, t_pss *b)
{
	size_t	pos;
	int		num;

	pp(PB, a, b);
	pp(PB, a, b);
	if (ft_max(*b) != b->stack[0])
		swap_op(SB, b);
	while (a->size != 0)
	{
		pos = find_pos(*b, a->stack[0]);
		if (pos == 0)
			pp(PB, a, b);
		else if (pos == b->size)
		{
			pp(PB, a, b);
			rotate(RB, b);
		}
		else
		{
			num = find_pos(*b, a->stack[0]);
			for (int i = num; i > 0; i--)
				rotate(RB, b);
			pp(PB, a, b);
			for (int i = num; i > 0; i--)
				rrotate(RRB, b);
		}
	}
	while (b->size != 0)
		pp(PA, b, a);
}

int	main(int ac, char **argv)
{
	t_pss	a;
	t_pss	b;

	if (ac < 2)
		return (0);
	a = fill_a(ac - 1, &argv[1]);
	b.stack = ft_calloc(ac - 1, sizeof(long));
	b.size = 0;
	if (a.size <= 5)
		sort_five(&a, &b);
	else
		turk_sort(&a, &b);
	free(a.stack);
	free(b.stack);
}
