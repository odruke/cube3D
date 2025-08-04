/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:58:15 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/27 21:58:17 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coords	find_player(char **grid, int max_y, int max_x)
{
	t_coords	coords;
	t_coords	ret_coords;
	bool		player_found;

	coords.y = -1.0f;
	player_found = false;
	while ((int)++coords.y < max_y)
	{
		coords.x = -1.0f;
		while (grid[(int)coords.y][(int)++coords.x] && coords.x < max_x)
		{
			if (is_player(grid[(int)coords.y][(int)coords.x]))
			{
				if (!player_found)
					player_found = player_founded(&coords, &ret_coords);
				else
					find_player_error(grid, player_found);
			}
		}
	}
	if (!player_found)
		find_player_error(grid, player_found);
	return (ret_coords);
}

static bool	validate_pos(char **grid, t_coords start, t_coords max)
{
	int	y;
	int	x;

	y = start.y;
	x = start.x;
	if (!grid[y][x] || ft_isblank(grid[y][x]))
		return (false);
	if ((y == 0 && grid[y][x] == '0') || (x == 0 && grid[y][x] == '0'))
		return (false);
	if ((y == (max.y - 1) && grid[y][x] == '0') || (x == (max.x - 1)
			&& grid[y][x] == '0'))
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
	grid[(int)start.y][(int)start.x] = 'x';
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

void	check_corners(char **grid)
{
	int		y;
	int		x;

	y = -1;
	while (grid[++y])
	{
		x = -1;
		while (grid[y][++x])
		{
			if (ft_isblank(grid[y][x]))
			{
				if (!validate_corner(grid, x, y))
					error_handle(ERR_GRID_BAD_ITEM, "bad corner",
						__FILE__, __LINE__);
				while (grid[y][x] && grid[y][x + 1]
					&& ft_isblank(grid[y][x + 2]))
					x++;
			}
		}
		if (!validate_corner(grid, x, y))
			error_handle(ERR_GRID_BAD_ITEM, "bad corner", __FILE__, __LINE__);
	}
}

t_coords	valid_grid(char **grid, int y, int x)
{
	t_coords	player_coords;
	t_coords	max;

	max.y = y;
	max.x = x;
	check_corners(grid);
	player_coords = find_player(grid, y, x);
	walled(grid, x, y, player_coords);
	flood_fill(grid, player_coords, max);
	return (player_coords);
}
