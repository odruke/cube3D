###VARIABLES###

# name of the executable
NAME = cub3D

# compilator and compilation flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I ./include
LDFLAGS = -L ./libft -L ./mlx
LDLIBS = -lmlx -lft -lXext -lX11 -lm -lz

# variables
src_dir = ./src
obj_dir = ./obj

# source files (recursively find all .c files)
SRCS = $(shell find $(src_dir) -name "*.c")
OBJS = $(addprefix $(obj_dir)/,$(notdir $(SRCS:.c=.o)))

###RULES###
all: $(NAME)

$(NAME): libft/libft.a mlx/libmlx.a $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@ 

# Create object files from source files
$(obj_dir)/%.o: $(src_dir)/*/%.c | $(obj_dir)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(obj_dir)/%.o: $(src_dir)/%.c | $(obj_dir)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
	$(MAKE) -C mlx clean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re