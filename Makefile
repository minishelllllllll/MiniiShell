NAME = minishell
CC = cc
CFLAGS = -Werror -Wextra -Wall -fsanitize=address -g

SRC := 	$(wildcard src/parsing/*.c) \
		$(wildcard src/execution/*.c) \
		$(wildcard *.c) \
		$(wildcard libft/*.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) 

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)