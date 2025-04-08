PURP = \033[1;35m
SPURP = \033[35m
RESET = \033[0m

NAME = fractol

CC_FLGS = cc -Wall -Werror -Wextra -lm
LIB_PATH = includes/libft
MLX_PATH = includes/minilibx-linux

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBFT = $(LIB_PATH)/libft.a
MLX = $(MLX_PATH)/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_FILES)
	@$(CC_FLGS) -o $@ $^ -L$(LIB_PATH) -lft -L$(MLX_PATH) -lmlx -lXext -lX11
	@echo "$(SPURP)\n---------------------OBJECTS CREATED---------------------\n$(RESET)"
	@echo "$(PURP)\n---------------------$(NAME) CREATED---------------------\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC_FLGS) -I$(INC_DIR) -I$(LIB_PATH) -I$(MLX_PATH) -c -o $@ $<
	@echo "$(SPURP)\n---------------------OBJECT DIRECTORY CREATED---------------------\n$(RESET)"

$(LIBFT):
	@make -C $(LIB_PATH)
	@echo "$(SPURP)\n---------------------LIBFT CREATED---------------------\n$(RESET)"

$(MLX):
	@make -C $(MLX_PATH)
	@echo "$(SPURP)\n---------------------MLX CREATED---------------------\n$(RESET)"

clean:
	@make -C $(LIB_PATH) clean
	@make -C $(MLX_PATH) clean
	@rm -r $(OBJ_DIR)
	@echo "$(SPURP)\n---------------------OBJECTS DELETED---------------------\n$(RESET)"

fclean: clean
	@make -C $(LIB_PATH) fclean
	@echo "$(SPURP)\n---------------------LIBFT DELETED---------------------\n$(RESET)"
	@rm $(NAME)
	@echo "$(SPURP)\n---------------------$(NAME) DELETED---------------------\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re
