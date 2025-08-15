/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:34:43 by odruke-s          #+#    #+#             */
/*   Updated: 2025/08/15 14:53:57 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_element_position(t_elements *elements, int index)
{
	int			*pos_len;
	int			i;
	int			*tmp;

	i = -1;
	pos_len = &elements->positions->len;
	if (!elements->positions->pos)
	{
		elements->positions->pos = safe_calloc(sizeof(int), 1,
				__FILE__, __LINE__);
		elements->positions->pos[0] = index;
		*pos_len += 1;
	}
	else
	{
		*pos_len += 1;
		tmp = elements->positions->pos;
		elements->positions->pos = safe_calloc(sizeof(int), *pos_len,
				__FILE__, __LINE__);
		while (++i < *pos_len - 1)
			elements->positions->pos[i] = tmp[i];
		elements->positions->pos[i] = index;
		free(tmp);
	}
}

bool	is_element_line_position(int line_pos)
{
	t_data	*data;
	int		*positions;
	int		len;
	int		i;

	i = -1;
	data = recover_data_address(NULL);
	positions = data->map->elements->positions->pos;
	len = data->map->elements->positions->len;
	while (++i < len)
	{
		if (positions[i] == line_pos)
			return (true);
	}
	return (false);
}
