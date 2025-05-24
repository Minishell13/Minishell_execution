NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L./Libft -lft -lreadline -lncurses 

INC_DIR = ./includes
TEST_DIR = ./test
LIBFT_DIR = ./Libft
SRC_DIR = ./srcs
EXEC_DIR = $(SRC_DIR)/execution
BUILT_DIR = $(EXEC_DIR)/builtins
EXPAND_DIR = $(EXEC_DIR)/expand
INCLUDES = -I${INC_DIR} -I./Libft/includes
LIBFT = $(LIBFT_DIR)/libft.a

# TODO: Just for testing !!!
TEST =	$(TEST_DIR)/expand.c $(TEST_DIR)/arr_utils.c $(TEST_DIR)/builtins.c \
		$(TEST_DIR)/execution.c $(TEST_DIR)/setup.c

BUILTINS =	$(BUILT_DIR)/env.c $(BUILT_DIR)/export.c $(BUILT_DIR)/unset.c $(BUILT_DIR)/pwd.c

EXPAND =	$(EXPAND_DIR)/expand.c $(EXPAND_DIR)/utils.c $(EXPAND_DIR)/utils/expand_modes.c \
			$(EXPAND_DIR)/utils/extract_value.c $(EXPAND_DIR)/utils/expand_heredoc.c

EXEC =	$(BUILTINS) $(EXPAND) $(EXEC_DIR)/executor.c $(EXEC_DIR)/exec_cmd.c $(EXEC_DIR)/exec_pipeline.c $(EXEC_DIR)/exec_utils.c \
		$(EXEC_DIR)/exec_redirection.c $(EXEC_DIR)/exec_subshell.c $(EXEC_DIR)/exec_and_or.c

SRCS =	$(TEST) $(EXEC) $(SRC_DIR)/setup.c $(SRC_DIR)/main.c $(SRC_DIR)/ast/ast.c $(SRC_DIR)/cleanup/cleanup.c \
		$(SRC_DIR)/debug/debugging.c $(SRC_DIR)/ast/ast_examples.c $(SRC_DIR)/exit/errors.c

	
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o minishell $(LDFLAGS)

%.o: %.c ${INC_DIR}/minishell.h ${INC_DIR}/execution.h ${INC_DIR}/expand.h
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
