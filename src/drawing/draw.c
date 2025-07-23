/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/23 16:53:06 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	torad(int x)
{
	return (x / (180.0 / M_PI));//OLD. is this the correct formula [degree to radian] ?
	// return ((x * M_PI) / 180.0);
}

int	toangle(double x)
{
	return (x * (180.0 / M_PI));//OLD. is this the correct formula [radian to degree] ?
	// return ((x / M_PI) /180.0);
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
		put_pixel(data, line_x, line_y, RED);
		i++;
	}

	// Draw arrow head (two small lines)
	for (i = 1; i <= 5; i++)
	{
		int head_x1 = arrow_x - (int)(cos_angle * i) + (int)(sin_angle * i);
		int head_y1 = arrow_y - (int)(sin_angle * i) - (int)(cos_angle * i);
		int head_x2 = arrow_x - (int)(cos_angle * i) - (int)(sin_angle * i);
		int head_y2 = arrow_y - (int)(sin_angle * i) + (int)(cos_angle * i);
		put_pixel(data, head_x1, head_y1, RED);
		put_pixel(data, head_x2, head_y2, RED);
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
				draw_square(data, i * SQUARE_WIDTH, u * SQUARE_HEIGHT, WHITE);
			i++;
		}
		u++;
	}
}

void	draw_ray(t_data *data, float x_pos, float y_pos, float angle)
{
	float	ray_y;
	float	ray_x;
	float	cos_angle;
    float	sin_angle;

	ray_y = y_pos;
	ray_x = x_pos;
	cos_angle = cos(angle);//make it to calculate at each loop iteration outside functions
	sin_angle = -sin(angle);//and pass to all functions to improve performance
	while (!touch(ray_x, ray_y, data->map->grid))
	{
		put_pixel(data, ray_x, ray_y, GREEN);
		ray_y += sin_angle;
		ray_x += cos_angle;
	}
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}
void	draw_wall_line(t_data *data, float x_pos, float y_pos, float angle, int i)
{
	float	ray_y;
	float	ray_x;
	float	cos_angle;
    float	sin_angle;
	float	dist;
	float	height;
	int	start_y;
	int	end_y;

	ray_y = y_pos;
	ray_x = x_pos;
	cos_angle = cos(angle);//make it to calculate at each loop iteration outside functions
	sin_angle = -sin(angle);//and pass to all functions to improve performance
	while (!touch(ray_x, ray_y, data->map->grid))
	{
		ray_y += sin_angle;
		ray_x += cos_angle;
	}
	dist = distance(ray_x - x_pos, ray_y - y_pos);
	height = (SQUARE_HEIGHT / dist) * (WIN_WIDTH / 2);
	start_y = (WIN_HEIGHT - height) / 2;
	end_y = start_y + height;
	while (start_y < end_y)
	{
		put_pixel(data, i, start_y, BLUE);
		start_y++;
	}
}

void	draw_pov(t_data *data)
{
	float	start;
	float	fraction;
	int		i;

	fraction = M_PI / 3 / WIN_WIDTH;
	// Center the field of view on the player's angle
	start = data->player->angle - (M_PI / 3) / 2;  // Start at left edge of 60° FOV
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_wall_line(data, data->player->pos.x, data->player->pos.y, start, i);
		start += fraction;
		i++;
	}
}

void cone_of_view(t_data *data)
{
	float	start;
	float	fraction;
	int		i;

	fraction = M_PI / 3 / WIN_WIDTH;
	// Center the field of view on the player's angle
	start = data->player->angle - (M_PI / 3) / 2;  // Start at left edge of 60° FOV
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_ray(data, data->player->pos.x, data->player->pos.y, start);
		start += fraction;
		i++;
	}
}

int	loop_hook(t_data *data)
{
	player_movement(data);
	clear_display(data);
	if (DEBUG)
	{
		draw_map(data);
		draw_player(data, data->player->pos.x, data->player->pos.y, YELLOW);
		cone_of_view(data);
	}
	else
		draw_pov(data);
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
	draw_player(data, data->player->pos.x, data->player->pos.y, YELLOW);
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
}

