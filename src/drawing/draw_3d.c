/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/08/01 09:07:27 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_map(t_data *data)
// {
// 	int	i;
// 	int	u;

// 	u = 0;
// 	while (u < data->map->height)
// 	{
// 		i = 0;
// 		while (i < data->map->width && data->map->grid[u][i])
// 		{
// 			if ((data->map->grid)[u][i] == '1')
// 				draw_square(data->mlx->mlx_img,
// 					i * SQUARE, u * SQUARE, SQUARE, WHITE);
// 			i++;
// 		}
// 		u++;
// 	}
// }

// void	draw_ray(t_mlx_img *img, double x_pos, double y_pos, double angle, int square)
// {
// 	t_data	*data;
// 	double	ray_y;
// 	double	ray_x;
// 	double	cos_angle;
//     double	sin_angle;

// 	data = recover_data_address(NULL);
// 	ray_y = y_pos;
// 	ray_x = x_pos;
// 	cos_angle = cos(angle);
// 	sin_angle = -sin(angle);
// 	while (!touch(ray_x, ray_y, data->map->grid, square))
// 	{
// 		put_pixel(img, ray_x - (data->player->pos.x / square),
// 			ray_y - (data->player->pos.y / square), GREEN);
// 		ray_y += sin_angle;
// 		ray_x += cos_angle;
// 	}
// }

// void cone_of_view(t_data *data)
// {
// 	double	start;
// 	double	fraction;
// 	int	i;

// 	fraction = torad(60) / WIN_WIDTH;
// 	start = data->player->angle - torad(60) / 2;
// 	i = 0;
// 	while (i < WIN_WIDTH)
// 	{
// 		draw_ray(data->mlx->mlx_img, data->player->pos.x, data->player->pos.y, start, SQUARE);
// 		start += fraction;
// 		i++;
// 	}
// }


void	draw_wall_line(t_data *data, float x_pos, float y_pos, float angle, int i)
{
	float		dist;
	float		height;
	int			start_y;
	int			end_y;
	int			u;
	int			pixel;
	int			wall_start;
	int			wall_end;

	dist = get_distance(data, &(t_coords){y_pos, x_pos}, angle);
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
	while (u <= start_y)
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
	u = end_y;
	while (u <= WIN_HEIGHT)
	{
		put_pixel(data->mlx->mlx_img, i, u, get_hexa(data->map->elements->f_color));
		u++;
	}
}

void	draw_pov(t_data *data)
{
	double	start;
	double	fov_slice;
	int		i;

	fov_slice = torad(60) / WIN_WIDTH;
	start = data->player->angle + torad(60) / 2;
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_wall_line(data, data->player->pos.x,
			data->player->pos.y, start, i);
		start -= fov_slice;
		i++;
	}
}

int	loop_hook(t_data *data)
{
	player_movement(data);
	if (DEBUG)
	{
		fill_display(data->mlx->mlx_img, data->mlx->mlx_img->img_w,
			data->mlx->mlx_img->img_h);
		// draw_map(data);
		// draw_square(data->mlx->mlx_img, data->player->pos.x,
		// 	data->player->pos.y, 5);
		// cone_of_view(data);
	}
	else
		draw_pov(data);
	mlx_put_image_to_window(data->mlx->mlx_tunnel,
		data->mlx->window, data->mlx->mlx_img->img, 0, 0);
	draw_mini_map(data, data->mlx->mlx_img->img_w - \
data->mini_map->img.img_w, 0);
	return (0);
}
