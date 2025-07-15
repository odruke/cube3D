###VARIABLES###

# name of the executable
NAME = cub3D

# compilator and compilation flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
MFLAGS = -Lmlx -lmlx -lXext -lX11 -lm -lbsd

# directories
MAIN_DIR = main/
UTILS_DIR = utils/
ERR_DIR = error_and_free/
PARS_DIR = parsing/
SRC_DIR = ./src/
OBJ_DIR = $(SRC_DIR)target/
INC_DIR = ./include/
LIBFT_DIR = ./libft/
MLX_DIR = ./mlx/

# custom libraries
LIBFT = $(LIBFT_DIR)libft.a
MLX = $(MLX_DIR)libmlx.a

# files
MAIN_FILES = main.c
UTILS_FILES = safe_functions.c
PARSING_FILES = load_map.c parsing.c validations.c load_cardinal_textures.c parsing_utils.c debug_parsing.c load_colors.c grid_check.c
ERR_FILES = error_handle.c free_data.c free_data_utils.c
FILES = $(addprefix $(ERR_DIR), $(ERR_FILES)) \
		$(addprefix $(MAIN_DIR), $(MAIN_FILES)) \
		$(addprefix $(UTILS_DIR), $(UTILS_FILES)) \
		$(addprefix $(PARS_DIR), $(PARSING_FILES)) \

INC_FILES = cub3d.h
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
INC = $(addprefix $(INC_DIR)%.h, $(INC_FILES))



#####RULES####

all: aux_libraries $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MFLAGS) $(MLX) $(LIBFT) -o $@
	@$(MAKE) compilation_success

# create .o file
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "Compiling: %s                                    \r" $<
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	printf "Starting compilation..."
	@mkdir -p $(OBJ_DIR)

aux_libraries:
	@make -C $(MLX_DIR) -s all
	@make -C $(LIBFT_DIR) -s all

# delete just file OBJ_DIR and o file inside
clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) -s clean
	@make -C $(MLX_DIR) -s clean

# executes clean and deletes the executable
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) -s fclean

re: fclean all

compilation_success:
	@echo "╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗"
	@echo "╠╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╣"
	@echo "╠╣ ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ ╠╣"
	@echo "╠╣██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗╠╣"
	@echo "╠╣██║     ██║   ██║██████╔╝ █████╔╝██║  ██║╠╣"
	@echo "╠╣██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║╠╣"
	@echo "╠╣╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝╠╣"
	@echo "╠╣ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╠╣"
	@echo "╠╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╣"
	@echo "╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝"

.PHONY: clean fclean re all aux_libraries compilation_success
