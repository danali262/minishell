NAME = minishell

SRCS = utilities.c lexer.c main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all 
    