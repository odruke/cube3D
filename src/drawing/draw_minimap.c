/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:07:11 by tienshi           #+#    #+#             */
/*   Updated: 2025/07/31 17:32:48 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_walls(t_data *data, t_coords *start_p)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (u < data->mini_map->fov)
	{
		while (i < data->mini_map->fov)
		{
			if (((start_p->x + i < data->map->width
						&& start_p->y + u < data->map->height)
					&& (start_p->x + i >= 0 && start_p->y + u >= 0))
				&& (data->map->grid[(int)start_p->y + u]\
[(int)start_p->x + i] == '1'))
			{
				draw_full_square(&data->mini_map->img, i
					* (data->mini_map->img.img_w / data->mini_map->fov),
					u * (data->mini_map->img.img_h / data->mini_map->fov),
					data->mini_map->img.img_w / data->mini_map->fov);
			}
			i++;
		}
		i = 0;
		u++;
	}
}

void	draw_mini_map(t_data *data, double x, double y)
{
	t_coords	p_coord;
	t_coords	start_p;

	fill_display(&data->mini_map->img,
		data->mini_map->img.img_w, data->mini_map->img.img_h);
	p_coord.x = roundf(data->player->pos.x / SQUARE);
	p_coord.y = roundf(data->player->pos.y / SQUARE);
	start_p.x = p_coord.x - data->mini_map->fov / 2;
	start_p.y = p_coord.y - data->mini_map->fov / 2;
	draw_walls(data, &start_p);
	draw_square(&data->mini_map->img, (data->mini_map->img.img_w / 2) - 2
		, (data->mini_map->img.img_h / 2) - 2, 2);
	mlx_put_image_to_window(data->mlx->mlx_tunnel, data->mlx->window,
		data->mini_map->img.img, x, y);
}
