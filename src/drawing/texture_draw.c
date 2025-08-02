/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:49:52 by tienshi           #+#    #+#             */
/*   Updated: 2025/07/31 22:32:40 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_mlx_img	*get_face(t_texture *textures, float angle, int side)//import new version from original file
{
	while (angle < 0)
		angle += TWO_PI;
	while (angle >= TWO_PI)
		angle -= TWO_PI;
	if (side)
	{
		if ((angle <= TWO_PI && angle > THREE_HALF_PI)
			|| (angle <= THREE_HALF_PI && angle > M_PI))
			return (textures->n_wall);
		if ((angle <= M_PI && angle > HALF_PI)
			|| (angle <= HALF_PI && angle >= 0))
			return (textures->s_wall);
	}
	else
	{
		if ((angle <= M_PI && angle > HALF_PI)
			|| (angle <= THREE_HALF_PI && angle > M_PI))
			return (textures->e_wall);
		else if ((angle <= HALF_PI && angle >= 0)
			|| (angle <= TWO_PI && angle > THREE_HALF_PI))
			return (textures->w_wall);
	}
	return (NULL);
}

int	set_pixel_texture(t_texture *textures, float height, int y, float angle)//erase this from original file
{
	t_mlx_img	*face;
	char			*pos;
	int				tex_x;
	int				tex_y;
	int				wall_start;

	face = get_face(textures, angle, textures->side);
	if (!face)
		error_handle(ERR_UNKNOWN, "Couldn't get face", __FILE__, __LINE__);
	wall_start = (WIN_HEIGHT - height) / 2;
	tex_x = (int)(textures->wall_hit * face->img_w);
	if (tex_x >= face->img_w)
		tex_x = face->img_w - 1;
	if (face == textures->n_wall || face == textures->e_wall)
		tex_x = face->img_w - 1 - tex_x;
	tex_y = (y - wall_start) * face->img_h / height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= face->img_h)
		tex_y = face->img_h - 1;
	pos = face->pixel_arr + tex_y * face->line + tex_x * (face->bpp / 8);
	return (*(int *)pos);
}
