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

void	draw_ceiling(t_data *data, int i, int start_y)
{
	int		u;
	t_color	*ceiling_color;

	ceiling_color = data->map->elements->c_color;
	u = 0;
	while (u <= start_y)
	{
		u++;
		put_pixel(data->mlx->mlx_img, i, u, get_hexa(ceiling_color));
	}
}

void	draw_floor(t_data *data, int i, int end_y)
{
	t_color	*floor_color;

	floor_color = data->map->elements->f_color;
	while (end_y <= WIN_HEIGHT)
	{
		put_pixel(data->mlx->mlx_img, i, end_y, get_hexa(floor_color));
		end_y++;
	}
}

void	draw_wall_line(t_data *data, t_coords pos, float angle, int i)
{
	float		dist;
	float		height;
	int			start_y;
	int			end_y;
	int			pixel;

	dist = get_distance(data, &(t_coords){pos.y, pos.x}, angle);
	height = (SQUARE / dist) * (WIN_WIDTH / 2);
	start_y = (WIN_HEIGHT - height) / 2;
	end_y = start_y + height;
	if (start_y < 0)
		start_y = 0;
	if (end_y > WIN_HEIGHT)
		end_y = WIN_HEIGHT;
	draw_ceiling(data, i, start_y);
	while (start_y < end_y)
	{
		pixel = set_pixel_texture(data->map->elements->textures,
				height, start_y, angle);
		put_pixel(data->mlx->mlx_img, i, start_y, pixel);
		start_y++;
	}
	draw_floor(data, i, end_y);
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
		draw_wall_line(data, data->player->pos, start, i);
		start -= fov_slice;
		i++;
	}
}

int	loop_hook(t_data *data)
{
	static bool	started;

	if (!started)
	{
		printf("\033[1;32m✅ Game loop starded \033[0m\n");
		started = true;
	}
	player_movement(data);
	if (DEBUG == 2)
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
