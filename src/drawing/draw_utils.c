/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:29:59 by tienshi           #+#    #+#             */
/*   Updated: 2025/07/31 01:32:03 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx_img *img, int x, int y, int color)
{
	char	*pos;

	if (x >= img->img_w || y >= img->img_h || x < 0 || y < 0)
		return ;
	pos = img->pixel_arr + y * img->line + x * (img->bpp / 8);
	*(int *)pos = color;
}

void	fill_display(t_mlx_img *img, int width, int height)
{
	int	i;
	int	u;

	u = 0;
	while (u < height)
	{
		i = 0;
		while (i < width)
		{
			put_pixel(img, i, u, BLACK);
			i++;
		}
		u++;
	}
}

void	draw_full_square(t_mlx_img *img, int x, int y, int size)
{
	int	i;
	int	u;

	u = y;
	while (u - y <= size)
	{
		i = x;
		while (i - x < size)
		{
			put_pixel(img, i, u, RED);
			i++;
		}
		u++;
	}
}

void	draw_square(t_mlx_img *img, int x, int y, int size)
{
	int	i;
	int	u;

	u = y - 1;
	while (++u - y <= size)
	{
		i = x;
		if ((u - y) % size == 0)
		{
			while (i - x <= size)
			{
				put_pixel(img, i, u, GREEN);
				i++;
			}
		}
		else
		{
			while (i - x <= size)
			{
				if (i - x == 0 || i - x == size)
					put_pixel(img, i, u, GREEN);
				i++;
			}
		}
	}
}

int	get_hexa(t_color *color)
{
	return ((color->r << 16) | (color->g << 8) | color->b);
}
