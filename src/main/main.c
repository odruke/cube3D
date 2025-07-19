/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:41:39 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/19 09:14:05 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		free_and_exit(data);
	else if (keycode == UP_KEY_W)
		data->player->pos.y -= 5;
	else if (keycode == DOWN_KEY_S)
		data->player->pos.y += 5;
	else if (keycode == LEFT_KEY_A)
		data->player->pos.x -= 5;
	else if (keycode == RIGHT_KEY_D)
		data->player->pos.x += 5;
	return (0);
}

t_data	*recover_data_address(t_data *data)
{
	static t_data	*stock_data;

	if (data)
		stock_data = data;
	return (stock_data);
}
void	init_elements(t_elements *elements)
{
	elements->c_color = (t_color *)safe_calloc(sizeof(t_color), 1,
		__FILE__, __LINE__);
	elements->f_color = (t_color *)safe_calloc(sizeof(t_color), 1,
		__FILE__, __LINE__);
	elements->c_color->r = 0;
	elements->c_color->g = 0;
	elements->c_color->b = 0;
	elements->f_color->r = 0;
	elements->f_color->g = 0;
	elements->f_color->b = 0;
	elements->path_texture_ea = NULL;
	elements->path_texture_no = NULL;
	elements->path_texture_so = NULL;
	elements->path_texture_we = NULL;
}

void	init_data(t_data *data, char *filemap)
{
	recover_data_address(data);
	data->map = (t_map *)safe_calloc(sizeof(t_map), 1, __FILE__, __LINE__);
	data->map->elements = (t_elements *)safe_calloc(sizeof(t_elements), 1,
		__FILE__, __LINE__);
	data->player = (t_camera *)safe_calloc(sizeof(t_camera), 1, __FILE__, __LINE__);
	init_elements(data->map->elements);
	init_map(data->player, data->map, filemap);
	data->mlx.w = WIN_WIDTH;
	data->mlx.h = WIN_HEIGHT;
	data->mlx.mlx_tunnel = mlx_init();
	if (!data->mlx.mlx_tunnel)
		error_handle(ERR_MLX, "init", __FILE__, __LINE__);
	data->mlx.window = mlx_new_window(data->mlx.mlx_tunnel,
			data->mlx.w, data->mlx.h, "cub3D");
	if (!data->mlx.window)
		error_handle(ERR_MLX, "new window", __FILE__, __LINE__);
	data->mlx.mlx_img.img = mlx_new_image(data->mlx.mlx_tunnel,
		data->mlx.w, data->mlx.h);
	if (!data->mlx.mlx_img.img)
		error_handle(ERR_MLX, "create image", __FILE__, __LINE__);
	recover_data_address(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	errno = 0;
	if (ac != 2)
		error_handle(ERR_BAD_ARGS, NULL, __FILE__, __LINE__);
	data = safe_calloc(1, sizeof(t_data), __FILE__, __LINE__);
	init_data(data, av[1]);
	printf("\033[1;32m✅ Mlx connection establised \033[0m\n");
	printf("\033[1;32m✅ window created \033[0m\n");
	if (DEBUG)
		print_debug_data(data);
	generate_world(data);
	mlx_hook(data->mlx.window, 2, (1L << 0), handle_keypress, data);
	mlx_hook(data->mlx.window, 17, 0, free_and_exit, data);
	mlx_loop(data->mlx.mlx_tunnel);
}
