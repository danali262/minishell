NAME = minishell

SRC = \
	src/main.c \
	src/reader/read_command_line.c \
	src/reader/command_line_aux.c \
	src/reader/set_term_attr.c \
	src/reader/keys.c\
	src/reader/handle_keys.c \
	src/reader/shell_utilities.c\
	src/term_cap/init_terminal_data.c \
	src/command_history/update_history.c \
	src/command_history/prev_history.c \
	src/command_history/next_history.c \
	src/command_history/history_aux.c \
	src/parser/parse_command_line.c \
	src/parser/lexer/lexer_aux.c \
	src/parser/lexer/lexer.c \
	src/parser/lexer/lexer2.c \
	src/parser/lexer/lexer3.c \
	src/parser/lexer/lexer4.c \
	src/parser/lexer/utilities.c\
	src/parser/parser.c\
	src/parser/parser2.c\
	src/parser/parser3.c\
	src/parser/parser4.c\
	src/parser/parser5.c\
	src/parser/parser_aux.c\
	src/parser/astree.c \
	src/executor/execute_command.c \
	src/executor/builtins/builtins.c


OBJS = $(SRC:.c=.o)
# remove the flags for amd processor and debugging
CFLAGS = -Wall -Werror -Wextra  -O0 -g -target x86_64-apple-macos10.12 

INCLUDES =	./libft

CC = gcc

all: $(NAME)

$(NAME):	$(OBJS) $(INCLUDES)
			make -C libft/
			cp libft/libft.a .
			$(CC) -ltermcap -Llibft -lft \
			-o $(NAME) $(OBJS) $(CFLAGS)
			# $(CC) $(CFLAGS) -o $(NAME) $(OBJS) -ltermcap -Llibft -lft

%.o:	%.c
			$(CC) $(CFLAGS) -Ilibft/include -Isrc -c $< -o $@

clean:
			rm -f $(OBJS)
			make clean -C libft

fclean: 	clean
			rm -f libft.a
			rm -f libft/libft.a
			rm -f $(NAME)

re: fclean all 
    