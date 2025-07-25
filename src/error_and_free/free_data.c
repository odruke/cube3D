/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:38:49 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/25 19:43:37 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_list(t_list **list, void (*del)(void *))
{
	t_list	*tmp;

	if (!list || !*list)
		return ;
	if (!del)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->content)
			del((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}
void	free_map(t_map *map)
{
	if (map->grid)
		free_table(map->grid);
	free(map);
}

void	free_elements(t_elements *elements)
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
	free(elements);
}

void	free_textures(t_data *data)
{
	if (data->map->elements->textures)//will need to see this
	{
		if (data->map->elements->textures->N_Wall)
		{
			mlx_destroy_image(data->mlx.mlx_tunnel, data->map->elements->textures->N_Wall->img);
			free(data->map->elements->textures->N_Wall);
		}
		free(data->map->elements->textures);
	}
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->mlx.mlx_img.img)
		{
			mlx_destroy_image(data->mlx.mlx_tunnel, data->mlx.mlx_img.img);
		}
		if (data->map->elements->textures)
			free_textures(data);
		if (data->mlx.window)
			mlx_destroy_window(data->mlx.mlx_tunnel, data->mlx.window);
		if (data->mlx.mlx_tunnel)
		{
			mlx_destroy_display(data->mlx.mlx_tunnel);
			free(data->mlx.mlx_tunnel);
		}
		if (data->map)
		{
			if (data->map->elements)
				free_elements(data->map->elements);
			free_map(data->map);
		}
		if (data->player)
			free(data->player);
		if (data->mouse)
			free(data->mouse);
		free(data);
	}
	printf("\033[1;35m✨Memory freed successfully🚀\n🚪Exiting game👋\033[0m\n");
}

int	free_and_exit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}
