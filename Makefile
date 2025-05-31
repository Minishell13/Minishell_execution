NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L./Libft -lft -lreadline -lncurses 

INC_DIR = ./includes
TEST_DIR = ./test
LIBFT_DIR = ./Libft
SRC_DIR = ./srcs
SETUP_DIR = $(SRC_DIR)/setup
SIG_DIR = $(SRC_DIR)/signals
AST_DIR = $(SRC_DIR)/ast
EXEC_DIR = $(SRC_DIR)/execution
EXPAND_DIR = $(SRC_DIR)/expansion
BUILT_DIR = $(EXEC_DIR)/builtins
INCLUDES = -I${INC_DIR} -I./Libft/includes
LIBFT = $(LIBFT_DIR)/libft.a

# TODO: Just for testing !!!
TEST =	$(TEST_DIR)/expand.c $(TEST_DIR)/arr_utils.c $(TEST_DIR)/builtins.c \
		$(TEST_DIR)/execution.c $(TEST_DIR)/setup.c $(TEST_DIR)/signals.c

BUILTINS =	$(BUILT_DIR)/builtins.c $(BUILT_DIR)/utils.c $(BUILT_DIR)/env.c $(BUILT_DIR)/export.c $(BUILT_DIR)/unset.c $(BUILT_DIR)/pwd.c \
			$(BUILT_DIR)/echo.c $(BUILT_DIR)/exit.c $(BUILT_DIR)/cd.c

EXPAND =	$(EXPAND_DIR)/expand.c $(EXPAND_DIR)/utils.c $(EXPAND_DIR)/utils/expand_modes.c \
			$(EXPAND_DIR)/utils/extract_value.c $(EXPAND_DIR)/utils/expand_heredoc.c

EXEC =	$(BUILTINS) $(EXPAND) $(EXEC_DIR)/executor.c $(EXEC_DIR)/exec_cmd.c $(EXEC_DIR)/exec_pipeline.c $(EXEC_DIR)/exec_redirection.c \
		$(EXEC_DIR)/exec_subshell.c $(EXEC_DIR)/exec_and_or.c $(EXEC_DIR)/utils/heredoc_utils.c $(EXEC_DIR)/utils/path_utils.c $(EXEC_DIR)/utils/redir_utils.c

AST =  $(AST_DIR)/ast.c $(AST_DIR)/ast_examples.c

SIG = $(SIG_DIR)/signals.c

SETUP = $(SETUP_DIR)/setup.c

SRCS =	$(TEST) $(SETUP) $(SIG) $(AST) $(EXEC)  $(SRC_DIR)/cleanup/cleanup.c \
		$(SRC_DIR)/debug/debugging.c $ $(SRC_DIR)/exit/errors.c


OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o minishell $(LDFLAGS)

%.o: %.c ${INC_DIR}/minishell.h ${INC_DIR}/execution.h ${INC_DIR}/expand.h ${INC_DIR}/builtins.h ${INC_DIR}/signals.h ${INC_DIR}/setup.h ${INC_DIR}/typedef.h ${INC_DIR}/redirections.h
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
