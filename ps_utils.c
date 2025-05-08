/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:58:40 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/08 13:02:47 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_max/libft.h"

void	swap_op(const char *name, long *stack, size_t size)
{
	ft_printf("%s\n", name);
	if (size == 0 || size == 1)
		return ;
	else
		ft_swap(&stack[0], &stack[1]);
}

void	ft_swap(long *a, long *b)
{
	long	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	top_swap(long *stack, size_t size)
{
	if (size == 0 || size == 1)
		return ;
	else
		ft_swap(&stack[0], &stack[1]);
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
