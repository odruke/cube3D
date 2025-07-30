/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 09:38:08 by tienshi           #+#    #+#             */
/*   Updated: 2025/07/29 16:20:57 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture_img	*get_face(t_texture *textures, float angle, int side)//angle gets to be negative needs to reset
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < M_PI && angle > (M_PI / 2) && side)//face south
		return (textures->s_Wall);
	else if (angle < M_PI && angle > (M_PI / 2) && !side)//face east
		return (textures->e_Wall);
	else if (angle < (M_PI / 2) && angle > 0 && side)//face south
		return (textures->s_Wall);
	else if (angle < (M_PI / 2) && angle > 0 && !side)//face west
		return (textures->w_Wall);
	else if (angle < (M_PI * 2) && angle > ((3 * M_PI) / 2) && side)//face north
		return (textures->n_Wall);
	else if (angle < (M_PI * 2) && angle > ((3 * M_PI) / 2) && !side)//face west
		return (textures->w_Wall);
	else if (angle < ((3 * M_PI) / 2) && angle > M_PI && side)//face north
		return (textures->n_Wall);
	else if (angle < ((3 * M_PI) / 2) && angle > M_PI && !side)//face east
		return (textures->e_Wall);
	return (NULL);
}

int		set_pixel_texture(t_texture *textures, float height, int y, float dist, float angle, int side)
{
	t_texture_img	*face;
	char			*pos;
	int				tex_x, tex_y;
	int				wall_height;
	int				wall_start;

	(void)x;
	face = get_face(textures, angle, side);
	if (!face)
		error_handle(ERR_UNKNOWN, "Couldn't get face", __FILE__, __LINE__);
	wall_start = (WIN_HEIGHT - wall_height) / 2;

	tex_x = (int)(textures->wall_hit * face->img_w);
	if (tex_x >= face->img_w)
		tex_x = face->img_w - 1;
	/*this reverses N and E textures, otherwise will be draw sideways*/
	if (face == textures->n_Wall || face == textures->e_Wall)
		tex_x = face->img_w - 1 - tex_x;

	// Texture Y coordinate based on wall position
	tex_y = (y - wall_start) * face->img_h / wall_height;

	// Bounds checking
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= face->img_h)
		tex_y = face->img_h - 1;
	pos = face->pixel_arr + tex_y * face->line + tex_x * (face->bpp / 8);
	return (*(int *)pos);
}

void	put_pixel(t_mlx_img *img, int x, int y, int color)
{
	char	*pos;

	if (x >= img->img_w || y >= img->img_h || x < 0 || y < 0)
		return ;
	pos = img->pixel_arr + y * img->line + x * (img->bpp / 8);
	*(int *)pos = color;
}

void	fill_display(t_mlx_img *img, int width, int height, int color)
{
	int	i;
	int	u;

	u = 0;
	while (u < height)
	{
		i = 0;
		while (i < width)
		{
			put_pixel(img, i, u, color);
			i++;
		}
		u++;
	}
}

void	draw_full_square(t_mlx_img *img, int x, int y, int size, int color)
{
	int	i;
	int	u;

	u = y;
	while (u - y <= size)
	{
		i = x;
		while (i - x < size)
		{
			put_pixel(img, i, u, color);
			i++;
		}
		u++;
	}
}

void	draw_square(t_mlx_img *img, int x, int y, int size, int color)
{
	int	i;
	int	u;

	u = y;
	while (u - y <= size)
	{
		i = x;
		if ((u - y) % size == 0)
		{
			while (i - x <= size)
			{
				put_pixel(img, i, u, color);
				i++;
			}
		}
		else
		{
			while (i - x <= size)
			{
				if (i - x == 0 || i - x == size)
					put_pixel(img, i, u, color);
				i++;
			}
		}
		u++;
	}
}

int	get_hexa(t_color *color)
{
	return ((color->r << 16) | (color->g << 8) | color->b);
}

bool	touch(float x, float y, char **grid, int square)
{
	int	ymap;
	int	xmap;

	ymap = y / square;
	xmap = x / square;
	if (grid[ymap][xmap] == '1')
		return (true);
	return (false);
}
