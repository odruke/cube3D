/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:39:26 by stripet           #+#    #+#             */
/*   Updated: 2025/07/25 23:37:59 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	int dx;

    (void)y;
	dx = data->mouse->x - x;
	if (dx > 0)
		data->player->angle += torad(3);
	else if (dx < 0)
		data->player->angle -= torad(3);
	data->mouse->x = x;
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		free_and_exit(data);
	else if (keycode == UP_KEY_W)
		data->player->key_up = true;
	else if (keycode == DOWN_KEY_S)
		data->player->key_down = true;
	else if (keycode == LEFT_KEY_A)
		data->player->key_left = true;
	else if (keycode == RIGHT_KEY_D)
		data->player->key_right = true;
	else if (keycode == LEFT_ARROW)
		data->player->left_rotate = true;
	else if (keycode == RIGHT_ARROW)
		data->player->right_rotate = true;
	else if (keycode == 105)
		printf("X Y is equal to %f %f and Angle is equal to %i\n",data->player->pos.x, data->player->pos.y, toangle(data->player->angle));
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == UP_KEY_W)
		data->player->key_up = false;
	else if (keycode == DOWN_KEY_S)
		data->player->key_down = false;
	else if (keycode == LEFT_KEY_A)
		data->player->key_left = false;
	else if (keycode == RIGHT_KEY_D)
		data->player->key_right = false;
	else if (keycode == LEFT_ARROW)
		data->player->left_rotate = false;
	else if (keycode == RIGHT_ARROW)
		data->player->right_rotate = false;
	return (0);
}
