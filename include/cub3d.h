/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:23:46 by odruke-s          #+#    #+#             */
/*   Updated: 2025/08/01 08:34:58 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <limits.h>
# include <sys/types.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <time.h>
# ifndef DEBUG
#  define DEBUG 0
# endif
# ifndef M_PI
#  define M_PI 3.14159265358979323846
#  define M_PI 3.14159265358979323846
# endif
# define HALF_PI 1.5707963267948966f
# define THREE_HALF_PI 4.7123889803846899f
# define TWO_PI 6.2831853071795865f
# define WIN_WIDTH 1600
# define WIN_HEIGHT 800
# define SQUARE 30
# define BUFFER_SIZE 50
# define ESC_KEY 65307
# define UP_KEY_W 119
# define DOWN_KEY_S 115
# define LEFT_KEY_A 97
# define RIGHT_KEY_D 100
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define LEFT_SHIFT   65505
# define CONTINUE 0
# define RESET 1
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFF00
# define WALK 1
# define RUN 2.5

typedef struct s_dda
{
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	cos_angle;
	float	sin_angle;
	int		map_x;
	int		map_y;
}	t_dda;

typedef struct s_fps
{
	int			frame_count;
	clock_t		last_time;
	float		fps;
	char		fps_text[32];
}	t_fps;

typedef enum e_move
{
	UP,
	DOWN,
	RIGHT,
	LEFT
}	t_move;

typedef enum e_error
{
	ERR_BAD_ARGS,
	ERR_MALLOC,
	ERR_MLX,
	ERR_LOAD_MAP,
	ERR_MAP_EXT,
	ERR_MAP_ELEM,
	ERR_GRID_BAD_ITEM,
	ERR_TXTUR_OPEN,
	ERR_TXTUR_EXT,
	ERR_TXTUR_DIR,
	ERR_UNKNOWN
}	t_error;

typedef struct s_coords
{
	double	y;
	double	x;
}	t_coords;

typedef struct s_fd
{
	int		fd;
	char	*filename;
}	t_fd;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_mouse
{
	int		x;
	int		y;
	float	sens;
}	t_mouse;

typedef struct s_camera
{
	t_coords	pos;
	double		angle;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;
	bool		boost;
}	t_camera;

typedef struct s_mlx_img
{
	void	*img;
	char	*pixel_arr;
	int		bpp;
	int		line;
	int		endian;
	int		img_w;
	int		img_h;
}	t_mlx_img;

typedef struct s_texture
{
	t_mlx_img	*n_wall;
	t_mlx_img	*s_wall;
	t_mlx_img	*w_wall;
	t_mlx_img	*e_wall;
	bool		side;
	float		wall_hit;
}	t_texture;

typedef struct s_elements
{
	char		*path_texture_no;
	char		*path_texture_so;
	char		*path_texture_we;
	char		*path_texture_ea;
	t_color		*f_color;
	t_color		*c_color;
	t_texture	*textures;
}	t_elements;

typedef struct s_map
{
	int			width;
	int			height;
	char		**grid;
	t_elements	*elements;
}	t_map;

typedef struct s_mini_map
{
	int			fov;
	t_mlx_img	img;
}	t_mini_map;

typedef struct s_mlx
{
	void		*mlx_tunnel;
	void		*window;
	t_mlx_img	*mlx_img;
}	t_mlx;

typedef struct s_data
{
	t_mlx		*mlx;
	t_map		*map;
	t_camera	*player;
	t_mouse		*mouse;
	t_mini_map	*mini_map;
	t_fps		*fps;
	t_dda		*dda;
}	t_data;

t_data		*recover_data_address(t_data *data);
void		init_data(t_data *data, char *map_to_load);

/* parsing helpers and validation functions */
char		*get_next_line(t_fd fd, int reset);
bool		is_grid_char(char c);
bool		is_player(char c);
bool		player_founded(t_coords *coords, t_coords *ret);
void		find_player_error(char **grid, bool player_found);
bool		line_is_grid(char *line);
bool		line_is_only_spaces(char *line);
int			check_grid(t_fd fd);
void		check_corners(char **grid);
bool		validate_corner(char **grid, int x, int y);
bool		valid_ext(char *filemap);
char		*skip_until_grid(t_fd fd);
bool		get_texture_paths(t_elements *elements, t_fd fd);
bool		get_colours(t_elements *elements, t_fd fd);
void		zeroing_endstring(char **str);
bool		color_is_in_range(char *code, int start, int len);
void		fordward_index(char *line, int *i);
int			str_append_mem(char **s1, char *s2, size_t size2);
t_coords	valid_grid(char **grid, int y, int x);
int			get_map_height(char **grid);
int			get_map_width(char **grid);
void		init_map(t_camera *player, t_map *map, char *filemap);

/* flood fill and helpers */

char		**copy_grid(char **grid, int max_y);


/* error handeling and exiting functions*/

int			error_handle(t_error error, char *msg, char *file, int line);
void		free_table(char **table);
int			free_and_exit(t_data *data, int exit_code);

/* error controled functions */

void		*safe_malloc(size_t bytes, char *file, int line);
void		*safe_calloc(size_t bytes, size_t size, char *file, int line);
void		*safe_xpm_to_img(t_data *data, char *path, t_mlx_img *img);
char		*safe_mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
				int *size_line, int *endian);

/*game control functions*/

int			handle_keypress(int keycode, t_data *data);
int			handle_keyrelease(int keycode, t_data *data);
int			mouse_move(int x, int y, t_data *data);
int			enter_win(t_data *data);
void		player_movement(t_data *data);
void		mlx_hook_start(t_data *data);

/* movement helper functions */

float	get_speed(void);
bool	point_valid(t_map *map, t_coords point);
bool	validate_move_with_radius(t_data *data, t_coords new_pos);

/*on-screen printing functions*/

double		torad(int x);
int			toangle(double x);
void		fill_display(t_mlx_img *img, int width, int height);
void		draw_square(t_mlx_img *img, int x, int y, int size);
void		draw_full_square(t_mlx_img *img, int x, int y, int size);
void		put_pixel(t_mlx_img *img, int x, int y, int color);
int			loop_hook(t_data *data);
bool		touch(double x, double y, char **grid, int square);
int			get_hexa(t_color *color);
void		draw_pov(t_data *data);
void		draw_mini_map(t_data *data, double x, double y);
int			set_pixel_texture(t_texture *textures,
				float height, int y, float angle);
float		get_distance(t_data *data, t_coords *ray, float angle);
void		init_dda(t_dda *dda, float angle);
void		set_dda(t_dda *dda, t_coords *ray);

/* format check functions*/

void		valid_textures(t_elements *elements);


/* debug functions */

void		print_debug_data(t_data *data);
void		debug_print_grid(char **grid);
void		debug_print_texture_path(t_elements *elements);
void		debug_print_colors(t_elements *elements);
void		debug_print_player(char **grid, t_camera *player);

/* fps functions */

void	init_fps(t_fps *fps);
void	update_fps(t_fps *fps);
void	draw_fps(t_data *data);

#endif
