/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:49:23 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/09 14:05:33 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft_max/libft.h"
# include <stdlib.h>

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

typedef struct num_array
{
	long	*stack;
	size_t	size;
}			t_pss;
/* operations */
void		ft_swap(long *a, long *b);
void		top_swap(t_pss stack);
void		swap_op(const char *name, t_pss *stack);
void		ss(t_pss a, t_pss b);
void		rotate(char *name, t_pss *stack);
void		pp(const char *op_name, t_pss *from, t_pss *to);
void		rrotate(char *name, t_pss *stack);
void		dual_rotate(const char *name, t_pss a, t_pss b);
/* push_swap.c */
void		print_error_and_exit(long *a, long *b);
/*utils*/
long		ft_min(t_pss a);
long		ft_max(t_pss a);
#endif
