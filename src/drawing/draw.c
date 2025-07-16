/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:49:32 by stripet           #+#    #+#             */
/*   Updated: 2025/07/15 11:07:53 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_pos(int	x, int y)
{
	t_data	*data;
	int		i;
	int		u;
	char	*pos;

	i = x - 5;
	u = y - 5;
	data = recover_data_address(NULL);
	while (u < y + 5)
	{
		while (i < x + 5)
		{
			pos = data->mlx.mlx_img.pixel_arr + u * data->mlx.mlx_img.line
				+ i * (data->mlx.mlx_img.bpp / 8);
			*(int *)pos = 0xFF0000;
			i++;
		}
		i = x - 5;
		u++;
	}
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
}

void    draw(void)
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
		if (y % 50 == 0)
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
				if (i % 50 == 0)
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
	draw_player_pos(data->player.x, data->player.y);
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
}
