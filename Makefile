NAME := philo

CC := gcc

CFLAGS := -Wall -Wextra -Werror

SOURCE := philo.c init.c routine.c observer.c utils.c

OBJS := $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
