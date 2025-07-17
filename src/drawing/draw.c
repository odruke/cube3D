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

void	drawbox(t_data *data, int y, int x, unsigned int color, int tile)
{
	char	*pos;
	int 	i;
	int		j;
	int		xsave;

	xsave = x;
	i = -1;
	while (++i < tile && y < WIN_HEIGHT)
	{
		x = xsave;
		j = -1;
		while (++j < tile && x < WIN_WIDTH)
		{
			pos = data->mlx.mlx_img.pixel_arr + y * data->mlx.mlx_img.line
				+ x * (data->mlx.mlx_img.bpp / 8);
			*(int *)pos = color;
			x++;
		}
		y++;
	}

}

void	imaplayer(t_data *data)
{

	int		tile;

	tile = 5;

	drawbox(data, data->player->pos.y * 32, data->player->pos.x * 32, RED, tile);
}

void	drawmap(t_data *data)
{
	int		y;
	int		x;
	int		ygrid;
	int		xgrid;
	int		tile;

	tile = 32;
	y = 0;
	ygrid = 0;
	data->mlx.mlx_img.pixel_arr = mlx_get_data_addr(data->mlx.mlx_img.img, &data->mlx.mlx_img.bpp,
		&data->mlx.mlx_img.line, &data->mlx.mlx_img.endian);
	if (!data->mlx.mlx_img.pixel_arr)
		error_handle(ERR_MLX, "get_data_addr failed", __FILE__, __LINE__);
	while (y < WIN_HEIGHT && ygrid < data->map->height)
	{
		x = 0;
		xgrid = 0;
		while (data->map->grid[ygrid][xgrid] &&( x < WIN_WIDTH && ygrid < data->map->width))
		{
			if (data->map->grid[ygrid][xgrid] == '1')
				drawbox(data, y, x, WHITE, tile);
			else if (data->map->grid[ygrid][xgrid] == '0')
				drawbox(data, y, x, BLACK, tile);
			xgrid++;
			x += tile;
		}
		ygrid++;
		y += tile;
	}
}

void	generate_world(void)
{
	t_data	*data;

	data = recover_data_address(NULL);
	// generate_grid();
	// draw_player();
	drawmap(data);
	imaplayer(data);
	mlx_put_image_to_window(data->mlx.mlx_tunnel, data->mlx.window, data->mlx.mlx_img.img, 0, 0);
}

