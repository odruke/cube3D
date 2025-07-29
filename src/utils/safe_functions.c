/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:39:43 by odruke-s          #+#    #+#             */
/*   Updated: 2025/06/24 11:39:45 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*safe_malloc(size_t bytes, char *file, int line)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		error_handle(ERR_MALLOC, NULL, file, line);
	return (res);
}

void	*safe_calloc(size_t bytes, size_t size, char *file, int line)
{
	void	*res;

	res = ft_calloc(bytes, size);
	if (!res)
		error_handle(ERR_MALLOC, NULL, file, line);
	return (res);
}
