/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/26 13:39:15 by tienshi          ###   ########.fr       */
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
	cos_angle = cos(angle);
	sin_angle = -sin(angle);
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

float	fixed_dist(t_data *data, float x, float y, t_coords p2)
{
	t_coords	delta;
	float		fixed_angl;
	float		ret_val;

	delta.x = p2.x - x;
	delta.y = p2.y - y;
	fixed_angl = (atan2(delta.y, delta.x) + data->player->angle);
	ret_val = distance(delta.x, delta.y) * cos(fixed_angl);
	return (ret_val);
}
void	draw_wall_line(t_data *data, float x_pos, float y_pos, float angle, int i)
{
	t_coords	ray;
	float		cos_angle;
    float		sin_angle;
	float		dist;
	float		height;
	int			start_y;
	int			end_y;
	int			u;

	ray.x = x_pos;
	ray.y = y_pos;
	cos_angle = cos(angle);
	sin_angle = -sin(angle);
	while (!touch(ray.x, ray.y, data->map->grid))
	{
		ray.y += sin_angle;
		ray.x += cos_angle;
	}
	dist = fixed_dist(data, x_pos, y_pos, ray);//issue here where sometimes we get a distance bigger than win height
	if (dist == 0)//temp fix as well
		height = WIN_HEIGHT;
	else
		height = (SQUARE_HEIGHT / dist) * (WIN_WIDTH / 2);
	if (height > WIN_HEIGHT)//temporary fix
		height = WIN_HEIGHT;
	start_y = (WIN_HEIGHT - height) / 2;
	end_y = start_y + height;
	u = start_y;
	while (u >= 0)//might need ot check for u = 0;
	{
		u--;
		put_pixel (data, i, u, get_hexa(data->map->elements->c_color));
	}
	while (start_y < end_y)
	{
		put_pixel(data, i, start_y, BLUE);
		start_y++;
	}
	u = end_y; //might need to check for u = WIN_HEIGHT
	while (u <= WIN_HEIGHT)
	{
		put_pixel(data, i, u, get_hexa(data->map->elements->f_color));
		u++;
	}
}

void	draw_pov(t_data *data)
{
	float	start;
	float	fov_slice;
	int		i;

	fov_slice = torad(60) / WIN_WIDTH;
	start = data->player->angle + torad(60) / 2;
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_wall_line(data, data->player->pos.x, data->player->pos.y, start, i);
		start -= fov_slice;
		i++;
	}
}

void cone_of_view(t_data *data)
{
	float	start;
	float	fraction;
	int		i;

	fraction = M_PI / 3 / WIN_WIDTH;
	start = data->player->angle - (M_PI / 3) / 2;
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

void	init_world(t_data *data)
{
	data->player->pos.x *= SQUARE_WIDTH;
	data->player->pos.y *= SQUARE_HEIGHT;
	data->mlx.mlx_img.pixel_arr = mlx_get_data_addr(data->mlx.mlx_img.img, &data->mlx.mlx_img.bpp
		, &data->mlx.mlx_img.line, &data->mlx.mlx_img.endian);
}

