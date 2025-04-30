NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./Libft -lft -lreadline -lncurses
SRC_DIR = ./srcs
INCLUDES = -I./includes -I./Libft/includes
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	$(SRC_DIR)/main.c $(SRC_DIR)/ast.c $(SRC_DIR)/executor.c $(SRC_DIR)/cleanup.c \
		$(SRC_DIR)/debugging.c $(SRC_DIR)/ast_examples.c

# SRCS =	$(SRC_DIR)/main.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/ast.c \
# 		$(SRC_DIR)/debugging.c
	
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o minishell $(LDFLAGS)

%.o: %.c ./includes/minishell.h
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
