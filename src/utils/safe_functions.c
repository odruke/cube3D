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

void	*safe_xpm_to_img(t_data *data, char *path, int *width, int *height)
{
	void	*ret;

	ret = mlx_xpm_file_to_image(data->mlx->mlx_tunnel, path, width, height);
	if (!ret)
		error_handle(ERR_TXTUR_OPEN, path, __FILE__, __LINE__);
	return (ret);
}

void	*safe_mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
	int *size_line, int *endian)
{
	void	*ret;

	ret = mlx_get_data_addr(img_ptr, bits_per_pixel, size_line,
			endian);
	if (!ret)
		error_handle(ERR_MLX, "error with get data adrr", __FILE__, __LINE__);
	return (ret);
}
