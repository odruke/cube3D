#include "cub3d.h"

void	debug_print_grid(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
		printf("%s\n", grid[i]);
}

void	debug_print_texture_path(t_elements *elements)
{
	printf("path to NO is: %s\n", elements->path_texture_no);
	printf("path to SO is: %s\n", elements->path_texture_so);
	printf("path to WE is: %s\n", elements->path_texture_we);
	printf("path to EA is: %s\n", elements->path_texture_ea);
}

void	debug_print_colors(t_elements *elements)
{
	int	r;
	int	g;
	int	b;

	r = elements->c_color->r;
	g = elements->c_color->g;
	b = elements->c_color->b;
	printf("Ceiling color is: R=%i, G=%i, B=%i\n", r, g, b);
	r = elements->f_color->r;
	g = elements->f_color->g;
	b = elements->f_color->b;
	printf("Floor color is: R=%i, G=%i, B=%i\n", r, g, b);
}
