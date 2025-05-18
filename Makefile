CC = cc
CFLAGS = -Wall -Wextra -g #-Werror
INC = -I./includes
LIB = -lc -lpthread
SRC = $(wildcard src/*.c)
NAME = philo

.PHONY: all clean fclean re bonus
.SECONDARY:

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	$(CC) $^ -lc -o $(NAME)

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC:.c=.o) $(BONUS:.c=.o)

fclean: clean
	rm -rf $(NAME) $(BNAME)

re: fclean all