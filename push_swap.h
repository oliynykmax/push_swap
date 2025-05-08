/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:49:23 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/08 15:04:14 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
#include "libft_max/libft.h"

# define SA "sa"
# define SB "sb"
# define PA "pa"
# define PB "pb"
# define RR "rr"
# define RRR "rrr"
# define RRA "rra"
# define RRB "rrb"
# define RA "ra"
# define RB "rb"
/* operations */
void	ft_swap(long *a, long *b);
void	top_swap(long *stack, size_t size);
void	swap_op(const char *name, long *stack, size_t size);
void	ss(long *a, long *b, size_t sizea, size_t sizeb);
void	pp(const char *op_name, long *from, size_t size_from, long *to);
void	rotate(char *name, long *stack, size_t size);
void	rrotate(char *name, long *stack, size_t size);
void	dual_rotate(const char *name, long *a, size_t size_a, long *b,
			size_t size_b);
/* push_swap.c */
void	print_error_and_exit(long *a, long *b);

#endif
