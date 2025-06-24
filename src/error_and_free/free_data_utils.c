/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:39:17 by odruke-s          #+#    #+#             */
/*   Updated: 2025/06/24 11:39:23 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
		free(table[i++]);
	free(table);
}
