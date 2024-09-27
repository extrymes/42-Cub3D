NAME = cub3d

UI_DIR = ui
UI_FILES = window.c
UI_SRCS = main.c $(addprefix $(UI_DIR)/,$(UI_FILES))

PARS_DIR = parsing
PARS_FILES = map.c parse_design.c parse_utils.c
PARS_SRCS = main.c $(addprefix $(PARS_DIR)/,$(PARS_FILES))

STRUCT_DIR = structs
STRUCT_FILES = data.c map.c
STRUCT_SRCS = $(addprefix $(STRUCT_DIR)/,$(STRUCT_FILES))

UTIL_DIR = utils
UTIL_FILES =  error.c
UTIL_SRCS = $(addprefix $(UTIL_DIR)/,$(UTIL_FILES))

OBJS = $(UI_SRCS:.c=.o) $(PARS_SRCS:.c=.o) $(STRUCT_SRCS:.c=.o) $(UTIL_SRCS:.c=.o)
HDR_DIR = includes

MINILIBX_DIR = /home/sabras/sgoinfre/minilibx
MINILIBX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11

LIBFT_DIR = libft
LIBFT_FILE = libft.a
LIBFT = $(addprefix $(LIBFT_DIR)/,$(LIBFT_FILE))

CFLAGS = -Wall -Wextra -Werror
CC = cc $(CFLAGS) -g -I $(HDR_DIR)

BOLD = \033[1m
GRAY = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

%.o: %.c
	@$(CC) -c $< -o $@
	@echo "$(GRAY)Compiled: $<$(RESET)"

all: $(NAME)

$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Building executable...$(RESET)"
	@$(CC) -lm -o $(NAME) $^ $(MINILIBX_FLAGS)
	@echo "$(GREEN)Executable $(NAME) successfully created!$(RESET)"
	@echo "$(RESET)\n\
	█▀▀ █░░█ █▀▀▄$(RED) █▀▀█ █▀▀▄$(RESET)\n\
	█░░ █░░█ █▀▀▄$(RED) ░░▀▄ █░░█$(RESET)\n\
	▀▀▀ ░▀▀▀ ▀▀▀░$(RED) █▄▄█ ▀▀▀░$(RESET)\n"

clean:
	@echo "$(BLUE)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Cleaning complete!$(RESET)"

fclean: clean
	@echo "$(BLUE)Complete cleanup..."
	@rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Cleaning complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
