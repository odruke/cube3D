/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/19 18:01:29 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	torad(int x)
{
	return (x / (180.0 / M_PI));
}

int	toangle(double x)
{
	return (x * (180.0 / M_PI));
}

void	draw_player(t_data *data, int x, int y, int color)
{
	int	i;
	int	u;
	int	arrow_x;
	int	arrow_y;
	float	cos_angle;
	float	sin_angle;
	int	arrow_length;

	// Draw player square
	u = y;
	while (u - y <= 5)
	{
		i = x;
		if ((u - y) % 5 == 0)
		{
			while (i - x <= 5)
			{
				put_pixel(data, i, u, color);
				i++;
			}
		}
		else
		{
			while (i - x <= 5)
			{
				if (i - x == 0 || i - x == 5)
					put_pixel(data, i, u, color);
				i++;
			}
		}
		u++;
	}
	
	// Draw direction arrow
	arrow_length = 12;
	// 90° points up, 0° points right, 180° points left, 270° points down
	cos_angle = cos(data->player->angle);  // Subtract 90° to make 90° point up
	sin_angle = -sin(data->player->angle);
	
	// Calculate arrow tip position
	arrow_x = x + 2 + (int)(cos_angle * arrow_length);
	arrow_y = y + 2 + (int)(sin_angle * arrow_length);
	
	// Draw arrow line from center to tip
	i = 0;
	while (i <= arrow_length)
	{
		int line_x = x + 2 + (int)(cos_angle * i);
		int line_y = y + 2 + (int)(sin_angle * i);
		put_pixel(data, line_x, line_y, 0xFF0000);
		i++;
	}
	
	// Draw arrow head (two small lines)
	for (i = 1; i <= 5; i++)
	{
		int head_x1 = arrow_x - (int)(cos_angle * i) + (int)(sin_angle * i);
		int head_y1 = arrow_y - (int)(sin_angle * i) - (int)(cos_angle * i);
		int head_x2 = arrow_x - (int)(cos_angle * i) - (int)(sin_angle * i);
		int head_y2 = arrow_y - (int)(sin_angle * i) + (int)(cos_angle * i);
		put_pixel(data, head_x1, head_y1, 0xFF0000);
		put_pixel(data, head_x2, head_y2, 0xFF0000);
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	u;
	
	u = 0;
	while (u < data->map->height)
	{
		i = 0;
		while (i < data->map->width && data->map->grid[u][i])
		{
			if ((data->map->grid)[u][i] == '1')
				draw_square(data, i * SQUARE_WIDTH, u * SQUARE_HEIGHT, 0xFFFFFF);
			i++;
		}
		u++;
	}
}

void	player_movement(t_data *data)
{
	int 	speed;
    double angle_speed;
    float cos_angle;
    float sin_angle;

	speed = 1;
	angle_speed = torad(1);
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
	
    if (data->player->key_up)
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

int	loop_hook(t_data *data)
{
	player_movement(data);
	clear_display(data);
	draw_map(data);
	draw_player(data, data->player->pos.x, data->player->pos.y, 0xFFFF00);
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
	return (0);
}

void	generate_world(t_data *data)
{
	data->player->pos.x *= SQUARE_WIDTH;
	data->player->pos.y *= SQUARE_HEIGHT;
	data->mlx.mlx_img.pixel_arr = mlx_get_data_addr(data->mlx.mlx_img.img, &data->mlx.mlx_img.bpp
		, &data->mlx.mlx_img.line, &data->mlx.mlx_img.endian);
	draw_map(data);
	draw_player(data, data->player->pos.x, data->player->pos.y, 0xFFFF00);
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
}

