/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/31 22:24:00 by tienshi          ###   ########.fr       */
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

double	get_distance_dda(char **grid, t_coords *ray, const double cos_angle, const double sin_angle, t_data *data, double angle)
{
	/*store original ray position*/
	double orig_x = ray->x / SQUARE;  // Convert to grid coordinates
	double orig_y = ray->y / SQUARE;  // Convert to grid coordinates

	/*player pos for the grid*/
	int map_x = (int)(ray->x / SQUARE);
	int map_y = (int)(ray->y / SQUARE);

	/*direction of the vector*/
	// float ray_dir_x = cos_angle;
	// float ray_dir_y = sin_angle;


	double delta_dist_x = fabs(1.0f / cos_angle);
	double delta_dist_y = fabs(1.0f / sin_angle);

	int step_x, step_y;
	double side_dist_x, side_dist_y;

	/*direction and step for the grid. if we go up, y-1, right x+1 and so on || also gives the delta distance for x and y*/
	if (cos_angle < 0)
	{
		step_x = -1;
		side_dist_x = (orig_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1.0f) - orig_x) * delta_dist_x;
	}
	if (sin_angle < 0)
	{
		step_y = -1;
		side_dist_y = (orig_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((map_y + 1.0f) - orig_y) * delta_dist_y;
	}

	/*we chose the shortest distance, meaning the closest intersection*/
	bool 	hit = false;
	//int side = 0;  0 for vertical, 1 for horizontal
	/*while we haven't hit a wall*/
	/*we use the side distance to determine which side we hit first*/
	/*if we hit a wall, we set hit to 1*/
	/*we also update the ray coordinates for texture mapping if needed*/
	/*we also update the map_x and map_y for the grid*/
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			data->map->elements->textures->side = 0; // vertical hit
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			data->map->elements->textures->side = 1; // horizontal hit
		}
		if (grid[map_y][map_x] == '1')
			hit = true;
	}
	double dist;
	if (data->map->elements->textures->side == 1)
	{
		float hit_x = orig_x + ((map_y - orig_y + (1 - step_y) / 2) / sin_angle) * cos_angle;
		data->map->elements->textures->wall_hit = hit_x - floor(hit_x);
		dist = (map_y - orig_y + (1 - step_y) / 2) / sin_angle;
	}
	else
	{
		float hit_y = orig_y + ((map_x - orig_x + (1 - step_x) / 2) / cos_angle) * sin_angle;
		data->map->elements->textures->wall_hit = hit_y - floor(hit_y);
		dist = (map_x - orig_x + (1 - step_x) / 2) / cos_angle;
	}
	// Fish-eye correction: use relative angle
	dist = dist * cos(angle - data->player->angle) * SQUARE;
	return (dist);
}

void	draw_wall_line(t_data *data, double x_pos, double y_pos, double angle, int i)
{
	t_coords	ray;
	double		cos_angle;
    double		sin_angle;
	double		dist;
	double		height;
	int			start_y;
	int			end_y;
	int			u;
	int			pixel;

	ray.x = x_pos;
	ray.y = y_pos;
	cos_angle = cos(angle);
	sin_angle = -sin(angle);
	dist = get_distance_dda(data->map->grid, &ray, cos_angle, sin_angle, data, angle);
	if (dist == 0)//temp fix as well
		height = WIN_HEIGHT;
	else
		height = (SQUARE / dist) * (WIN_WIDTH / 2);
	// if (height > WIN_HEIGHT)//temporary fix //this causes stretching when close
	// 	height = WIN_HEIGHT;
	start_y = (WIN_HEIGHT - height) / 2;
	end_y = start_y + height;
	// u = start_y;
	u = 0;
	while (u <= start_y)//might need ot check for u = 0;
	{
		u++;
		put_pixel(data->mlx->mlx_img, i, u, get_hexa(data->map->elements->c_color));
	}
	while (start_y < end_y)
	{
		pixel = set_pixel_texture(data->map->elements->textures, height, start_y, angle);
		put_pixel(data->mlx->mlx_img, i, start_y, pixel);
		start_y++;
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
	draw_mini_map(data, data->mlx->mlx_img->img_w -\
data->mini_map->size, 0);
	return (0);
}
