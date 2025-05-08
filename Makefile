NAME = push_swap

SRCS = push_swap.c
#BONUS_C = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 

#BONUS = ${BONUS_C:.c=.o}
#.SECONDARY: ${BONUS}

OBJS = ${SRCS:.c=.o}
.SECONDARY: ${OBJS}

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

all:	${NAME}

.c.o:
	${CC} ${CFLAGS} -I. -c $< -o ${<:.c=.o}

$(NAME):
	${CC} ${CFLAGS} ${SRCS} libft.a -I. -o ${NAME}

run: ${NAME}
	./${NAME} 2 3 2345235 7 9 1 23 123 618765871

clean:
	${RM} ${NAME}

fclean:	clean
	${RM} ${NAME}
	
re:		fclean all

.PHONY: all clean fclean re
