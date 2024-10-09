NAME = cub3d

GAME_DIR = game
UI_DIR = ui
PARS_DIR = parsing
STRUCT_DIR = structs
UTIL_DIR = utils
BIN_DIR = bin
HDR_DIR = includes

GAME_FILES = events.c
UI_FILES = window.c images.c raycasting.c render.c
PARS_FILES = map.c parse_design.c parse_utils.c parse_map.c parse_utils2.c
STRUCT_FILES = data.c map.c img.c player.c coord.c
UTIL_FILES =  error.c

SRCS = main.c \
	$(addprefix $(GAME_DIR)/,$(GAME_FILES)) \
	$(addprefix $(UI_DIR)/,$(UI_FILES)) \
	$(addprefix $(PARS_DIR)/,$(PARS_FILES)) \
	$(addprefix $(STRUCT_DIR)/,$(STRUCT_FILES)) \
	$(addprefix $(UTIL_DIR)/,$(UTIL_FILES))

OBJS = $(SRCS:%.c=$(BIN_DIR)/%.o)

MLX_LINUX = mlx_linux/libmlx.a
MLX_MACOS = mlx_macos/libmlx.a
LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g
CC = cc $(CFLAGS)

INCLUDES = -I libft

BOLD = \033[1m
GRAY = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    INCLUDES += -I mlx_linux -I includes
    MFLAGS = -L mlx_linux -l mlx -l Xext -l X11 -lm -lz
    MLX = $(MLX_LINUX)
else ifeq ($(UNAME_S), Darwin)
    INCLUDES += -I mlx_macos -I includes
    MFLAGS = -L mlx_macos -l mlx -framework OpenGL -framework AppKit
    MLX = $(MLX_MACOS)
else
    $(error Operating system not supported)
endif

all: $(MLX) $(LIBFT) $(NAME)

$(BIN_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(INCLUDES) -c $< -o $@

$(MLX_LINUX):
	@echo "$(YELLOW)Building minilibx...$(RESET)"
	@make -s -C mlx_linux
	@echo "$(GREEN)Building complete!$(RESET)"

$(MLX_MACOS):
	@echo "$(YELLOW)Building minilibx...$(RESET)"
	@make -s -C mlx_macos
	@echo "$(GREEN)Building complete!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -s -C libft
	@echo "$(GREEN)Building complete!$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@echo "\n$(YELLOW)Linking objects...$(RESET)"
	@$(CC) -o $(NAME) $^ $(MFLAGS)
	@echo "$(BLUE)Progress: 100%$(RESET)"
	@echo "$(GREEN)Compilation complete!$(RESET)"
	@echo "\n\
	█▀▀ █░░█ █▀▀▄$(RED) █▀▀█ █▀▀▄$(RESET)\n\
	█░░ █░░█ █▀▀▄$(RED) ░░▀▄ █░░█$(RESET)\n\
	▀▀▀ ░▀▀▀ ▀▀▀░$(RED) █▄▄█ ▀▀▀░$(RESET)\n"

clean:
	@echo "$(BLUE)Cleaning objects...$(RESET)"
	@rm -rf $(BIN_DIR)
	@make clean -s -C mlx_linux
	@make clean -s -C mlx_macos
	@make clean -s -C libft
	@echo "$(GREEN)Cleaning complete!$(RESET)"

fclean: clean
	@echo "$(BLUE)Complete cleanup..."
	@rm -f $(NAME)
	@make fclean -s -C libft
	@echo "$(GREEN)Cleaning complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
