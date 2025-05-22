# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 19:29:32 by maoliiny          #+#    #+#              #
#    Updated: 2025/05/22 18:44:34 by maoliiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = push_swap.c \
	   operations.c \
	   ps_utils.c \
	   turk_and_cost.c \
	   mini_sort.c \
	   small_turk.c

LIBFT_SRCS = libft_max/ft_atoi.c \
			 libft_max/ft_bzero.c \
			 libft_max/ft_calloc.c \
			 libft_max/ft_isalnum.c \
			 libft_max/ft_isalpha.c \
			 libft_max/ft_isascii.c \
			 libft_max/ft_isdigit.c \
			 libft_max/ft_isprint.c \
			 libft_max/ft_itoa.c \
			 libft_max/ft_lstadd_back_bonus.c \
			 libft_max/ft_lstadd_front_bonus.c \
			 libft_max/ft_lstclear_bonus.c \
			 libft_max/ft_lstdelone_bonus.c \
			 libft_max/ft_lstiter_bonus.c \
			 libft_max/ft_lstlast_bonus.c \
			 libft_max/ft_lstmap_bonus.c \
			 libft_max/ft_lstnew_bonus.c \
			 libft_max/ft_lstsize_bonus.c \
			 libft_max/ft_memchr.c \
			 libft_max/ft_memcmp.c \
			 libft_max/ft_memcpy.c \
			 libft_max/ft_memmove.c \
			 libft_max/ft_memset.c \
			 libft_max/ft_printf.c \
			 libft_max/ft_printf_utils.c \
			 libft_max/ft_putchar_fd.c \
			 libft_max/ft_putendl_fd.c \
			 libft_max/ft_putnbr_fd.c \
			 libft_max/ft_putstr_fd.c \
			 libft_max/ft_split.c \
			 libft_max/ft_strdup.c \
			 libft_max/ft_striteri.c \
			 libft_max/ft_strjoin.c \
			 libft_max/ft_strlcat.c \
			 libft_max/ft_strlcpy.c \
			 libft_max/ft_strlen.c \
			 libft_max/ft_strncmp.c \
			 libft_max/ft_strnstr.c \
			 libft_max/ft_strrchr.c \
			 libft_max/ft_strtrim.c \
			 libft_max/ft_substr.c \
			 libft_max/ft_strmapi.c \
			 libft_max/ft_tolower.c \
			 libft_max/ft_toupper.c \
			 libft_max/get_next_line.c \
			 libft_max/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
.SECONDARY = $(OBJS) 
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
.SECONDARY = $(LIBFT_OBJS) 
INCLUDES = -I./libft_max

all: $(NAME)

$(NAME): $(OBJS) libft_max/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft_max/libft.a -o $(NAME)

libft_max/libft.a: $(LIBFT_OBJS)
	@make -C libft_max

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make clean -C libft_max

fclean: clean
	rm -f $(NAME)
	rm -f libft_max/libft.a
	@make fclean -C libft_max

re: fclean all

.PHONY: all clean fclean re

