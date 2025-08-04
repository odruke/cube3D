/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:15:08 by odruke-s          #+#    #+#             */
/*   Updated: 2025/08/04 18:15:11 by odruke-s         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_open_wall(char **grid, int pos_x, int pos_y, t_coords limits)
{
	if (pos_y == limits.y || pos_y == 0)
		return (true);
	if (pos_x == limits.x || pos_x == 0)
		return (true);
	if (ft_isblank(grid[pos_y - 1][pos_x]) || ft_isblank(grid[pos_y + 1][pos_x]))
		return (true);
	if (ft_isblank(grid[pos_y][pos_x - 1]) || ft_isblank(grid[pos_y][pos_x + 1]))
		return (true);
	return (false);
}

void	walled(char **grid, int width, int heigh)
{
	int	y;
	int	x;

	y = -1;
	while (grid[++y])
	{
		x = -1;
		while (grid[y][++x])
		{
			if (grid[y][x] == '0')
				if (is_open_wall(grid, x, y, (t_coords){heigh, width}))
					error_handle(ERR_GRID_BAD_ITEM, "open wall", __FILE__, __LINE__);
		}
	}
}
