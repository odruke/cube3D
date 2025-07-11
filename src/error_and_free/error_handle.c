/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:38:25 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/11 14:07:48 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*err_str_format(t_error error)
{
	static char	*errstr_tab[ERR_UNKNOWN + 1];

	errstr_tab[ERR_BAD_ARGS] = "Error: Bad input. Usage:\n./cub3D maps/[mapname]\n";
	errstr_tab[ERR_MALLOC] = "Malloc failed at: %s:%i\n";
	errstr_tab[ERR_MLX] = "MLX: %s failed at: %s:%i\n";
	errstr_tab[ERR_LOAD_MAP] = "Can't open file %s. Failed at: %s:%i\n";
	errstr_tab[ERR_MAP_EXT] = "%s is not a .cub file. Failed at: %s:%i\n";
	errstr_tab[ERR_UNKNOWN] = "%s\n";
	return (errstr_tab[error]);
}


int	error_handle(t_error error, char *msg, char *file, int line)
{
	const char	*err_str;
	t_data			*data;

	data = recover_data_address(NULL);
	err_str = err_str_format(error);
	if (!msg)
		printf(err_str, file, line);
	else
		printf(err_str, msg, file, line);
	free_data(data);
	exit(EXIT_FAILURE);
}
