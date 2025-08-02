/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_calcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:46:03 by tienshi           #+#    #+#             */
/*   Updated: 2025/07/31 01:17:27 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	torad(int x)
{
	return (x * (M_PI / 180));
}

int	toangle(double x)
{
	return (x * (180.0 / M_PI));
}

bool	touch(double x, double y, char **grid, int square)//obsolete?
{
	int	xmap;
	int	ymap;

	xmap = x / square;
	ymap = y / square;
	if (grid[ymap][xmap] == '1')
		return (true);
	return (false);
}

double	fixed_dist(t_data *data, double x, double y, t_coords p2)//obsolete?
{
	t_coords	delta;
	double		fixed_angl;
	double		ret_val;

	delta.x = p2.x - x;
	delta.y = p2.y - y;
	fixed_angl = (atan2(delta.y, delta.x) - data->player->angle);
	ret_val = sqrt(delta.x * delta.x + delta.y * delta.y) * cos(fixed_angl);
	return (ret_val);
}
