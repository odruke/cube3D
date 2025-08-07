/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_components.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:05:40 by odruke-s          #+#    #+#             */
/*   Updated: 2025/08/07 14:05:43 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_core(t_mlx *mlx)
{
	mlx->mlx_tunnel = mlx_init();
	if (!mlx->mlx_tunnel)
		error_handle(ERR_MLX, "init", __FILE__, __LINE__);
	mlx->window = mlx_new_window(mlx->mlx_tunnel,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!mlx->window)
		error_handle(ERR_MLX, "new window", __FILE__, __LINE__);
}

void	init_mlx_images(t_mlx *mlx, t_mini_map *mini_map)
{
	t_mlx_img	*mlx_img;

	mlx_img = mlx->mlx_img;
	mlx_img->img = mlx_new_image(mlx->mlx_tunnel, mlx_img->img_w,
			mlx_img->img_h);
	if (!mlx_img->img)
		error_handle(ERR_MLX, "create mlx image", __FILE__, __LINE__);
	mlx_img->pixel_arr = safe_mlx_get_data_addr(mlx_img->img,
			&mlx_img->bpp, &mlx_img->line, &mlx_img->endian);
	mini_map->img.img = mlx_new_image(mlx->mlx_tunnel,
			mini_map->img.img_w, mini_map->img.img_h);
	if (!mini_map->img.img)
		error_handle(ERR_MLX, "create minimap image", __FILE__, __LINE__);
	mini_map->img.pixel_arr = safe_mlx_get_data_addr(mini_map->img.img,
			&mini_map->img.bpp, &mini_map->img.line, &mini_map->img.endian);
}
