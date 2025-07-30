//
/*   ERASE THIS FILE BEFORE BEFORE PRESENTING THE PROJECT */
#include "cub3d.h"

/**
 * Initialize the FPS counter structure
 */
void	init_fps(t_fps *fps)
{
	fps->frame_count = 0;
	fps->last_time = clock();
	fps->fps = 0.0f;
	fps->fps_text[0] = '\0';
}

/**
 * Update FPS counter - calculates FPS every 30 frames for stability
 */
void	update_fps(t_fps *fps)
{
	clock_t	current_time;
	double	time_diff;

	fps->frame_count++;

	// Update FPS display every 30 frames for more stable reading
	if (fps->frame_count >= 30)
	{
		current_time = clock();
		time_diff = (double)(current_time - fps->last_time) / CLOCKS_PER_SEC;

		if (time_diff > 0)
		{
			fps->fps = fps->frame_count / time_diff;
			snprintf(fps->fps_text, sizeof(fps->fps_text), "FPS: %.1f", fps->fps);
		}

		fps->frame_count = 0;
		fps->last_time = current_time;
	}
}

/**
 * Draw FPS counter on screen at top-left corner
 */
void	draw_fps(t_data *data)
{
	if (data->fps->fps_text[0] != '\0')
	{
		mlx_string_put(data->mlx->mlx_tunnel, data->mlx->window,
			10, 20, RED, data->fps->fps_text);
	}
}
