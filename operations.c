/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:03:39 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/08 17:23:20 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ss(t_pss a, t_pss b)
{
	ft_printf("ss\n");
	top_swap(a);
	top_swap(b);
}

void	pp(const char *op_name, t_pss *from, t_pss *to)
{
	if (from->size == 0)
		return ;
	ft_printf("%s\n", op_name);
	to->size = to->size + 1;
	rrotate(NULL, to);
	ft_swap(&from->stack[0], &to->stack[0]);
	rotate(NULL, from);
	from->size = from->size - 1;
}

void	rotate(char *name, t_pss *stack)
{
	size_t	i;
	long	first;
	size_t	size;

	size = stack->size;
	i = 0;
	if (size < 2)
		return ;
	first = stack->stack[0];
	while (i < size - 1)
	{
		stack->stack[i] = stack->stack[i + 1];
		i++;
	}
	stack->stack[size - 1] = first;
	if (name != NULL)
		ft_printf("%s\n", name);
}

void	rrotate(char *name, t_pss *stack)
{
	size_t	i;
	long	last;
	size_t	size;

	size = stack->size;
	if (size < 2)
		return ;
	last = stack->stack[size - 1];
	i = size - 1;
	while (i > 0)
	{
		stack->stack[i] = stack->stack[i - 1];
		i--;
	}
	stack->stack[0] = last;
	if (name != NULL)
		ft_printf("%s\n", name);
}

void	dual_rotate(const char *name, t_pss a, t_pss b)
{
	if (ft_memcmp(name, "rr", ft_strlen(name)) == 0)
	{
		rotate(NULL, &a);
		rotate(NULL, &b);
	}
	else if (ft_memcmp(name, "rrr", ft_strlen(name)) == 0)
	{
		rrotate(NULL, &a);
		rrotate(NULL, &b);
	}
	ft_printf("%s\n", name);
}
