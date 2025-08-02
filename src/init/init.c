/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:39:55 by tienshi           #+#    #+#             */
/*   Updated: 2025/08/01 09:21:52 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_face(t_data *data, t_mlx_img *face_img, char *path)
{
	face_img->img = NULL;
	face_img->pixel_arr = NULL;
	face_img->line = 0;
	face_img->bpp = 0;
	face_img->endian = 0;
	face_img->img_h = 0;
	face_img->img_w = 0;
	face_img->img = safe_xpm_to_img(data, path, face_img);
	face_img->pixel_arr = safe_mlx_get_data_addr(face_img->img, &face_img->bpp,
			&face_img->line, &face_img->endian);
}

static void	init_textures(t_elements *elements, t_texture *textures)
{
	t_data	*data;

	data = recover_data_address(NULL);
	valid_textures(elements);
	textures->n_wall = (t_mlx_img *)safe_calloc(sizeof(t_mlx_img), 1,
			__FILE__, __LINE__);
	textures->s_wall = (t_mlx_img *)safe_calloc(sizeof(t_mlx_img), 1,
			__FILE__, __LINE__);
	textures->w_wall = (t_mlx_img *)safe_calloc(sizeof(t_mlx_img), 1,
			__FILE__, __LINE__);
	textures->e_wall = (t_mlx_img *)safe_calloc(sizeof(t_mlx_img), 1,
			__FILE__, __LINE__);
	init_face(data, textures->n_wall, elements->path_texture_no);
	init_face(data, textures->s_wall, elements->path_texture_so);
	init_face(data, textures->w_wall, elements->path_texture_we);
	init_face(data, textures->e_wall, elements->path_texture_ea);
	textures->side = 0;
	textures->wall_hit = 0;
}

static void	alloc_mem(t_data *data)
{
	data->mlx = (t_mlx *)safe_calloc(sizeof(t_mlx), 1, __FILE__, __LINE__);
	data->mlx->mlx_img = (t_mlx_img *)safe_calloc(sizeof(t_mlx_img), 1,
			__FILE__, __LINE__);
	data->map = (t_map *)safe_calloc(sizeof(t_map), 1, __FILE__, __LINE__);
	data->map->elements = (t_elements *)safe_calloc(sizeof(t_elements), 1,
			__FILE__, __LINE__);
	data->map->elements->textures = (t_texture *)safe_calloc(sizeof(t_texture),
			1, __FILE__, __LINE__);
	data->map->elements->c_color = (t_color *)safe_calloc(sizeof(t_color),
			1, __FILE__, __LINE__);
	data->map->elements->f_color = (t_color *)safe_calloc(sizeof(t_color),
			1, __FILE__, __LINE__);
	data->mini_map = (t_mini_map *)safe_calloc(sizeof(t_mini_map), 1,
			__FILE__, __LINE__);
	data->player = (t_camera *)safe_calloc(sizeof(t_camera), 1,
			__FILE__, __LINE__);
	data->mouse = (t_mouse *)safe_calloc(sizeof(t_mouse), 1,
			__FILE__, __LINE__);
	data->dda = (t_dda *)safe_calloc(sizeof(t_dda), 1, __FILE__, __LINE__);
}

void	init_data(t_data *data, char *filemap)
{
	recover_data_address(data);
	alloc_mem(data);
	data->mlx->mlx_img->img_w = WIN_WIDTH;
	data->mlx->mlx_img->img_h = WIN_HEIGHT;
	data->mouse->sens = 0.5;
	data->mini_map->fov = 20;
	data->mini_map->img.img_w = data->mlx->mlx_img->img_w / 6;
	data->mini_map->img.img_h = data->mini_map->img.img_w;
	data->mlx->mlx_tunnel = mlx_init();
	if (!data->mlx->mlx_tunnel)
		error_handle(ERR_MLX, "init", __FILE__, __LINE__);
	data->mlx->window = mlx_new_window(data->mlx->mlx_tunnel,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->mlx->window)
		error_handle(ERR_MLX, "new window", __FILE__, __LINE__);
	init_map(data->player, data->map, filemap);
	init_textures(data->map->elements, data->map->elements->textures);
	data->mlx->mlx_img->img = mlx_new_image(data->mlx->mlx_tunnel,
			data->mlx->mlx_img->img_w, data->mlx->mlx_img->img_h);
	if (!data->mlx->mlx_img->img)
		error_handle(ERR_MLX, "create image", __FILE__, __LINE__);
	data->mlx->mlx_img->pixel_arr = safe_mlx_get_data_addr(\
data->mlx->mlx_img->img, &data->mlx->mlx_img->bpp, &data->mlx->mlx_img->line,
			&data->mlx->mlx_img->endian);
	data->mini_map->img.img = mlx_new_image(data->mlx->mlx_tunnel,
			data->mini_map->img.img_w, data->mini_map->img.img_h);
	if (!data->mini_map->img.img)
		error_handle(ERR_MLX, "create image", __FILE__, __LINE__);
	data->mini_map->img.pixel_arr = safe_mlx_get_data_addr(\
data->mini_map->img.img, &data->mini_map->img.bpp, &data->mini_map->img.line,
			&data->mini_map->img.endian);
	mlx_mouse_get_pos(data->mlx->mlx_tunnel, data->mlx->window,
		&data->mouse->x, &data->mouse->y);
	recover_data_address(data);
}

void	mlx_hook_start(t_data *data)
{
	mlx_mouse_hide(data->mlx->mlx_tunnel, data->mlx->window);
	mlx_hook(data->mlx->window, 2, (1L << 0), handle_keypress, data);
	mlx_hook(data->mlx->window, 3, (1L << 1), handle_keyrelease, data);
	mlx_hook(data->mlx->window, 6, (1L << 6), mouse_move, data);
	mlx_hook(data->mlx->window, 7, (1L << 4), enter_win, data);
	mlx_loop_hook(data->mlx->mlx_tunnel, loop_hook, data);
	mlx_hook(data->mlx->window, 17, 0, free_and_exit, data);
	mlx_loop(data->mlx->mlx_tunnel);
}
