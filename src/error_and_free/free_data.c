/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:38:49 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/11 14:03:34 by stripet          ###   ########.fr       */
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
		if (data->window)
			mlx_destroy_window(data->mlx, data->window);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
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
