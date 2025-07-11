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

const t_errinfo	*get_errinfo(t_error error)
{
	static t_errinfo	errtab[ERR_UNKNOWN + 1];

	errtab[ERR_BAD_ARGS] = (t_errinfo){ERR_BAD_ARGS, EXIT_FAILURE,
		"Error: Bad input. Usage:\n./cub3D maps/[mapname]\n"};
	errtab[ERR_MALLOC] = (t_errinfo){ERR_MALLOC, EXIT_FAILURE,
		"Malloc failed at: %s:%i\n"};
	errtab[ERR_MLX] = (t_errinfo){ERR_MLX, EXIT_FAILURE,
		"MLX: %s failed at: %s:%i\n"};
	errtab[ERR_UNKNOWN] = (t_errinfo){ERR_UNKNOWN, 1, "%s\n"};
	return (&errtab[error]);
}

int	error_handle(t_errarg err_args)
{
	const t_errinfo	*err_info;
	t_data			*data;

	data = recover_data_address(NULL);
	err_info = get_errinfo(err_args.error);
	if (!err_args.msg)
		printf(err_info->str_format, err_args.file, err_args.line);
	else
		printf(err_info->str_format, err_args.msg, err_args.file,
			err_args.line);
	if (err_args.terminate)
	{
		free_data(data);
		exit(err_info->exit_code);
	}
	else
		return (err_info->exit_code);
}
