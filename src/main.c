/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:41:39 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/31 00:41:18 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*recover_data_address(t_data *data)
{
	static t_data	*stock_data;

	if (data)
		stock_data = data;
	return (stock_data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	errno = 0;
	if (ac != 2)
		error_handle(ERR_BAD_ARGS, NULL, __FILE__, __LINE__);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (-1);
	init_data(data, av[1]);
	printf("\033[1;32m✅ Mlx connection establised \033[0m\n");
	printf("\033[1;32m✅ window created \033[0m\n");
	if (DEBUG)
		print_debug_data(data);
	data->player->pos.x *= SQUARE;//might want to change all functinons to not need that if im not too lazy
	data->player->pos.y *= SQUARE;
	mlx_hook_start(data);
}
