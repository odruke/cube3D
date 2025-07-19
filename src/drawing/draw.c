/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/19 10:31:43 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_data *data, int x, int y, int color)
{
	int	i;
	int	u;

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

void	generate_world(t_data *data)
{
	data->mlx.mlx_img.pixel_arr = mlx_get_data_addr(data->mlx.mlx_img.img, &data->mlx.mlx_img.bpp
		, &data->mlx.mlx_img.line, &data->mlx.mlx_img.endian);
	clear_display(data);
	draw_map(data);
	draw_player(data, data->player->pos.x * SQUARE_WIDTH
		, data->player->pos.y * SQUARE_HEIGHT, 0xFFFF00);
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
}
