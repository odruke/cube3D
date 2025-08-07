/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:34:15 by odruke-s          #+#    #+#             */
/*   Updated: 2025/08/08 00:34:21 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(t_dda *dda, float angle)
{
	dda->step_x = 0;
	dda->step_y = 0;
	dda->side_dist_x = 0;
	dda->side_dist_y = 0;
	dda->cos_angle = cos(angle);
	dda->sin_angle = -sin(angle);
	dda->delta_dist_x = fabs(1.0f / dda->cos_angle);
	dda->delta_dist_y = fabs(1.0f / dda->sin_angle);
}

void	set_dda(t_dda *dda, t_coords *ray)
{
	if (dda->cos_angle < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = ((ray->x / SQUARE)
				- (int)(ray->x / SQUARE)) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (((int)(ray->x / SQUARE) + 1.0f)
				- (ray->x / SQUARE)) * dda->delta_dist_x;
	}
	if (dda->sin_angle < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = ((ray->y / SQUARE)
				- (int)(ray->y / SQUARE)) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (((int)(ray->y / SQUARE) + 1.0f)
				- (ray->y / SQUARE)) * dda->delta_dist_y;
	}
}

static void	perform_dda(t_data *data, t_dda *dda, t_coords *ray)
{
	int	hit;

	dda->map_x = (int)(ray->x / SQUARE);
	dda->map_y = (int)(ray->y / SQUARE);
	hit = 0;
	while (!hit)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			data->map->elements->textures->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			data->map->elements->textures->side = 1;
		}
		if (data->map->grid[dda->map_y][dda->map_x] == '1')
			hit = 1;
	}
}

float	set_distance(t_data *data, t_dda *dda, t_coords *ray, float angle)
{
	float	dist;
	float	hit_y;
	float	hit_x;
	float	hit;

	if (data->map->elements->textures->side == 0)
	{
		hit_y = (ray->y / SQUARE) + ((dda->map_x - (ray->x / SQUARE)
					+ (1 - dda->step_x) / 2) / dda->cos_angle) * dda->sin_angle;
		hit = hit_y - floor(hit_y);
		dist = (dda->map_x - (ray->x / SQUARE)
				+ (1 - dda->step_x) / 2) / dda->cos_angle;
	}
	else
	{
		hit_x = (ray->x / SQUARE) + ((dda->map_y - (ray->y / SQUARE)
					+ (1 - dda->step_y) / 2) / dda->sin_angle) * dda->cos_angle;
		hit = hit_x - floor(hit_x);
		dist = (dda->map_y - (ray->y / SQUARE)
				+ (1 - dda->step_y) / 2) / dda->sin_angle;
	}
	data->map->elements->textures->wall_hit = hit;
	dist = dist * cos(angle - data->player->angle) * SQUARE;
	return (dist);
}

float	get_distance(t_data *data, t_coords *ray, float angle)
{
	init_dda(data->dda, angle);
	set_dda(data->dda, ray);
	perform_dda(data, data->dda, ray);
	return (set_distance(data, data->dda, ray, angle));
}
