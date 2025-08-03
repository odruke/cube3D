###VARIABLES###

# name of the executable
NAME = cub3D

# variables
src_dir = ./src
obj_dir = ./obj
DEBUG ?= 0

# compilator and compilation flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
INCLUDES = -I ./include
LDFLAGS = -L ./libft -L ./mlx
LDLIBS = -lmlx -lft -lXext -lX11 -lm -lz
DB = -DDEBUG=$(DEBUG)

# source files (recursively find all .c files)
SRCS = $(shell find $(src_dir) -name "*.c")
OBJS = $(addprefix $(obj_dir)/,$(notdir $(SRCS:.c=.o)))

###RULES###
all: $(NAME)

debug: fclean
	@$(MAKE) DEBUG=1

debug2: fclean
	@$(MAKE) DEBUG=2

$(NAME): libft/libft.a mlx/libmlx.a $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Create object files from source files
$(obj_dir)/%.o: $(src_dir)/*/%.c | $(obj_dir)
	$(CC) $(CFLAGS) $(INCLUDES) $(DB) -c $< -o $@

$(obj_dir)/%.o: $(src_dir)/%.c | $(obj_dir)
	$(CC) $(CFLAGS) $(INCLUDES) $(DB) -c $< -o $@

# Create object directory
$(obj_dir):
	mkdir -p $(obj_dir)

# Build libft
libft/libft.a:
	$(MAKE) -C libft

# Build mlx
mlx/libmlx.a:
	$(MAKE) -C mlx

# Clean object files
clean:
	rm -rf $(obj_dir)
	$(MAKE) -C libft clean

# Clean everything
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
#	$(MAKE) -C mlx clean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
