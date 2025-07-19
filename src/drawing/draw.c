/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/16 15:54:55 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(void)
{
	t_data	*data;
	int		i;
	int		u;
	char	*pos;

	data = recover_data_address(NULL);
	i = data->mlx.w / 2 - 5;
	u = data->mlx.h / 2 - 5;
	while (u < data->mlx.h / 2 + 5)
	{
		while (i < data->mlx.w / 2 + 5)
		{
			pos = data->mlx.mlx_img.pixel_arr + u * data->mlx.mlx_img.line
				+ i * (data->mlx.mlx_img.bpp / 8);
			*(int *)pos = 0xFF0000;
			i++;
		}
		i = data->mlx.w / 2 - 5;
		u++;
	}
}

void    generate_grid(void)
{
	t_data	*data;
	int		i;
	int		y;
	char	*pos;

	i = 0;
	y = 0;
	data = recover_data_address(NULL);
	data->mlx.mlx_img.pixel_arr = mlx_get_data_addr(data->mlx.mlx_img.img, &data->mlx.mlx_img.bpp,
		&data->mlx.mlx_img.line, &data->mlx.mlx_img.endian);
	if (!data->mlx.mlx_img.pixel_arr)
		error_handle(ERR_MLX, "get_data_addr failed", __FILE__, __LINE__);
	while (y < data->mlx.h)
	{
		if (y % SQUARE_HEIGHT == 0)
		{
			while (i < data->mlx.w)
			{
				pos = data->mlx.mlx_img.pixel_arr + y * data->mlx.mlx_img.line
					+ i * (data->mlx.mlx_img.bpp / 8);
				*(int *)pos = 0xFFFFFF;
				i++;
			}
			i = 0;
		}
		else
		{
			while (i < data->mlx.w)
			{
				if (i % SQUARE_WIDTH == 0)
				{
					pos = data->mlx.mlx_img.pixel_arr + y * data->mlx.mlx_img.line
						+ i * (data->mlx.mlx_img.bpp / 8);
					*(int *)pos = 0xFFFFFF;
				}
				else
				{
					pos = data->mlx.mlx_img.pixel_arr + y * data->mlx.mlx_img.line
						+ i * (data->mlx.mlx_img.bpp / 8);
					*(int *)pos = 0x000000;
				}
				i++;
			}
			i = 0;
		}
		y++;
	}
}

void	generate_world(void)
{
	t_data	*data;

	data = recover_data_address(NULL);
	generate_grid();
	draw_player();
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
}

