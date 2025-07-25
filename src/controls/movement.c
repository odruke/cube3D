#include "cub3d.h"

bool	valid_move(t_map *map, int x, int y)
{
	char	*valid_pos;
	char	pos;

	y = y / SQUARE_HEIGHT;
	x = x / SQUARE_WIDTH;
	if (y < 0 || y > map->height || x < 0 || x > map->width)
		return (false);
	valid_pos = "NSWE0";//maybe we should change the NSWE to 0 when we parse ?
	pos = map->grid[y][x];
	while (*valid_pos)
	{
		if (*valid_pos == pos)
			return (true);
		valid_pos++;
	}
	return (false);
}

void	calc_pos(t_move move, t_coords *coords,
	const float *cos_angle, const float *sin_angle)
{
	int		speed;

	speed = 1;
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

void	displace(t_move move, t_data *data,
	const float cos_angle, const float sin_angle)
{
	t_coords	coords;

	coords.x = data->player->pos.x;
	coords.y = data->player->pos.y;

	calc_pos(move, &coords, &cos_angle, &sin_angle);
	if (valid_move(data->map, coords.x, coords.y))
	{
		data->player->pos.x = coords.x;
		data->player->pos.y = coords.y;
	}
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
