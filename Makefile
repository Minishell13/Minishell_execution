NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./Libft -lft -lreadline -lncurses
SRC_DIR = ./srcs
INCLUDES = -I./includes -I./Libft/includes
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

EXEC =	$(SRC_DIR)/execution/executor.c $(SRC_DIR)/execution/exec_cmd.c $(SRC_DIR)/execution/exec_pipeline.c $(SRC_DIR)/execution/exec_utils.c \
		$(SRC_DIR)/execution/exec_redirection.c $(SRC_DIR)/execution/exec_subshell.c $(SRC_DIR)/execution/exec_and_or.c

SRCS =	$(EXEC) $(SRC_DIR)/main.c $(SRC_DIR)/ast/ast.c $(SRC_DIR)/cleanup/cleanup.c \
		$(SRC_DIR)/debug/debugging.c $(SRC_DIR)/ast/ast_examples.c $(SRC_DIR)/exit/errors.c

# SRCS =	$(SRC_DIR)/main.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/ast.c \
# 		$(SRC_DIR)/debugging.c
	
OBJS = $(SRCS:.c=.o)


all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o minishell $(LDFLAGS)

%.o: %.c ./includes/minishell.h ./includes/execution.h
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
