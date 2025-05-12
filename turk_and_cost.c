/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_and_cost.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:51:58 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/12 11:23:04 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_cost(t_pss a, t_pss b, size_t pos_a)
{
	size_t	pos_b_target;
	int		a_cost;
	int		b_cost;

	pos_b_target = find_b_target_idx(b, a.stack[pos_a]);
	a_cost = pos_a;
	if (pos_a > a.size / 2)
		a_cost = a.size - pos_a;
	b_cost = 0;
	if (b.size > 0)
	{
		b_cost = pos_b_target;
		if (pos_b_target > b.size / 2)
			b_cost = b.size - pos_b_target;
	}
	return (a_cost + b_cost + 1);
}

static size_t	find_cheapest(t_pss a, t_pss b)
{
	size_t	cheapest_pos;
	int		min_cost;
	int		current_cost;
	size_t	i;

	min_cost = INT_MAX;
	cheapest_pos = 0;
	i = 0;
	while (i < a.size)
	{
		current_cost = get_cost(a, b, i);
		if (current_cost < min_cost)
		{
			min_cost = current_cost;
			cheapest_pos = i;
		}
		i++;
	}
	return (cheapest_pos);
}

void	rotate_to_top(t_pss *s, size_t pos, int is_a)
{
	if (s->size == 0 || pos >= s->size)
		return ;
	if (pos <= s->size / 2)
	{
		while (pos > 0)
		{
			if (is_a)
				rotate(RA, s);
			else
				rotate(RB, s);
			pos--;
		}
	}
	else
	{
		pos = s->size - pos;
		while (pos > 0)
		{
			if (is_a)
				rrotate(RRA, s);
			else
				rrotate(RRB, s);
			pos--;
		}
	}
}

static size_t	find_a_target_idx(t_pss a, long val_from_b)
{
	size_t	i;
	size_t	target_idx;
	long	closest_larger_val;

	if (a.size == 0)
		return (0);
	if (val_from_b < ft_min(a))
		return (find_index(a, ft_min(a)));
	if (val_from_b > ft_max(a))
		return (find_index(a, ft_min(a)));
	target_idx = 0;
	closest_larger_val = LONG_MAX;
	i = 0;
	while (i < a.size)
	{
		if (a.stack[i] > val_from_b && a.stack[i] < closest_larger_val)
		{
			closest_larger_val = a.stack[i];
			target_idx = i;
		}
		i++;
	}
	return (target_idx);
}

void	turk_sort(t_pss *a, t_pss *b)
{
	size_t	cheapest_a_idx;
	size_t	b_target_idx;
	size_t	a_target_idx;

	pp(PB, a, b);
	pp(PB, a, b);
	sort_three(a);
	while (a->size > 3)
	{
		cheapest_a_idx = find_cheapest(*a, *b);
		b_target_idx = find_b_target_idx(*b, a->stack[cheapest_a_idx]);
		rotate_to_top(a, cheapest_a_idx, 1);
		rotate_to_top(b, b_target_idx, 0);
		pp(PB, a, b);
	}
	sort_three(a);
	while (b->size > 0)
	{
		a_target_idx = find_a_target_idx(*a, b->stack[0]);
		rotate_to_top(a, a_target_idx, 1);
		pp(PA, b, a);
	}
}
