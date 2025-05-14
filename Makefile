NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./Libft -lft -lreadline -lncurses

TEST_DIR = ./test
LIBFT_DIR = ./Libft
SRC_DIR = ./srcs
EXEC_DIR = $(SRC_DIR)/execution
EXPAND_DIR = $(EXEC_DIR)/expand

INCLUDES = -I./includes -I./Libft/includes
LIBFT = $(LIBFT_DIR)/libft.a

# TODO: Just for testing !!!
TEST = $(TEST_DIR)/expand.c $(TEST_DIR)/wildcard.c

EXPAND =	$(EXPAND_DIR)/expand_var.c
# $(EXPAND_DIR)/expand.c $(EXPAND_DIR)/expand_wildcard.c 

EXEC =	$(EXPAND) $(EXEC_DIR)/executor.c $(EXEC_DIR)/exec_cmd.c $(EXEC_DIR)/exec_pipeline.c $(EXEC_DIR)/exec_utils.c \
		$(EXEC_DIR)/exec_redirection.c $(EXEC_DIR)/exec_subshell.c $(EXEC_DIR)/exec_and_or.c

SRCS =	$(TEST) $(EXEC) $(SRC_DIR)/main.c $(SRC_DIR)/ast/ast.c $(SRC_DIR)/cleanup/cleanup.c \
		$(SRC_DIR)/debug/debugging.c $(SRC_DIR)/ast/ast_examples.c $(SRC_DIR)/exit/errors.c

# SRCS =	$(SRC_DIR)/main.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/ast.c \
# 		$(SRC_DIR)/debugging.c
	
OBJS = $(SRCS:.c=.o)


all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o minishell $(LDFLAGS)

%.o: %.c ./includes/minishell.h ./includes/execution.h ./includes/expand.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
