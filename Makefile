NAME	=	philo
SRC		=	main.c philo.c utils1.c philo_init.c utils2.c
OBJS 	= 	$(SRC:.c=.o)
CC 		= 	cc
CFLAGS 	=	-Wall -Wextra -Werror
RM	 	= 	rm -rf

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re