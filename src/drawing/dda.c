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

// float	get_distance_dda(char **grid, t_coords *ray, const float cos_angle, const float sin_angle, t_data *data, float angle)
// {
// 	/*this is to set dda*/
// 	float	orig_x;  // Convert to grid coordinates
// 	float	orig_y;  // Convert to grid coordinates
// 	int		map_x;
// 	int		map_y;
// 	float	delta_dist_x;
// 	float	delta_dist_y;

// /*set this for dda*/
// 	int 	step_x;
// 	int		step_y;
// 	float	side_dist_x;
// 	float	side_dist_y;

// 	orig_x = ray->x / SQUARE;  // Convert to grid coordinates
// 	orig_y = ray->y / SQUARE;  // Convert to grid coordinates

// 	/*player pos for the grid*/
// 	map_x = (int)(ray->x / SQUARE);
// 	map_y = (int)(ray->y / SQUARE);

// 	delta_dist_x = fabs(1.0f / cos_angle);
// 	delta_dist_y = fabs(1.0f / sin_angle);

// /************SET DDA***************** */
// 	/*direction and step for the grid. if we go up, y-1, right x+1 and so on || also gives the delta distance for x and y*/
// 	if (cos_angle < 0)
// 	{
// 		step_x = -1;
// 		side_dist_x = (orig_x - map_x) * delta_dist_x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_dist_x = ((map_x + 1.0f) - orig_x) * delta_dist_x;
// 	}
// 	if (sin_angle < 0)
// 	{
// 		step_y = -1;
// 		side_dist_y = (orig_y - map_y) * delta_dist_y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_dist_y = ((map_y + 1.0f) - orig_y) * delta_dist_y;
// 	}


// /***************PERFORM DDA***************** */
// 	/*we chose the shortest distance, meaning the closest intersection*/
// 	int hit = 0;
// 	//int side = 0;  0 for vertical, 1 for horizontal
// 	/*while we haven't hit a wall*/
// 	/*we use the side distance to determine which side we hit first*/
// 	/*if we hit a wall, we set hit to 1*/
// 	/*we also update the ray coordinates for texture mapping if needed*/
// 	/*we also update the map_x and map_y for the grid*/
// 	while (!hit)//?
// 	{
// 		if (side_dist_x < side_dist_y)
// 		{
// 			side_dist_x += delta_dist_x;
// 			map_x += step_x;
// 			data->map->elements->textures->side = 0; // vertical hit
// 		}
// 		else
// 		{
// 			side_dist_y += delta_dist_y;
// 			map_y += step_y;
// 			data->map->elements->textures->side = 1; // horizontal hit
// 		}
// 		if (grid[map_y][map_x] == '1')
// 			hit = 1;
// 	}

// /****************************GET DISTANCE FROM  ***************************/
// 	float dist;
// 	float hit_y;
// 	float hit_x;
// 	float hit_;
// 	if (data->map->elements->textures->side == 0)
// 	{
// 		hit_y = orig_y + ((map_x - orig_x + (1 - step_x) / 2) / cos_angle) * sin_angle;
// 		hit_ = hit_y - floor(hit_y);
// 		dist = (map_x - orig_x + (1 - step_x) / 2) / cos_angle;
// 	}
// 	else
// 	{
// 		hit_x = orig_x + ((map_y - orig_y + (1 - step_y) / 2) / sin_angle) * cos_angle;
// 		hit_ = hit_x - floor(hit_x);
// 		dist = (map_y - orig_y + (1 - step_y) / 2) / sin_angle;
// 	}
// 	data->map->elements->textures->wall_hit = hit_;

// 	// Fish-eye correction: use relative angle
// 	dist = dist * cos(angle - data->player->angle) * SQUARE;
// 	return (dist);
// }
