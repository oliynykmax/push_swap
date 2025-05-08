NAME = push_swap

SRCS = push_swap.c operations.c ps_utils.c

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
