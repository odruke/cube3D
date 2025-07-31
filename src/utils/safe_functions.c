/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:39:43 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/31 22:31:06 by tienshi          ###   ########.fr       */
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

void	*safe_xpm_to_img(t_data *data, char *path, t_mlx_img *img)
{
	void	*ret;

	ret = mlx_xpm_file_to_image(data->mlx->mlx_tunnel, path,
			&img->img_w, &img->img_h);
	if (!ret)
		error_handle(ERR_TXTUR_OPEN, path, __FILE__, __LINE__);
	return (ret);
}

char	*safe_mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
	int *size_line, int *endian)
{
	char	*ret;

	ret = mlx_get_data_addr(img_ptr, bits_per_pixel, size_line,
			endian);
	if (!ret)
		error_handle(ERR_MLX, "error with get data adrr", __FILE__, __LINE__);
	return (ret);
}
