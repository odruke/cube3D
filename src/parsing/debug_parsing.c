/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:08:10 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/27 17:08:13 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_debug_data(t_data *data)
{
	debug_print_grid(data->map->grid);
	printf("\n\nmap width is %i, height is %i\n",
		data->map->width, data->map->height);
	debug_print_player(data->map->grid, data->player);
	debug_print_texture_path(data->map->elements);
	debug_print_colors(data->map->elements);
}

void	debug_print_grid(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
		printf("%s\n", grid[i]);
}

void	debug_print_texture_path(t_elements *elements)
{
	printf("path to NO is: %s\n", elements->path_texture_no);
	printf("path to SO is: %s\n", elements->path_texture_so);
	printf("path to WE is: %s\n", elements->path_texture_we);
	printf("path to EA is: %s\n", elements->path_texture_ea);
}

void	debug_print_colors(t_elements *elements)
{
	int	r;
	int	g;
	int	b;

	r = elements->c_color->r;
	g = elements->c_color->g;
	b = elements->c_color->b;
	printf("Ceiling color is: R=%i, G=%i, B=%i\n", r, g, b);
	r = elements->f_color->r;
	g = elements->f_color->g;
	b = elements->f_color->b;
	printf("Floor color is: R=%i, G=%i, B=%i\n", r, g, b);
}

void	debug_print_player(char **grid, t_camera *player)
{
	printf("player position is y=%i, x=%i\n", (int)player->pos.y,
		(int)player->pos.x);
	if (grid[(int)player->pos.y][(int)player->pos.x] == 'N')
		printf("Player angle is North: %i°\n\n", toangle(player->angle));
	else if (grid[(int)player->pos.y][(int)player->pos.x] == 'E')
		printf("Player angle is East: %i°\n\n", toangle(player->angle));
	else if (grid[(int)player->pos.y][(int)player->pos.x] == 'S')
		printf("Player angle is South: %i°\n\n", toangle(player->angle));
	else if (grid[(int)player->pos.y][(int)player->pos.x] == 'W')
		printf("Player angle is West: %i°\n\n", toangle(player->angle));
}
