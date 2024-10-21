NAME = cub3D

SRC_DIR = src
SRC_ENGINE_DIR = engine
SRC_PARS_DIR = parsing
SRC_STRUCT_DIR = structs
SRC_UTIL_DIR = utils
BIN_DIR = bin
HDR_DIR = includes

ENGINE_FILES = raycasting.c rendering.c minimap.c door.c events.c routine.c moves.c rotates.c mouse.c
PARS_FILES = map.c parse_design.c parse_utils.c parse_map.c parse_utils2.c
STRUCT_FILES = data.c map.c img.c player.c ray.c keys.c
UTIL_FILES = images.c time.c error.c

SRCS = $(addprefix $(SRC_DIR)/,main.c \
	$(addprefix $(SRC_ENGINE_DIR)/,$(ENGINE_FILES)) \
	$(addprefix $(SRC_PARS_DIR)/,$(PARS_FILES)) \
	$(addprefix $(SRC_STRUCT_DIR)/,$(STRUCT_FILES)) \
	$(addprefix $(SRC_UTIL_DIR)/,$(UTIL_FILES)))

OBJS = $(SRCS:%.c=$(BIN_DIR)/%.o)

MLX_LINUX = mlx_linux/libmlx.a
MLX_MACOS = mlx_macos/libmlx.a
LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -O3 -mtune=native -flto
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
    INCLUDES += -I mlx_linux -I includes/linux_includes
    MFLAGS = -L mlx_linux -l mlx -l Xext -l X11 -lm -lz -lXfixes
    MLX = $(MLX_LINUX)
else ifeq ($(UNAME_S), Darwin)
    INCLUDES += -I mlx_macos -I includes/macos_includes
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
