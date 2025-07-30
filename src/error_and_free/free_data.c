/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:38:49 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/28 14:01:45 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	if (map->grid)
		free_table(map->grid);
	free(map);
}

void	free_textures(t_data *data, t_texture *textures)
{

	if (data->map->elements->textures->n_Wall)
	{
		mlx_destroy_image(data->mlx->mlx_tunnel, textures->n_Wall->img);
		free(data->map->elements->textures->n_Wall);
	}
	if (data->map->elements->textures->s_Wall)
	{
		mlx_destroy_image(data->mlx->mlx_tunnel, textures->n_Wall->img);
		free(data->map->elements->textures->s_Wall);
	}
	if (data->map->elements->textures->e_Wall)
	{
		mlx_destroy_image(data->mlx->mlx_tunnel, textures->n_Wall->img);
		free(data->map->elements->textures->e_Wall);
	}
	if (data->map->elements->textures->w_Wall)
	{
		mlx_destroy_image(data->mlx->mlx_tunnel, textures->n_Wall->img);
		free(data->map->elements->textures->w_Wall);
	}
}

void	free_elements(t_data *data, t_elements *elements)
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



void	free_minimap(t_data *data)
{
	if (data->mini_map->img.img)
		mlx_destroy_image(data->mlx->mlx_tunnel, data->mini_map->img.img);
	free(data->mini_map);
}

void	free_mlx(t_data *data)
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

void	free_data(t_data *data)//CONFIRM THE CORRECT ORDER OF STRUCTURES TO FREE
{
	if (data)
	{
		if (data->map)
		{
			if (data->map->elements)
			{
				free_elements(data, data->map->elements);
				free(data->map->elements);
			}
			free_map(data->map);
		}
		if (data->player)
			free(data->player);
		if (data->mouse)
			free(data->mouse);
		if (data->mini_map)
			free_minimap(data);
		if (data->mlx)
		{
			free_mlx(data);
			free(data->mlx);
		}
		free(data);
	}
	printf("\033[1;35m✨Memory freed successfully🚀\n🚪Exiting game👋\033[0m\n");
}

int	free_and_exit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}
