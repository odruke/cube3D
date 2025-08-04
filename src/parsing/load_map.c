/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:08:53 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/30 17:14:33 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**get_grid(t_fd fd)
{
	char	**map;
	int		size;
	int		i;

	i = 0;
	size = check_grid(fd);
	if (!size)
		error_handle(ERR_MAP_ELEM, "grid", __FILE__, __LINE__);
	map = (char **)safe_calloc(sizeof(char *), size + 1, __FILE__, __LINE__);
	map[0] = skip_until_grid(fd);
	while (map[i])
	{
		zeroing_endstring(&map[i]);
		i++;
		map[i] = get_next_line(fd, CONTINUE);
	}
	return (map);
}

static void	get_elements(t_elements *elements, t_fd fd)
{
	if (!get_texture_paths(elements, fd))
		error_handle(ERR_MAP_ELEM, "texture paths", __FILE__, __LINE__);
	if (!get_colours(elements, fd))
		error_handle(ERR_MAP_ELEM, "colour codes", __FILE__, __LINE__);
}

void	square_grid(char **grid, int max_x)
{
	int		y;
	char	*tmp;

	y = -1;
	while (grid[++y])
	{
		while ((int)ft_strlen(grid[y]) < max_x)
		{
			tmp = grid[y];
			grid[y] = ft_strjoin(grid[y], " ");
			free(tmp);
		}
	}
}

double	get_player_angle(char **grid, t_coords coords)
{
	if (grid[(int)coords.y][(int)coords.x] == 'N')
		return (90);
	if (grid[(int)coords.y][(int)coords.x] == 'E')
		return (0);
	if (grid[(int)coords.y][(int)coords.x] == 'S')
		return (270);
	if (grid[(int)coords.y][(int)coords.x] == 'W')
		return (180);
	return (-1);
}

void	init_map(t_camera *player, t_map *map, char *filemap)
{
	t_fd	fd;
	char	**ff_grid;

	ff_grid = NULL;
	if (!valid_ext(filemap))
		error_handle(ERR_MAP_EXT, filemap, __FILE__, __LINE__);
	fd.fd = open(filemap, O_RDONLY);
	if (fd.fd < 0)
		error_handle(ERR_LOAD_MAP, filemap, __FILE__, __LINE__);
	fd.filename = filemap;
	get_elements(map->elements, fd);
	map->grid = get_grid(fd);
	map->height = get_map_height(map->grid);
	map->width = get_map_width(map->grid);
	square_grid(map->grid, map->width);
	ff_grid = copy_grid(map->grid, map->height);
	player->pos = valid_grid(ff_grid, map->height, map->width);
	player->angle = torad(get_player_angle(map->grid, player->pos));
	free_table(ff_grid);
	close(fd.fd);
}
