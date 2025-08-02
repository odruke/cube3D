/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:38:49 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/31 17:44:56 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_data *data, t_texture *textures)
{

	if (data->map->elements->textures->n_wall)
	{
		if (textures->n_wall->img)
			mlx_destroy_image(data->mlx->mlx_tunnel, textures->n_wall->img);
		free(data->map->elements->textures->n_wall);
	}
	if (data->map->elements->textures->s_wall)
	{
		if (textures->s_wall->img)
			mlx_destroy_image(data->mlx->mlx_tunnel, textures->s_wall->img);
		free(data->map->elements->textures->s_wall);
	}
	if (data->map->elements->textures->w_wall)
	{
		if (textures->e_wall->img)
			mlx_destroy_image(data->mlx->mlx_tunnel, textures->e_wall->img);
		free(data->map->elements->textures->e_wall);
	}
	if (data->map->elements->textures->e_wall)
	{
		if (textures->w_wall->img)
			mlx_destroy_image(data->mlx->mlx_tunnel, textures->w_wall->img);
		free(data->map->elements->textures->w_wall);
	}
}

static void	free_elements(t_data *data, t_elements *elements)
{
	if (elements->path_texture_ea)
		free(elements->path_texture_ea);
	if (elements->path_texture_no)
		free(elements->path_texture_no);
	if (elements->path_texture_so)
		free(elements->path_texture_so);
	if (elements->path_texture_we)
		free(elements->path_texture_we);
	if (elements->c_color)
		free(elements->c_color);
	if (elements->f_color)
		free(elements->f_color);
	if (elements->textures)
	{
		free_textures(data, elements->textures);
		free(elements->textures);
	}
}

static void	free_mlx(t_data *data)
{
	if (data->mlx->mlx_img)
	{
		if (data->mlx->mlx_img->img)
			mlx_destroy_image(data->mlx->mlx_tunnel, data->mlx->mlx_img->img);
		free(data->mlx->mlx_img);
	}
	if (data->mlx->window)
		mlx_destroy_window(data->mlx->mlx_tunnel, data->mlx->window);
	if (data->mlx->mlx_tunnel)
	{
		mlx_destroy_display(data->mlx->mlx_tunnel);
		free(data->mlx->mlx_tunnel);
	}
}

static void	free_data(t_data *data)
{
	if (data->map)
	{
		if (data->map->elements)
		{
			free_elements(data, data->map->elements);
			free(data->map->elements);
		}
		if (data->map->grid)
			free_table(data->map->grid);
		free(data->map);
	}
	if (data->mini_map)
	{
		if (data->mini_map->img.img)
			mlx_destroy_image(data->mlx->mlx_tunnel, data->mini_map->img.img);
		free(data->mini_map);
	}
	if (data->mlx)
	{
		free_mlx(data);
		free(data->mlx);
	}
}


int	free_and_exit(t_data *data, int exit_code)
{
	if (!data)
		exit(exit_code);
	free_data(data);
	if (data->player)
		free(data->player);
	if (data->mouse)
		free(data->mouse);
	free(data);
	printf("\033[1;35m✨Memory freed successfully🚀\n🚪Exiting game👋\033[0m\n");
	exit(exit_code);
}
