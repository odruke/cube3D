/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/29 16:25:31 by stripet          ###   ########.fr       */
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
				draw_square(data->mlx->mlx_img, i * SQUARE, u * SQUARE, SQUARE, WHITE);
			i++;
		}
		u++;
	}
}

void	draw_ray(t_mlx_img *img, float x_pos, float y_pos, float angle, int square)
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
	while (!touch(ray_x, ray_y, data->map->grid, square))
	{
		put_pixel(img, ray_x - (data->player->pos.x / square), ray_y - (data->player->pos.y / square), GREEN);
		ray_y += sin_angle;
		ray_x += cos_angle;
	}
}

float	distance(float x, float y)//obsolete??
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_data *data, float x, float y, t_coords p2)//obsolete?
{
	t_coords	delta;
	float		fixed_angl;
	float		ret_val;

	delta.x = p2.x - x;
	delta.y = p2.y - y;
	fixed_angl = (atan2(delta.y, delta.x) - data->player->angle);
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
	int			pixel;
	int			wall_start;
	int			wall_end;

	ray.x = x_pos;
	ray.y = y_pos;
	cos_angle = cos(angle);
	sin_angle = -sin(angle);
	/*dda functions*/
	init_dda_data();
	set_dda();
	perform_dda();
	dist = get_distance_dda(data->map->grid, &ray, cos_angle, sin_angle, data, angle);
	/*dda functions*/
	if (dist == 0)//temp fix as well
		height = WIN_HEIGHT;
	else
		height = (SQUARE / dist) * (WIN_WIDTH / 2);
	// if (height > WIN_HEIGHT)//temporary fix //this causes stretching when close
	// 	height = WIN_HEIGHT;
	start_y = (WIN_HEIGHT - height) / 2;
	end_y = start_y + height;
	if (start_y < 0)
		wall_start = 0;
	else
		wall_start = start_y;

	if (end_y > WIN_HEIGHT)
		wall_end = WIN_HEIGHT;
	else
		wall_end = end_y;

	u = 0;
	while (u <= start_y)//might need ot check for u = 0;
	{
		u++;
		put_pixel(data->mlx->mlx_img, i, u, get_hexa(data->map->elements->c_color));
	}
	while (wall_start < wall_end)
	{
		pixel = set_pixel_texture(data->map->elements->textures, height, wall_start, angle);
		put_pixel(data->mlx->mlx_img, i, wall_start, pixel);
		wall_start++;
	}
	u = end_y; //might need to check for u = WIN_HEIGHT
	while (u <= WIN_HEIGHT)
	{
		put_pixel(data->mlx->mlx_img, i, u, get_hexa(data->map->elements->f_color));
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
		draw_ray(data->mlx->mlx_img, data->player->pos.x, data->player->pos.y, start, SQUARE);
		start += fraction;
		i++;
	}
}

void cone_of_view_mini(t_data *data, float px, float py)
{
	float	start;
	float	fraction;
	int		i;

	fraction = torad(60) / data->mini_map->img.img_w;
	start = data->player->angle - torad(60) / 2;
	i = 0;
	while (i < data->mini_map->img.img_w)
	{
		draw_ray(&data->mini_map->img, px, py, start, data->mini_map->img.img_w / data->mini_map->FOV);
		start += fraction;
		i++;
	}
}

void	draw_mini_map(t_data *data, float x, float y)//N W bug
{
	t_coords	p_coord;
	t_coords	start_p;
	int			i;
	int			u;

	fill_display(&data->mini_map->img, data->mini_map->img.img_w, data->mini_map->img.img_h, BLACK);
	p_coord.x = roundf(data->player->pos.x / SQUARE);//might need changes
	p_coord.y = roundf(data->player->pos.y / SQUARE);
	i = 0;
	u = 0;
	start_p.x = p_coord.x - data->mini_map->FOV / 2;
	start_p.y = p_coord.y - data->mini_map->FOV / 2;
	while (u < data->mini_map->FOV)
	{
		while (i < data->mini_map->FOV)
		{
			if (((start_p.x + i < data->map->width && start_p.y + u < data->map->height)
				&& (start_p.x + i >= 0 && start_p.y + u >= 0))
				&& (data->map->grid[(int)start_p.y + u][(int)start_p.x + i] == '1'))
			{
				draw_full_square(&data->mini_map->img, i * (data->mini_map->img.img_w / data->mini_map->FOV),
					u * (data->mini_map->img.img_h / data->mini_map->FOV),
					data->mini_map->img.img_w / data->mini_map->FOV, RED);
			}
			i++;
		}
		i = 0;
		u++;
	}
	draw_square(&data->mini_map->img, data->mini_map->img.img_w / 2, data->mini_map->img.img_h / 2, 3, GREEN);//might want to draw the player in the middle middle for accuracy purpose
	cone_of_view_mini(data, data->mini_map->img.img_w / 2, data->mini_map->img.img_h / 2);
	mlx_put_image_to_window(data->mlx->mlx_tunnel, data->mlx->window, data->mini_map->img.img, x, y);
}

int	loop_hook(t_data *data)
{
	update_fps(data->fps);//DELETE THIS BEFORE FINISHING THIS PROJECT
	player_movement(data);
	if (DEBUG)
	{
		fill_display(data->mlx->mlx_img, data->mlx->mlx_img->img_w, data->mlx->mlx_img->img_h, BLACK);
		draw_map(data);
		draw_square(data->mlx->mlx_img, data->player->pos.x, data->player->pos.y, 5, YELLOW);
		cone_of_view(data);
	}
	else
		draw_pov(data);
	mlx_put_image_to_window(data->mlx->mlx_tunnel, data->mlx->window, data->mlx->mlx_img->img, 0, 0);
	draw_mini_map(data, data->mlx->mlx_img->img_w - data->mini_map->img.img_w, 0);
	draw_fps(data);//DELETE THIS FILE BEFORE FINISHING THIS PROJECT
	return (0);
}

void	init_world(t_data *data)
{
	data->player->pos.x *= SQUARE;
	data->player->pos.y *= SQUARE;
	data->mlx->mlx_img->pixel_arr = mlx_get_data_addr(data->mlx->mlx_img->img, &data->mlx->mlx_img->bpp
		, &data->mlx->mlx_img->line, &data->mlx->mlx_img->endian);
}

