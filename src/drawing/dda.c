#include "cub3d.h"

// void	set_dda(const float cos_angle, const float sin_angle)
// {

// }

float	get_distance_dda(char **grid, t_coords *ray, const float cos_angle, const float sin_angle, t_data *data, float angle)
{
	/*this is to set dda*/
	float	orig_x;  // Convert to grid coordinates
	float	orig_y;  // Convert to grid coordinates
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;

/*set this for dda*/
	int 	step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;

	orig_x = ray->x / SQUARE;  // Convert to grid coordinates
	orig_y = ray->y / SQUARE;  // Convert to grid coordinates

	/*player pos for the grid*/
	map_x = (int)(ray->x / SQUARE);
	map_y = (int)(ray->y / SQUARE);

	delta_dist_x = fabs(1.0f / cos_angle);
	delta_dist_y = fabs(1.0f / sin_angle);


	/*direction and step for the grid. if we go up, y-1, right x+1 and so on || also gives the delta distance for x and y*/
	if (cos_angle < 0)
	{
		step_x = -1;
		side_dist_x = (orig_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1.0f) - orig_x) * delta_dist_x;
	}
	if (sin_angle < 0)
	{
		step_y = -1;
		side_dist_y = (orig_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((map_y + 1.0f) - orig_y) * delta_dist_y;
	}

	/*we chose the shortest distance, meaning the closest intersection*/
	int hit = 0;
	//int side = 0;  0 for vertical, 1 for horizontal
	/*while we haven't hit a wall*/
	/*we use the side distance to determine which side we hit first*/
	/*if we hit a wall, we set hit to 1*/
	/*we also update the ray coordinates for texture mapping if needed*/
	/*we also update the map_x and map_y for the grid*/
	while (!hit)//?
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			data->map->elements->textures->side = 0; // vertical hit
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			data->map->elements->textures->side = 1; // horizontal hit
		}
		if (grid[map_y][map_x] == '1')
			hit = 1;
	}
	float dist;
	if (data->map->elements->textures->side == 0)
	{
		float hit_y = orig_y + ((map_x - orig_x + (1 - step_x) / 2) / cos_angle) * sin_angle;
		data->map->elements->textures->wall_hit = hit_y - floor(hit_y);
		dist = (map_x - orig_x + (1 - step_x) / 2) / cos_angle;
	}
	else
	{
		float hit_x = orig_x + ((map_y - orig_y + (1 - step_y) / 2) / sin_angle) * cos_angle;
		data->map->elements->textures->wall_hit = hit_x - floor(hit_x);
		dist = (map_y - orig_y + (1 - step_y) / 2) / sin_angle;
	}
	// Fish-eye correction: use relative angle
	dist = dist * cos(angle - data->player->angle) * SQUARE;
	return (dist);
}
