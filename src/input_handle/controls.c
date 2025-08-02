/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:39:26 by stripet           #+#    #+#             */
/*   Updated: 2025/07/31 14:04:07 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	double	dx;

	dx = data->mouse->x - x;
	if (dx > 0)
	{
		data->player->angle += torad(dx) * data->mouse->sens;
	}
	else if (dx < 0)
	{
		data->player->angle += torad(dx) * data->mouse->sens;
	}
	data->mouse->x = x;
	data->mouse->y = y;
	return (0);
}

int	enter_win(t_data *data)
{
	data->mouse->x = data->mlx->mlx_img->img_w / 2;
	data->mouse->y = data->mlx->mlx_img->img_h / 2;
	mlx_mouse_move(data->mlx->mlx_tunnel, data->mlx->window,
		data->mouse->x, data->mouse->y);
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		free_and_exit(data, EXIT_SUCCESS);
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
	else if (keycode == LEFT_SHIFT)
		data->player->boost = true;
	else if (keycode == UP_ARROW)
	{
		if (data->mouse->sens < 2)
			data->mouse->sens += 0.1;
	}
	else if (keycode == DOWN_ARROW)
	{
		if (data->mouse->sens > 0.2)
			data->mouse->sens -= 0.1;
	}
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
	else if (keycode == LEFT_SHIFT)
		data->player->boost = false;
	return (0);
}
