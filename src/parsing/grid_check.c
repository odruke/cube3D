#include "cub3d.h"


char	**copy_grid(char **grid, int max_y)
{
	int		y;
	char	**ff_grid;

	y = -1;
	ff_grid = (char **)safe_calloc(sizeof(char *), max_y + 1, __FILE__, __LINE__);
	while (++y < max_y)
		ff_grid[y] = ft_strdup(grid[y]);
	return (ff_grid);
}

static bool	is_player(char c)
{
	char	*player;

	player = "NSEW";
	while (*player)
	{
		if (*player == c)
			return (true);
		player++;
	}

	return (false);
}

void	find_player_error(char **grid)
{
	free_table(grid);
	error_handle(ERR_GRID_BAD_ITEM, "multiple players", __FILE__, __LINE__);
}
t_coords	find_player(char **grid, int max_y, int max_x)
{
	t_coords	coords;
	int			y;
	int			x;
	bool		check;

	y = -1;
	check = false;
	while (++y < max_y)
	{
		x = -1;
		while (grid[y][++x] && x < max_x)
			if (is_player(grid[y][x]))
			{
				if (!check)
				{
					check = true;
					coords.x = x;
					coords.y = y;
				}
				else
					find_player_error(grid);
			}
	}
	return (coords);
}

static bool validate_pos(char **grid, t_coords start, t_coords max)
{
	int	y;
	int	x;

	y = start.y;
	x = start.x;
	if (!grid[y][x] || ft_isblank(grid[y][x]))
		return (false);
	if (( y == 0 && grid[y][x] == '0') || ( x == 0 && grid[y][x] == '0'))
		return (false);
	if (( y == (max.y - 1) && grid[y][x] == '0') || ( x == (max.x - 1) && grid[y][x] == '0'))
		return (false);
	return (true);
}

static void	flood_fill(char **grid, t_coords start, t_coords max)
{
	int	y;
	int	x;

	y = start.y;
	x = start.x;
	if (grid[y][x] == '1' || grid[y][x] == 'x')
		return ;
	if (!validate_pos(grid, start, max))
	{
		free_table(grid);
		error_handle(ERR_GRID_BAD_ITEM, "wall is open", __FILE__, __LINE__);
	}
	grid[start.y][start.x] = 'x';
	y -= 1;
	if (y >= 0)
		flood_fill(grid, (t_coords){start.y - 1, start.x}, max);
	y += 2;
	if (y < max.y)
		flood_fill(grid, (t_coords){start.y + 1, start.x}, max);
	x -= 1;
	if (x >= 0)
		flood_fill(grid, (t_coords){start.y, start.x - 1}, max);
	x += 2;
	if (x < max.x)
		flood_fill(grid, (t_coords){start.y, start.x + 1}, max);
}
/* also returns player position */
t_coords	valid_grid(char **grid, int y, int x)
{
	t_coords player_coords;
	t_coords max;

	max.y = y;
	max.x = x;
	player_coords = find_player(grid, y, x);
	flood_fill(grid, player_coords, max);
	return player_coords;
}


