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
	./${NAME} 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

clean:
	${RM} ${NAME}

fclean:	clean
	${RM} ${NAME}
	
re:		fclean all

.PHONY: all clean fclean re
