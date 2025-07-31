/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:38:25 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/31 11:40:23 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*err_str_format(t_error error)
{
	static char	*errstr_tab[ERR_UNKNOWN + 1];

	errstr_tab[ERR_BAD_ARGS] = "Error:\nUsage:\n./cub3D maps/[mapname]\n";
	errstr_tab[ERR_MALLOC] = "Malloc failed at: %s:%i\n";
	errstr_tab[ERR_MLX] = "MLX: %s failed at: %s:%i\n";
	errstr_tab[ERR_LOAD_MAP] = "Error:\nCan't open file %s.\n";
	errstr_tab[ERR_MAP_EXT] = "Error:\n%s is not a .cub file.\n";
	errstr_tab[ERR_MAP_ELEM] = "Error:\nCan't find element %s on map file.\n";
	errstr_tab[ERR_GRID_BAD_ITEM] = "Error:\nBad items on grid: %s.\n";
	errstr_tab[ERR_TXTUR_OPEN] = "Error:\nCant open texture: %s.\n";
	errstr_tab[ERR_TXTUR_EXT] = "Error:\n%s is not a .xpm file.\n";
	errstr_tab[ERR_TXTUR_DIR] = "Error:\n%s is a directory!!.\n";
	errstr_tab[ERR_UNKNOWN] = "%s\n";
	return (errstr_tab[error]);
}

static const char	*debug_err_str_format(t_error error)
{
	static char	*errstr_tab[ERR_UNKNOWN + 1];

	errstr_tab[ERR_BAD_ARGS] = "Error:\n\
Bad input. Usage:\n./cub3D maps/[mapname]\n";
	errstr_tab[ERR_MALLOC] = "Malloc failed at: %s:%i\n";
	errstr_tab[ERR_MLX] = "MLX: %s failed at: %s:%i\n";
	errstr_tab[ERR_LOAD_MAP] = "Error:\nCan't open file %s. Failed at: %s:%i\n";
	errstr_tab[ERR_MAP_EXT] = "Error:\n\
%s is not a .cub file. Failed at: %s:%i\n";
	errstr_tab[ERR_MAP_ELEM] = "Error:\n\
Can't find element %s on map file. Failed at: %s:%i\n";
	errstr_tab[ERR_GRID_BAD_ITEM] = "Error:\n\
Bad items on grid: %s. Failed at: %s:%i\n";
	errstr_tab[ERR_TXTUR_OPEN] = "Error:\nCant open texture: %s.\
Failed at: %s:%i\n";
	errstr_tab[ERR_TXTUR_EXT] = "Error:\n%s is not a .xpm file.\
Failed at: %s:%i\n";
	errstr_tab[ERR_TXTUR_DIR] = "Error:\n%s is a directory!!.\
Failed at: %s:%i\n";
	errstr_tab[ERR_UNKNOWN] = "%s\n";
	return (errstr_tab[error]);
}

int	error_handle(t_error error, char *msg, char *file, int line)
{
	const char	*err_str;
	t_data		*data;

	data = recover_data_address(NULL);
	if (DEBUG)
		err_str = debug_err_str_format(error);
	else
		err_str = err_str_format(error);
	if (!msg)
		printf(err_str, file, line);
	else
		printf(err_str, msg, file, line);
	free_and_exit(data, EXIT_FAILURE);
	return (-42);
}
