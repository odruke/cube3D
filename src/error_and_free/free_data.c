/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:38:49 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/15 10:27:59 by tienshi          ###   ########.fr       */
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

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->mlx.mlx_img.img)
		{
			mlx_destroy_image(data->mlx.mlx_tunnel, data->mlx.mlx_img.img);
		}
		if (data->mlx.window)
			mlx_destroy_window(data->mlx.mlx_tunnel, data->mlx.window);
		if (data->mlx.mlx_tunnel)
		{
			mlx_destroy_display(data->mlx.mlx_tunnel);
			free(data->mlx.mlx_tunnel);
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
