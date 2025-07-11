/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:41:39 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/11 14:03:52 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		free_and_exit(data);
	return (0);
}

t_data	*recover_data_address(t_data *data)
{
	static t_data	*stock_data;

	if (data)
		stock_data = data;
	return (stock_data);
}

void	init_data(t_data *data, char *map_to_load)
{
	(void)map_to_load;
	data->mlx = mlx_init();
	if (!data->mlx)
		error_handle((t_errarg){ERR_MLX, "init", __FILE__, __LINE__, KILL});
	data->window = mlx_new_window(data->mlx,
			800, 600, "cub3D");
	if (!data->window)
		error_handle((t_errarg){ERR_MLX,
			"new window", __FILE__, __LINE__, KILL});
	recover_data_address(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	errno = 0;
	if (ac != 2)
		error_handle((t_errarg){ERR_BAD_ARGS, NULL, __FILE__, __LINE__, KILL});
	data = safe_calloc(1, sizeof(t_data), __FILE__, __LINE__);
	init_data(data, av[1]);
	printf("\033[1;32m✅ Mlx connection establised \033[0m\n");
	printf("\033[1;32m✅ window created \033[0m\n");
	mlx_hook(data->window, 2, (1L << 0), handle_keypress, data);
	mlx_hook(data->window, 17, 0, free_and_exit, data);
	mlx_loop(data->mlx);
}
