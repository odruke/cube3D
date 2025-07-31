/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:33:05 by tienshi           #+#    #+#             */
/*   Updated: 2025/07/31 00:11:11 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_move(t_data *data, double x1, double y1, double x2, double y2)// not sure it works
{
	t_coords	p1;
	t_coords	d_dist;
	t_coords	step;
	t_coords	side_d;
	double		cos_a;
	double		sin_a;
	int			xp1;
	int			yp1;

	/*store original ray position*/
	p1.x = x1 / SQUARE;  // Convert to grid coordinates
	p1.y = y1 / SQUARE;  // Convert to grid coordinates
	xp1 = (int)(x1 / SQUARE);
	yp1 = (int)(y1 / SQUARE);
	cos_a = cos(data->player->angle);
	sin_a = -sin(data->player->angle);
	d_dist.x = fabs(1.0f / cos_a);
	d_dist.y = fabs(1.0f / sin_a);

	if (cos_a < 0)
	{
		step.x = -1;
		side_d.x = (p1.x - xp1) * d_dist.x;
	}
	else
	{
		step.x = 1;
		side_d.x = ((xp1 + 1.0f) - p1.x) * d_dist.x;
	}
	if (sin_a < 0)
	{
		step.y = -1;
		side_d.y = (p1.y - yp1) * d_dist.y;
	}
	else
	{
		step.y = 1;
		side_d.y = ((yp1 + 1.0f) - p1.y) * d_dist.y;
	}

	while (xp1 <= x2 / SQUARE && yp1 <= y2 / SQUARE)
	{
		if (side_d.x < side_d.y)
		{
			side_d.x += d_dist.x;
			xp1 += step.x;
		}
		else
		{
			side_d.y += d_dist.y;
			yp1 += step.y;
		}
		if (data->map->grid[yp1][xp1] == '1')
			return (false);
	}
	return (true);
}

static void	next_move(t_move move, t_coords *coords,
	const double cos_angle, const double sin_angle)
{
	float	speed;

	speed = 1;
	if (move == UP)
	{
		coords->x += cos_angle * speed;
		coords->y += sin_angle * speed;
	}
	else if (move == DOWN)
	{
		coords->x -= cos_angle * speed;
		coords->y -= sin_angle * speed;
	}
	else if (move == LEFT)
	{
		coords->x += sin_angle * speed;
		coords->y -= cos_angle * speed;
	}
	else if (move == RIGHT)
	{
		coords->x -= sin_angle * speed;
		coords->y += cos_angle * speed;
	}
}

static void	move(t_move move, t_data *data, double cos_angle, double sin_angle)
{
	t_coords	coords;

	coords.x = data->player->pos.x;
	coords.y = data->player->pos.y;

	next_move(move, &coords, cos_angle, sin_angle);
	if (is_valid_move(data, data->player->pos.x, data->player->pos.y,
			coords.x, coords.y))
	{
		data->player->pos.x = coords.x;
		data->player->pos.y = coords.y;
	}
}

void	player_movement(t_data *data)
{
	double	angle_speed;
	double	cos_angle;
	double	sin_angle;

	angle_speed = torad(1);
	if (data->player->left_rotate)
		data->player->angle += angle_speed;
	if (data->player->right_rotate)
		data->player->angle -= angle_speed;
	if (data->player->angle > torad(360))
		data->player->angle = 0;
	if (data->player->angle < 0)
		data->player->angle = torad(360);
	cos_angle = cos(data->player->angle);
	sin_angle = -sin(data->player->angle);

	if (data->player->key_up)
		move(UP, data, cos_angle, sin_angle);
	if (data->player->key_down)
		move(DOWN, data, cos_angle, sin_angle);
	if (data->player->key_left)
		move(LEFT, data, cos_angle, sin_angle);
	if (data->player->key_right)
		move(RIGHT, data, cos_angle, sin_angle);
}
