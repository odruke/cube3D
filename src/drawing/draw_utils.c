/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 09:38:08 by tienshi           #+#    #+#             */
/*   Updated: 2025/07/19 10:14:52 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pos;
    if(x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
        return;
    pos = data->mlx.mlx_img.pixel_arr + y * data->mlx.mlx_img.line
		+ x * (data->mlx.mlx_img.bpp / 8);
    *(int *)pos = color;
}

void	clear_display(t_data *data)
{
	int	i;
	int	u;

	u = 0;
	while (u < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			put_pixel(data, i, u, BLACK);
			i++;
		}
		u++;
	}
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	u;

	u = y;
	while (u - y <= SQUARE_HEIGHT)
	{
		i = x;
		if ((u - y) % SQUARE_HEIGHT == 0)
		{
			while (i - x <= SQUARE_WIDTH)
			{
				put_pixel(data, i, u, color);
				i++;
			}
		}
		else
		{
			while (i - x <= SQUARE_WIDTH)
			{
				if (i - x == 0 || i - x == SQUARE_WIDTH)
					put_pixel(data, i, u, color);
				i++;
			}
		}
		u++;
	}
}

bool	touch(float x, float y, char **grid)
{
	int	ymap;
	int	xmap;

	ymap = y / SQUARE_HEIGHT;
	xmap = x / SQUARE_WIDTH;
	if (grid[ymap][xmap] == '1')
		return (true);
	return (false);
}
