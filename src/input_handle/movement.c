/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:32:42 by odruke-s          #+#    #+#             */
/*   Updated: 2025/08/04 16:19:00 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_move_with_radius(t_data *data, t_coords new_pos)
{
	float		player_radius;
	t_coords	check_points[8];
	int			i;
	float		angle;

	player_radius = SQUARE * 0.03f;
	i = -1;
	while (++i < 8)
	{
		angle = (i * TWO_PI) / 8.0f;
		check_points[i].x = new_pos.x + cos(angle) * player_radius;
		check_points[i].y = new_pos.y + sin(angle) * player_radius;
		if (!point_valid(data->map, check_points[i]))
			return (false);
	}
	return (true);
}

void	calc_pos(t_move move, t_coords *coords,
	const float *cos_angle, const float *sin_angle)
{
	float	speed;

	speed = get_speed();
	if (move == UP)
	{
		coords->x += *cos_angle * speed;
		coords->y += *sin_angle * speed;
	}
	else if (move == DOWN)
	{
		coords->x -= *cos_angle * speed;
		coords->y -= *sin_angle * speed;
	}
	else if (move == LEFT)
	{
		coords->x += *sin_angle * speed;
		coords->y -= *cos_angle * speed;
	}
	else if (move == RIGHT)
	{
		coords->x -= *sin_angle * speed;
		coords->y += *cos_angle * speed;
	}
}

void	sliding_move(t_data *data, t_coords *original_pos, t_coords *new_pos)
{
	t_coords	x_only;
	t_coords	y_only;

	if (fabs(new_pos->x - original_pos->x)
		> 0.1f && fabs(new_pos->y - original_pos->y) > 0.1f)
	{
		x_only = *original_pos;
		x_only.x = new_pos->x;
		if (validate_move_with_radius(data, x_only))
		{
			data->player->pos = x_only;
			return ;
		}
		y_only = *original_pos;
		y_only.y = new_pos->y;
		if (validate_move_with_radius(data, y_only))
		{
			data->player->pos = y_only;
			return ;
		}
	}
}

void	displace(t_move move, t_data *data,
	const float cos_angle, const float sin_angle)
{
	t_coords	new_pos;
	t_coords	original_pos;

	original_pos = data->player->pos;
	new_pos = original_pos;
	calc_pos(move, &new_pos, &cos_angle, &sin_angle);
	if (validate_move_with_radius(data, new_pos))
	{
		data->player->pos = new_pos;
		return ;
	}
	sliding_move(data, &original_pos, &new_pos);
}

void	player_movement(t_data *data)
{
	double	angle_speed;
	float	cos_angle;
	float	sin_angle;

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
		displace(UP, data, cos_angle, sin_angle);
	if (data->player->key_down)
		displace(DOWN, data, cos_angle, sin_angle);
	if (data->player->key_left)
		displace(LEFT, data, cos_angle, sin_angle);
	if (data->player->key_right)
		displace(RIGHT, data, cos_angle, sin_angle);
}
