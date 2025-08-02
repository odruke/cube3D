/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:53:25 by tienshi           #+#    #+#             */
/*   Updated: 2025/07/31 00:03:25 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	valid_txtr_ext(char *filemap)
{
	int		len;

	len = ft_strlen(filemap);
	if (len <= 4)
		return (false);
	if (!ft_strcmp(".xpm", filemap + (len - 4)))
		return (true);
	return (false);
}

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, __O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

void	valid_textures(t_elements *elements)
{
	if (is_dir(elements->path_texture_ea))
		error_handle(ERR_TXTUR_DIR, elements->path_texture_ea,
			__FILE__, __LINE__);
	if (is_dir(elements->path_texture_no))
		error_handle(ERR_TXTUR_DIR, elements->path_texture_no,
			__FILE__, __LINE__);
	if (is_dir(elements->path_texture_so))
		error_handle(ERR_TXTUR_DIR, elements->path_texture_so,
			__FILE__, __LINE__);
	if (is_dir(elements->path_texture_we))
		error_handle(ERR_TXTUR_DIR, elements->path_texture_we,
			__FILE__, __LINE__);
	if (!valid_txtr_ext(elements->path_texture_ea))
		error_handle(ERR_TXTUR_EXT, elements->path_texture_ea,
			__FILE__, __LINE__);
	if (!valid_txtr_ext(elements->path_texture_no))
		error_handle(ERR_TXTUR_EXT, elements->path_texture_no,
			__FILE__, __LINE__);
	if (!valid_txtr_ext(elements->path_texture_so))
		error_handle(ERR_TXTUR_EXT, elements->path_texture_so,
			__FILE__, __LINE__);
	if (!valid_txtr_ext(elements->path_texture_we))
		error_handle(ERR_TXTUR_EXT, elements->path_texture_we,
			__FILE__, __LINE__);
}
