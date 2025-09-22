# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

# OS Detection
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    MLX_DIR    = ./minilibx-linux
    MLX_FLAGS  = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME_S), Darwin)
    MLX_DIR    = ./minilibx_macos
    MLX_FLAGS  = -L$(MLX_DIR) -framework OpenGL -framework AppKit
endif

# Includes
LIBFT     = ./libft/libft.a
INCLUDES  = -I./ -I./libft -I$(MLX_DIR)
RM        = rm -rf
NAME      = cub3D
OBJ_DIR   = obj

# Sources
SRCS = main.c \
       parser/argument_validation.c \
       parser/color_parsing.c \
       parser/cub3d_parsing.c \
       parser/data_init.c \
       parser/element_parsing.c \
       parser/map_parsing.c \
       parser/parse_free.c \
       parser/parsing_utils.c \
       parser/validate_map.c \
	   parser/store_cub.c \
       parser/xpm_to_img.c \
       render/coll_utils.c \
       render/collisions.c \
       render/draw_walls.c \
       render/put_line.c \
       render/raycasting.c \
       render/render_keys.c \
       render/utils.c \
       render/movement.c \
       render/draw_walls_utils.c \
       render/free_render.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Color output
GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

# Default target
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C ./libft > /dev/null
	@echo "$(YELLOW)Compiling MLX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

# Compile .o files into obj/ folder
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(MAKE) clean -C ./libft > /dev/null
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Removing executable...$(RESET)"
	@$(MAKE) fclean -C ./libft > /dev/null
	@$(RM) $(NAME)
	@echo "$(GREEN)Clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re