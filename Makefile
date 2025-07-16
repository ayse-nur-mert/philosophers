NAME = philo

# Source files
SRCS = src/main.c src/utils.c src/init.c src/routine.c src/cleanup.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

# Libft
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_REPO = git@vogsphere.42istanbul.com.tr:vogsphere/intra-uuid-8b4a61a8-63e9-408b-acc3-1ff1172e3e0d-6113678-amert

# Colors for pretty output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# Rules
all: $(NAME)

$(LIBFT_DIR):
	@echo "$(BLUE)Cloning libft...$(RESET)"
	@if [ ! -d "lib" ]; then mkdir -p lib; fi
	@git clone $(LIBFT_REPO) $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✓ libft cloned successfully!$(RESET)"

$(LIBFT): $(LIBFT_DIR)
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✓ libft compiled successfully!$(RESET)"

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BLUE)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

%.o: %.c src/philo.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)
	@if [ -d $(LIBFT_DIR) ]; then make -C $(LIBFT_DIR) clean > /dev/null 2>&1; fi
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executable and library...$(RESET)"
	@$(RM) $(NAME)
	@if [ -d $(LIBFT_DIR) ]; then $(RM) -rf $(LIBFT_DIR); fi
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
