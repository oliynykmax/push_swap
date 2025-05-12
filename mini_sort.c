/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:08:26 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/09 19:09:56 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_pss *a)
{
	long	max;

	if (a->size <= 1)
		return ;
	if (a->size == 2)
	{
		if (a->stack[0] > a->stack[1])
			swap_op(SA, a);
		return ;
	}
	max = ft_max(*a);
	if (a->stack[0] == max)
		rotate(RA, a);
	else if (a->stack[1] == max)
		rrotate(RRA, a);
	if (a->stack[0] > a->stack[1])
		swap_op(SA, a);
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

size_t	find_index(t_pss stack, long target)
{
	size_t	i;

	i = 0;
	while (i < stack.size)
	{
		if (stack.stack[i] == target)
			return (i);
		i++;
	}
	return (0);
}
