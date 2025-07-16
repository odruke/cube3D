/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:23:46 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/16 15:52:17 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <limits.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# define WIN_WIDTH 1601
# define WIN_HEIGHT 801
# define SQUARE_WIDTH 20
# define SQUARE_HEIGHT 20
# define DEBUG 1
# define BUFFER_SIZE 50
# define RESET 1
# define CONTINUE 0
# define ESC_KEY 65307
# define UP_KEY_W 119
# define DOWN_KEY_S 115
# define LEFT_KEY_A 97
# define RIGHT_KEY_D 100
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

typedef enum e_error
{
	ERR_BAD_ARGS,
	ERR_MALLOC,
	ERR_MLX,
	ERR_LOAD_MAP,
	ERR_MAP_EXT,
	ERR_MAP_ELEM,
	ERR_GRID_BAD_ITEM,
	ERR_UNKNOWN
}	t_error;

typedef struct s_coords
{
	int	y;
	int	x;
}	t_coords;

typedef struct s_camera
{
	t_coords	pos;
}	t_camera;

typedef	struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_elements
{
	char		*path_texture_no;
	char		*path_texture_so;
	char		*path_texture_we;
	char		*path_texture_ea;
	t_color		*f_color;
	t_color		*c_color;
}	t_elements;

typedef struct s_map
{
	int			width;
	int			height;
	char		**grid;
	t_elements	*elements;
}	t_map;

typedef struct s_mlx_img
{
	void	*img;
	char	*pixel_arr;
	int		bpp;
	int		line;
	int		endian;
}	t_mlx_img;

typedef struct s_mlx
{
	void		*mlx_tunnel;
	void		*window;
	t_mlx_img	mlx_img;
	int			w;
	int			h;
}	t_mlx;

typedef struct s_data
{
	t_mlx		mlx;
	t_camera	player;
	t_map		*map;
}	t_data;

typedef struct s_fd
{
	int		fd;
	char	*filename;
}	t_fd;


char	*get_next_line(t_fd fd, int reset);
/* V data management funcitons V*/

void	init_data(t_data *data, char *map_to_load);
t_data	*recover_data_address(t_data *data);

/* map handeling functions */

void	init_map(t_map *map, char *filemap);

/* parsing helpers and validation functions */

bool	is_grid_char(char c);
bool	line_is_grid(char *line);
bool	line_is_only_spaces(char *line);
int		check_grid(t_fd fd);
bool	valid_ext(char *filemap);
char	*skip_until_grid(t_fd fd);
bool	get_texture_paths(t_elements *elements, t_fd fd);
bool	get_colours(t_elements *elements, t_fd fd);
void	zeroing_endstring(char **str);
bool	color_is_in_range(char *code, int start, int len);
bool	valid_grid(char **grid, int y, int x);

/* flood fill and helpers */

char	**copy_grid(char **grid, int max_y);


/* error handeling and exiting functions*/

int		error_handle(t_error error, char *msg, char *file, int line);
void	free_table(char **table);
void	free_data(t_data *data);
int		free_and_exit(t_data *data);
void	free_list(t_list **list, void (*del)(void *));//?

/* error controled functions */

void	*safe_malloc(size_t bytes, char *file, int line);
void	*safe_calloc(size_t bytes, size_t size, char *file, int line);

/*game control functions*/

int		handle_keypress(int keycode, t_data *data);
int		count_table(char **table);//?


/*on-screen printing functions*/

void	generate_world(void);
void	generate_grid(void);
void	draw_player(void);

/* debug functions */

void	debug_print_grid(char **grid);
void	debug_print_texture_path(t_elements *elements);
void	debug_print_colors(t_elements *elements);

#endif
