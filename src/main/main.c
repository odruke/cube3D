/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:41:39 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/25 19:46:32 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	init_texture(t_data *data, t_elements *elements)
{
	elements->textures->N_Wall = (t_texture_img *)safe_calloc(sizeof(t_texture_img), 1, 
		__FILE__, __LINE__);
	elements->textures->N_Wall->img = mlx_xpm_file_to_image(data->mlx.mlx_tunnel, elements->path_texture_no,
		&elements->textures->N_Wall->width, &elements->textures->N_Wall->height);
	if (!elements->textures->N_Wall->img)
		error_handle(ERR_MLX, "Couldnt load texture", __FILE__, __LINE__);
	elements->textures->N_Wall->pixel_arr = mlx_get_data_addr(elements->textures->N_Wall->img, &elements->textures->N_Wall->bpp, 
		&elements->textures->N_Wall->line, &elements->textures->N_Wall->endian);
	if (!elements->textures->N_Wall->pixel_arr)
		error_handle(ERR_MLX, "error with get data adrr", __FILE__, __LINE__);
}

void	init_data(t_data *data, char *filemap)
{
	recover_data_address(data);
	data->map = (t_map *)safe_calloc(sizeof(t_map), 1, __FILE__, __LINE__);
	data->map->elements = (t_elements *)safe_calloc(sizeof(t_elements), 1,
		__FILE__, __LINE__);
	data->map->elements->textures = (t_texture *)safe_calloc(sizeof(t_texture), 1,
		__FILE__, __LINE__);
	data->player = (t_camera *)safe_calloc(sizeof(t_camera), 1, __FILE__, __LINE__);
	data->mouse = (t_coords *)safe_calloc(sizeof(t_coords), 1, __FILE__, __LINE__);
	//memory assigment
	init_elements(data->map->elements);
	init_map(data->player, data->map, filemap);
	//different element init
	data->mlx.w = WIN_WIDTH;
	data->mlx.h = WIN_HEIGHT;
	//variable assigment
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
	init_texture(data, data->map->elements);
	//mlx init
	// mlx_mouse_hide(data->mlx.mlx_tunnel, data->mlx.window);
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
	mlx_hook(data->mlx.window, 3, (1L<<1), handle_keyrelease, data);
	mlx_hook(data->mlx.window, 6, (1L << 6), mouse_move, data);
	mlx_loop_hook(data->mlx.mlx_tunnel, loop_hook, data);
	mlx_hook(data->mlx.window, 17, 0, free_and_exit, data);
	mlx_loop(data->mlx.mlx_tunnel);
}
