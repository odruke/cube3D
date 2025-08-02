/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:32:51 by odruke-s          #+#    #+#             */
/*   Updated: 2025/08/01 12:32:54 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_speed(void)
{
	t_data	*data;

	data = recover_data_address(NULL);
	if (data->player->boost)
		return (RUN);
	return (WALK);
}

bool	point_valid(t_map *map, t_coords point)
{
	int		grid_x;
	int		grid_y;
	char	*valid_pos;
	char	pos;

	grid_x = (int)(point.x / SQUARE);
	grid_y = (int)(point.y / SQUARE);
	if (grid_x < 0 || grid_x >= map->width
		|| grid_y < 0 || grid_y >= map->height)
		return (false);
	valid_pos = "NSWE0";
	pos = map->grid[grid_y][grid_x];
	while (*valid_pos)
	{
		if (*valid_pos == pos)
			return (true);
		valid_pos++;
	}
	return (false);
}
