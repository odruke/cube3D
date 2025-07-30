/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:41:39 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/29 16:09:48 by stripet          ###   ########.fr       */
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
void	init_face(t_texture_img *face_img)
{
	face_img->img = NULL;
	face_img->pixel_arr = NULL;
	face_img->line = 0;
	face_img->bpp = 0;
	face_img->endian = 0;
	face_img->img_h = 0;
	face_img->img_w = 0;
}

void	init_textures(t_texture *textures)
{
	alloc_textures(textures);
	init_face(textures->n_Wall);
	init_face(textures->s_Wall);
	init_face(textures->e_Wall);
	init_face(textures->w_Wall);
	textures->side = 0;
}
void	init_elements(t_elements *elements)
{
	elements->c_color = (t_color *)safe_calloc(sizeof(t_color), 1,
		__FILE__, __LINE__);
	elements->f_color = (t_color *)safe_calloc(sizeof(t_color), 1,
		__FILE__, __LINE__);
	elements->textures = (t_texture *)safe_calloc(sizeof(t_texture), 1,
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
	init_textures(elements->textures);
}

void	init_data(t_data *data, char *filemap)
{
	recover_data_address(data);
	data->map = (t_map *)safe_calloc(sizeof(t_map), 1, __FILE__, __LINE__);
	data->map->elements = (t_elements *)safe_calloc(sizeof(t_elements), 1,
		__FILE__, __LINE__);
	data->player = (t_camera *)safe_calloc(sizeof(t_camera), 1, __FILE__, __LINE__);
	data->mouse = (t_mouse *)safe_calloc(sizeof(t_mouse), 1, __FILE__, __LINE__);
	data->mini_map = (t_mini_map *)safe_calloc(sizeof(t_mini_map), 1, __FILE__, __LINE__);
	data->fps = (t_fps *)safe_calloc(sizeof(t_fps), 1, __FILE__, __LINE__);
	data->mlx = (t_mlx *)safe_calloc(sizeof(t_mlx), 1, __FILE__, __LINE__);
	data->mlx->mlx_img = (t_mlx_img *)safe_calloc(sizeof(t_mlx_img), 1, __FILE__, __LINE__);
	data->mlx->mlx_tunnel = mlx_init();
	if (!data->mlx->mlx_tunnel)
		error_handle(ERR_MLX, "init", __FILE__, __LINE__);
	//memory assigment
	init_elements(data->map->elements);
	init_map(data->player, data->map, filemap);
	//different element init
	data->mlx->mlx_img->img_w = WIN_WIDTH;
	data->mlx->mlx_img->img_h = WIN_HEIGHT;
	data->mouse->sens = 0.5;
	data->mini_map->FOV = 20;
	data->mini_map->img.img_w = data->mlx->mlx_img->img_w / 8;
	data->mini_map->img.img_h = data->mlx->mlx_img->img_w / 8;
	//variable assigment

	data->mlx->window = mlx_new_window(data->mlx->mlx_tunnel,
			data->mlx->mlx_img->img_w, data->mlx->mlx_img->img_h, "cub3D");
	if (!data->mlx->window)
		error_handle(ERR_MLX, "new window", __FILE__, __LINE__);
	data->mlx->mlx_img->img = mlx_new_image(data->mlx->mlx_tunnel,
		data->mlx->mlx_img->img_w, data->mlx->mlx_img->img_h);
	if (!data->mlx->mlx_img->img)
		error_handle(ERR_MLX, "create image", __FILE__, __LINE__);
	data->mini_map->img.img = mlx_new_image(data->mlx->mlx_tunnel,
		data->mini_map->img.img_w, data->mini_map->img.img_h);
	if (!data->mini_map->img.img)
		error_handle(ERR_MLX, "create image", __FILE__, __LINE__);
	data->mini_map->img.pixel_arr = mlx_get_data_addr(data->mini_map->img.img, &data->mini_map->img.bpp,
		&data->mini_map->img.line, &data->mini_map->img.endian);
	mlx_mouse_get_pos(data->mlx->mlx_tunnel, data->mlx->window, &data->mouse->x, &data->mouse->y);
	set_textures(data, data->map->elements);
	init_fps(data->fps);
	//mlx init
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
	init_world(data);
	mlx_mouse_hide(data->mlx->mlx_tunnel, data->mlx->window);//THIS FUNCTION LEAKS AS HELL OMG
	mlx_hook(data->mlx->window, 2, (1L<<0), handle_keypress, data);
	mlx_hook(data->mlx->window, 3, (1L<<1), handle_keyrelease, data);
	mlx_hook(data->mlx->window, 6, (1L<<6), mouse_move, data);
	mlx_hook(data->mlx->window, 7, (1L<<4), enter_win, data);
	mlx_loop_hook(data->mlx->mlx_tunnel, loop_hook, data);
	mlx_hook(data->mlx->window, 17, 0, free_and_exit, data);
	mlx_loop(data->mlx->mlx_tunnel);
}
