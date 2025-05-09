/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:58:40 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/09 19:07:57 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_op(const char *name, t_pss *stack)
{
	ft_printf("%s\n", name);
	if (stack->size == 0 || stack->size == 1)
		return ;
	else
		ft_swap(&stack->stack[0], &stack->stack[1]);
}

void	ft_swap(long *a, long *b)
{
	long	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	top_swap(t_pss stack)
{
	if (stack.size == 0 || stack.size == 1)
		return ;
	else
		ft_swap(&stack.stack[0], &stack.stack[1]);
}

void	print_error_and_exit(long *a, long *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	ft_is_sort(t_pss a)
{
	size_t	i;

	i = 0;
	while (i < a.size - 1)
	{
		if (a.stack[i] - a.stack[i + 1] > 0)
			return (0);
		i++;
	}
	return (1);
}
