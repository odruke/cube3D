/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:30:28 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/28 01:30:31 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_height(char **grid)
{
	int	height;

	height = -1;
	while (grid[++height])
		;
	return (height);
}

int	get_map_width(char **grid)
{
	size_t	witdth;
	int		i;

	witdth = 0;
	i = -1;
	while (grid[++i])
		if (ft_strlen(grid[i]) > witdth)
			witdth = ft_strlen(grid[i]);
	return (witdth);
}
