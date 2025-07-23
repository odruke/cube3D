#include "cub3d.h"

void	player_movement(t_data *data)
{
	int 	speed;
    double angle_speed;
    float cos_angle;
    float sin_angle;

	speed = 1;
	angle_speed = torad(1);
	// angle_speed = 1;
    if (data->player->left_rotate)
		data->player->angle += angle_speed;
    if (data->player->right_rotate)
		data->player->angle -= angle_speed;
    if (data->player->angle > torad(360))
		data->player->angle = 0;
    if (data->player->angle < 0)
		data->player->angle = torad(360);
	if (data->player->pos.x == 0)
		data->player->pos.x += 1;
	if (data->player->pos.y == 0)
		data->player->pos.y += 1;
	if (data->player->pos.x == WIN_WIDTH)
		data->player->pos.x -= 1;
	if (data->player->pos.y == WIN_HEIGHT)
		data->player->pos.y -= 1;
	// Use same angle calculation as arrow for consistency
	cos_angle = cos(data->player->angle);
	sin_angle = -sin(data->player->angle);


    if (data->player->key_up valid_move())
    {
        data->player->pos.x += cos_angle * speed;  // Move in arrow direction
        data->player->pos.y += sin_angle * speed;
    }
    if (data->player->key_down)
    {
        data->player->pos.x -= cos_angle * speed;  // Move opposite to arrow
        data->player->pos.y -= sin_angle * speed;
    }
    if (data->player->key_left)
    {
        data->player->pos.x += sin_angle * speed;  // Strafe left
        data->player->pos.y -= cos_angle * speed;
    }
    if (data->player->key_right)
    {
        data->player->pos.x -= sin_angle * speed;  // Strafe right
        data->player->pos.y += cos_angle * speed;
    }
}
