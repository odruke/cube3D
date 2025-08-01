#include "cub3d.h"

/* ========== DDA-ENHANCED MOVEMENT FUNCTIONS ========== */

/**
 * Check if a point is within valid map bounds and not a wall
 */
bool	dda_point_valid(t_map *map, t_coords point)
{
	int		grid_x;
	int		grid_y;
	char	*valid_pos;
	char	pos;

	grid_x = (int)(point.x / SQUARE);
	grid_y = (int)(point.y / SQUARE);

	if (grid_x < 0 || grid_x >= map->width ||
		grid_y < 0 || grid_y >= map->height)
		return (false);

	valid_pos = "NSWE0";
	pos = map->grid[grid_y][grid_x];
	while (*valid_pos)
	{
		if (*valid_pos == pos)
			return (true);
		valid_pos++;
	}
	return (false);
}

/**
 * DDA tracing with distance limitation for movement validation
 */
// float	perform_dda_with_distance(t_map *map, t_dda *dda, t_coords *ray, float max_distance)
// {
// 	int		hit;
// 	float	traveled_distance;
// 	float	step_distance;

// 	hit = 0;
// 	traveled_distance = 0;
// 	dda->map_x = (int)(ray->x / SQUARE);
// 	dda->map_y = (int)(ray->y / SQUARE);

// 	while (!hit && traveled_distance < max_distance)
// 	{
// 		if (dda->side_dist_x < dda->side_dist_y)
// 		{
// 			step_distance = dda->side_dist_x;
// 			dda->side_dist_x += dda->delta_dist_x;
// 			dda->map_x += dda->step_x;
// 		}
// 		else
// 		{
// 			step_distance = dda->side_dist_y;
// 			dda->side_dist_y += dda->delta_dist_y;
// 			dda->map_y += dda->step_y;
// 		}

// 		traveled_distance += step_distance * SQUARE;

// 		// Check bounds
// 		if (dda->map_x < 0 || dda->map_x >= map->width ||
// 			dda->map_y < 0 || dda->map_y >= map->height)
// 		{
// 			hit = 1;
// 			break;
// 		}

// 		if (map->grid[dda->map_y][dda->map_x] == '1')
// 			hit = 1;
// 	}

// 	return (traveled_distance);
// }

/**
 * Validate movement path using DDA ray tracing
 */
// bool	dda_valid_move(t_map *map, t_coords from, t_coords to)
// {
// 	t_dda		dda;
// 	t_coords	ray;
// 	float		angle;
// 	float		distance;
// 	float		move_distance;
// 	float		dx;
// 	float		dy;

// 	// Calculate movement vector
// 	dx = to.x - from.x;
// 	dy = to.y - from.y;
// 	move_distance = sqrt(dx * dx + dy * dy);

// 	if (move_distance == 0)
// 		return (true);

// 	angle = atan2(dy, dx);
// 	ray.x = from.x;
// 	ray.y = from.y;

// 	// Use DDA to trace the path
// 	init_dda(&dda, angle);
// 	set_dda(&dda, &ray);

// 	// Check if wall is hit before reaching destination
// 	distance = perform_dda_with_distance(map, &dda, &ray, move_distance);

// 	return (distance >= move_distance);
// }

/**
 * Validate movement considering player radius (8-point collision)
 */
bool	validate_move_with_radius(t_data *data, t_coords new_pos)
{
	float		player_radius;
	t_coords	check_points[8];
	int			i;
	float		angle;

	player_radius = SQUARE * 0.15f;  // Reduced from 0.3f to 0.15f (more realistic)

	// Check 8 points around player (circle approximation)
	for (i = 0; i < 8; i++)
	{
		angle = (i * M_PI * 2) / 8.0f;
		check_points[i].x = new_pos.x + cos(angle) * player_radius;
		check_points[i].y = new_pos.y + sin(angle) * player_radius;

		// Use DDA to check each point
		if (!dda_point_valid(data->map, check_points[i]))
			return (false);
	}
	return (true);
}

void	calc_pos(t_move move, t_coords *coords,
	const float *cos_angle, const float *sin_angle)
{
	float	speed;

	speed = get_speed();
	if (move == UP)
	{
		coords->x += *cos_angle * speed;
		coords->y += *sin_angle * speed;
	}
	else if (move == DOWN)
	{
		coords->x -= *cos_angle * speed;
		coords->y -= *sin_angle * speed;
	}
	else if (move == LEFT)
	{
		coords->x += *sin_angle * speed;
		coords->y -= *cos_angle * speed;
	}
	else if (move == RIGHT)
	{
		coords->x -= *sin_angle * speed;
		coords->y += *cos_angle * speed;
	}
}

