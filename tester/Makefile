
###VARIABLES###

# name of the executable
NAME = cube_tester

# compilator and compilation flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g


# directories
SRC_DIR = ./src/
OBJ_DIR = $(SRC_DIR)target/
INC_DIR = ./inc/

# files
FILES = utils.c main.c get_next_line.c
INC_FILES = cube_test.h
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
INC = $(addprefix $(INC_DIR)%.h, $(INC_FILES))

#####RULES####

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@$(MAKE) compilation_success

# create .o file
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "Compiling: %s                                    \r" $<
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	printf "Starting compilation..."
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

# executes clean and deletes the executable
fclean: clean
	@rm -f $(NAME)

re: fclean all

compilation_success:
	@echo "┌────────────────────────────────────────────────────────────────────────┐"
	@echo "│ ██████╗██╗   ██╗██████╗ ███████╗     ████████╗███████╗███████╗████████╗│"
	@echo "│██╔════╝██║   ██║██╔══██╗██╔════╝     ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝│"
	@echo "│██║     ██║   ██║██████╔╝█████╗          ██║   █████╗  ███████╗   ██║   │"
	@echo "│██║     ██║   ██║██╔══██╗██╔══╝          ██║   ██╔══╝  ╚════██║   ██║   │"
	@echo "│╚██████╗╚██████╔╝██████╔╝███████╗███████╗██║   ███████╗███████║   ██║   │"
	@echo "│ ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚══════╝╚═╝   ╚══════╝╚══════╝   ╚═╝   │"
	@echo "└────────────────────────────────────────────────────────────────────────┘"

.PHONY: clean fclean re all compilation_success
