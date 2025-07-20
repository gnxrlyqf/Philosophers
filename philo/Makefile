CC = cc
CFLAGS = -Wall -Wextra -Werror 
INC = -I./includes
LIB = -lc -lpthread
SRC = src/actions.c src/init.c src/main.c src/parse.c src/threads.c src/utils.c
NAME = philo

.PHONY: all clean fclean re bonus
.SECONDARY:

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	$(CC) $^ $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC:.c=.o) $(BONUS:.c=.o)

fclean: clean
	rm -rf $(NAME) $(BNAME)

re: fclean all