void	sliding_move(t_data *data, t_coords *original_pos, t_coords *new_pos)
{
	t_coords	x_only;
	t_coords	y_only;

	if (fabs(new_pos->x - original_pos->x) > 0.1f && fabs(new_pos->y - original_pos->y) > 0.1f)
	{
		// Try X-only movement (wall sliding)
		x_only = *original_pos;
		x_only.x = new_pos->x;
		if (validate_move_with_radius(data, x_only))
		{
			data->player->pos = x_only;
			return;
		}

		// Try Y-only movement (wall sliding)
		y_only = *original_pos;
		y_only.y = new_pos->y;
		if (validate_move_with_radius(data, y_only))
		{
			data->player->pos = y_only;
			return;
		}
	}
}

/**
 * Enhanced movement with wall sliding using DDA collision detection
 */
void	enhanced_displace(t_move move, t_data *data,
	const float cos_angle, const float sin_angle)
{
	t_coords	new_pos;
	t_coords	original_pos;
	// t_coords	x_only;
	// t_coords	y_only;


	original_pos = data->player->pos;
	new_pos = original_pos;

	calc_pos(move, &new_pos, &cos_angle, &sin_angle);
	// Try full movement first
	if (validate_move_with_radius(data, new_pos))
	{
		data->player->pos = new_pos;
		return;
	}

	// Calculate movement deltas


	// Only try sliding if there's significant movement in both directions
	// This prevents unwanted sliding when moving directly into a wall
	sliding_move(data, &original_pos, &new_pos);


	// No movement possible - stay in place
}

/**
 * Enhanced player movement with DDA-based collision detection
 */
void	enhanced_player_movement(t_data *data)
{
	double	angle_speed;
	float	cos_angle;
	float	sin_angle;

	angle_speed = torad(1);
	if (data->player->left_rotate)
		data->player->angle += angle_speed;
	if (data->player->right_rotate)
		data->player->angle -= angle_speed;
	if (data->player->angle > torad(360))
		data->player->angle = 0;
	if (data->player->angle < 0)
		data->player->angle = torad(360);
	cos_angle = cos(data->player->angle);
	sin_angle = -sin(data->player->angle);

	if (data->player->key_up)
		enhanced_displace(UP, data, cos_angle, sin_angle);
	if (data->player->key_down)
		enhanced_displace(DOWN, data, cos_angle, sin_angle);
	if (data->player->key_left)
		enhanced_displace(LEFT, data, cos_angle, sin_angle);
	if (data->player->key_right)
		enhanced_displace(RIGHT, data, cos_angle, sin_angle);
}

/* ========== ORIGINAL FUNCTIONS (commented for reference) ========== */

bool	valid_move(t_map *map, int x, int y)
{
	char	*valid_pos;
	char	pos;

	y = y / SQUARE;
	x = x / SQUARE;
	if (y < 0 || y > map->height || x < 0 || x > map->width)
		return (false);
	valid_pos = "NSWE0";
	pos = map->grid[y][x];
	while (*valid_pos)
	{
		if (*valid_pos == pos)
			return (true);
		valid_pos++;
	}
	return (false);
}

float	get_speed(void)
{
	t_data	*data;

	data = recover_data_address(NULL);
	if (data->player->boost)
		return (RUN);
	return (WALK);
}

void	displace(t_move move, t_data *data,
	const float cos_angle, const float sin_angle)
{
	t_coords	coords;

	coords.x = data->player->pos.x;
	coords.y = data->player->pos.y;

	calc_pos(move, &coords, &cos_angle, &sin_angle);
	if (valid_move(data->map, coords.x, coords.y))
	{
		data->player->pos.x = coords.x;
		data->player->pos.y = coords.y;
	}
}

/*
 * ORIGINAL PLAYER MOVEMENT FUNCTION - COMMENTED TO AVOID CONFLICT
 * Use enhanced_player_movement() instead for DDA-based collision detection
 */
/*
void	player_movement(t_data *data)
{
	double	angle_speed;
	float	cos_angle;
	float	sin_angle;

	angle_speed = torad(1);
	if (data->player->left_rotate)
		data->player->angle += angle_speed;
	if (data->player->right_rotate)
		data->player->angle -= angle_speed;
	if (data->player->angle > torad(360))
		data->player->angle = 0;
	if (data->player->angle < 0)
		data->player->angle = torad(360);
	cos_angle = cos(data->player->angle);
	sin_angle = -sin(data->player->angle);

	if (data->player->key_up)
		displace(UP, data, cos_angle, sin_angle);
	if (data->player->key_down)
		displace(DOWN, data, cos_angle, sin_angle);
	if (data->player->key_left)
		displace(LEFT, data, cos_angle, sin_angle);
	if (data->player->key_right)
		displace(RIGHT, data, cos_angle, sin_angle);
}
*/

/* ========== WRAPPER FOR BACKWARD COMPATIBILITY ========== */

/**
 * Wrapper function to maintain compatibility
 * Calls the enhanced movement system
 */
void	player_movement(t_data *data)
{
	enhanced_player_movement(data);
}
