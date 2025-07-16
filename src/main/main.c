/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:41:39 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/16 14:48:32 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	switch (keycode)
	{
		case ESC_KEY:
			free_and_exit(data);
			break;
		case UP_KEY_W:
			data->player.pos.y -= 5;
			draw();
			break;
		case DOWN_KEY_S:
			data->player.pos.y += 5;
			draw();
			break;
		case LEFT_KEY_A:
			data->player.pos.x -= 5;
			draw();
			break;
		case RIGHT_KEY_D:
			data->player.pos.x += 5;
			draw();
			break;
	}
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
	init_elements(data->map->elements);
	init_map(data->map, filemap);//implementation not finished
	data->mlx.w = 1601;
	data->mlx.h = 801;
	data->player.pos.x = data->mlx.w / 2;
	data->player.pos.y = data->mlx.h / 2;
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
	draw();
	mlx_hook(data->mlx.window, 2, (1L << 0), handle_keypress, data);
	mlx_hook(data->mlx.window, 17, 0, free_and_exit, data);
	mlx_loop(data->mlx.mlx_tunnel);
}
