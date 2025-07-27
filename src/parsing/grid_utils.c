/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:58:47 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/27 21:58:50 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_player(char c)
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

bool	player_founded(t_coords *coords, t_coords *ret)
{
	ret->y = coords->y;
	ret->x = coords->x;
	return (true);
}

char	**copy_grid(char **grid, int max_y)
{
	int		y;
	char	**ff_grid;

	y = -1;
	ff_grid = (char **)safe_calloc(sizeof(char *),
			max_y + 1, __FILE__, __LINE__);
	while (++y < max_y)
		ff_grid[y] = ft_strdup(grid[y]);
	return (ff_grid);
}

bool	validate_corner(char **grid, int x, int y)
{
	if (y > 0 && x > 0)
		if (grid[y -1][x -1] == '0')
			return (false);
	if (grid[y + 1] && x > 0)
		if (grid[y + 1][x - 1] == '0')
			return (false);
	if (!grid[y][x] || grid[y][x + 1] == ' ')
		return (true);
	if (y > 0 && grid[y][x + 1])
		if (grid[y -1][x + 1] == '0')
			return (false);
	if (grid[y + 1] && grid[y][x + 1])
		if (grid[y + 1][x + 1] == '0')
			return (false);
	return (true);
}

void	find_player_error(char **grid, bool player_found)
{
	if (player_found)
	{
		free_table(grid);
		error_handle(ERR_GRID_BAD_ITEM, "multiple players", __FILE__, __LINE__);
	}
	else
	{
		free_table(grid);
		error_handle(ERR_GRID_BAD_ITEM, "player not found", __FILE__, __LINE__);
	}
}
