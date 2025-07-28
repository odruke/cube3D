/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/28 16:50:18 by stripet          ###   ########.fr       */
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
				draw_square(data->mlx.mlx_img, i * SQUARE, u * SQUARE, SQUARE, WHITE);
			i++;
		}
		u++;
	}
}

void	draw_ray(t_mlx_img img, float x_pos, float y_pos, float angle)// change to t_img
{
	t_data	*data;
	float	ray_y;
	float	ray_x;
	float	cos_angle;
    float	sin_angle;

	data = recover_data_address(NULL);
	ray_y = y_pos;
	ray_x = x_pos;
	cos_angle = cos(angle);
	sin_angle = -sin(angle);
	while (!touch(ray_x, ray_y, data->map->grid))
	{
		put_pixel(img, ray_x, ray_y, GREEN);
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
		height = (SQUARE / dist) * (WIN_WIDTH / 2);
	if (height > WIN_HEIGHT)//temporary fix
		height = WIN_HEIGHT;
	start_y = (WIN_HEIGHT - height) / 2;
	end_y = start_y + height;
	u = start_y;
	while (u >= 0)//might need ot check for u = 0;
	{
		u--;
		put_pixel(data->mlx.mlx_img, i, u, get_hexa(data->map->elements->c_color));
	}
	while (start_y < end_y)
	{
		put_pixel(data->mlx.mlx_img, i, start_y, BLUE);
		start_y++;
	}
	u = end_y; //might need to check for u = WIN_HEIGHT
	while (u <= WIN_HEIGHT)
	{
		put_pixel(data->mlx.mlx_img, i, u, get_hexa(data->map->elements->f_color));
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
	int	i;

	fraction = torad(60) / WIN_WIDTH;
	start = data->player->angle - torad(60) / 2;
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_ray(data->mlx.mlx_img, data->player->pos.x, data->player->pos.y, start);
		start += fraction;
		i++;
	}
}

// void	draw_mini_map(t_data *data, float x, float y)
// {
// 	t_coords	p_coord;
// 	t_coords

// 	p_coord.x = data->player->pos.x / SQUARE_WIDTH;
// 	p_coord.y = data->player->pos.y / SQUARE_HEIGHT;

// }
void	draw_mini_map(t_data *data, float x, float y)
{
	t_coords	p_coord;
	t_coords	start_p;

	fill_display(data->mini_map->img, BLACK);
	p_coord.x = data->player->pos.x / SQUARE;
	p_coord.y = data->player->pos.y / SQUARE;
	//find player position in x y mode
	start_p.x = p_coord.x - data->mini_map->FOV / 2;//idk how it works for uneven numbers
	start_p.y = p_coord.y - data->mini_map->FOV / 2;//same here
	//find how far we should draw based on FOV
	while (start_p.x < data->mini_map->width && start_p.y < data->mini_map->height)
	{
		draw_square(data->mini_map->img, start_p.x, start_p.y, data->mini_map->width / data->mini_map->FOV, RED);
		start_p.x += data->mini_map->width / data->mini_map->FOV;
		start_p.y += data->mini_map->height / data->mini_map->FOV;
	}
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mini_map->img.img, x, y);
}

int	loop_hook(t_data *data)
{
	player_movement(data);
	if (DEBUG)
	{
		fill_display(data->mlx.mlx_img, BLACK);
		draw_map(data);
		draw_square(data->mlx.mlx_img, data->player->pos.x, data->player->pos.y, 5, YELLOW);
		cone_of_view(data);
	}
	else
		draw_pov(data);
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
	// draw_mini_map(data, data->mlx.w - data->mini_map->width, 0);
	return (0);
}

void	init_world(t_data *data)
{
	data->player->pos.x *= SQUARE;
	data->player->pos.y *= SQUARE;
	data->mlx.mlx_img.pixel_arr = mlx_get_data_addr(data->mlx.mlx_img.img, &data->mlx.mlx_img.bpp
		, &data->mlx.mlx_img.line, &data->mlx.mlx_img.endian);
}

