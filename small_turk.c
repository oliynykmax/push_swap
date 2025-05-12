/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_turk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:21:30 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/12 11:22:50 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_turk(t_pss *a, t_pss *b)
{
	if (a->size <= 3)
	{
		sort_three(a);
		return ;
	}
	while (a->size > 3)
	{
		rotate_to_top(a, find_index(*a, ft_min(*a)), 1);
		pp(PB, a, b);
	}
	sort_three(a);
	while (b->size > 0)
		pp(PA, b, a);
}
