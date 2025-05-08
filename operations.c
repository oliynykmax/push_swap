/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:03:39 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/08 15:03:03 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ss(long *a, long *b, size_t sizea, size_t sizeb)
{
	ft_printf("ss\n");
	top_swap(a, sizea);
	top_swap(b, sizeb);
}

// void	pp(long *from, size_t size_from, long *to)
// {
// 	if (size_from == 0)
// 		return ;
// 	else
// 		ft_swap(&from[0], &to[0]);
// }
//
// void	pa(long *a, long *b, size_t sizeb)
// {
// 	ft_printf("pa\n");
// 	pp(b, sizeb, a);
// }
//
// void	pb(long *a, long *b, size_t sizea)
// {
// 	ft_printf("pa\n");
// 	pp(a, sizea, b);
// }

void	pp(const char *op_name, long *from, size_t size_from, long *to)
{
	if (size_from == 0)
		return ;
	ft_printf("%s\n", op_name);
	ft_swap(&from[0], &to[0]);
}

void	rotate(char *name, long *stack, size_t size)
{
	size_t	i;
	long	first;

	i = 0;
	if (size < 2)
		return ;
	first = stack[0];
	while (i < size - 1)
	{
		stack[i] = stack[i + 1];
		i++;
	}
	stack[size - 1] = first;
	if (name != NULL)
		ft_printf("%s\n", name);
}

void	rrotate(char *name, long *stack, size_t size)
{
	size_t	i;
	long	last;

	i = 0;
	if (size < 2)
		return ;
	last = stack[size - 1];
	while (i < size - 1)
	{
		stack[i + 1] = stack[i];
		i++;
	}
	stack[0] = last;
	if (name != NULL)
		ft_printf("%s\n", name);
}

void	dual_rotate(const char *name, long *a, size_t size_a, long *b,
		size_t size_b)
{
	if (ft_memcmp(name, "rr", ft_strlen(name)) == 0)
	{
		rotate(NULL, a, size_a);
		rotate(NULL, b, size_b);
	}
	else if (ft_memcmp(name, "rrr", ft_strlen(name)) == 0)
	{
		rrotate(NULL, a, size_a);
		rrotate(NULL, b, size_b);
	}
	ft_printf("%s\n", name);
}
