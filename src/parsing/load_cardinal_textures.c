/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cardinal_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:59:35 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/27 21:59:39 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_texture_path(t_elements *elements,
	char *line, int i, int ide)
{
	char	*assign;
	int 	len;

	len = ft_strlen(line);
	if (ft_isblank(line[len -1]) && ft_isblank(line[len -1]))
	{
		while (len > 2 && ft_isblank(line[len -1]))
			len--;
		if (line[len] == ' ')
			line[len] = '\0';
	}
	assign = ft_strndup(line + i, len - 1);
	zeroing_endstring(&assign);
	if (ide == 0)
		elements->path_texture_no = assign;
	else if (ide == 1)
		elements->path_texture_so = assign;
	else if (ide == 2)
		elements->path_texture_we = assign;
	else if (ide == 3)
		elements->path_texture_ea = assign;
}

static	int	check_ide_and_format(char *line, int *i)
{
	static char	*ide[5];
	int			id;

	*i = -1;
	id = -1;
	ide[0] = "NO";
	ide[1] = "SO";
	ide[2] = "WE";
	ide[3] = "EA";
	ide[4] = NULL;
	while (ft_isblank(line[++(*i)]))
		;
	while (++id < 4)
		if (!ft_strncmp(line + *i, ide[id], 2))
			break ;
	if (id == 4)
		return (-1);
	fordward_index(line, i);
	if (ft_strncmp(line + *i, "./", 2))
		return (-1);
	ide[id] = '\0';
	return (id);

}

bool	get_texture_paths(t_elements *elements, t_fd fd)
{
	char	*line;
	int		ide;
	int		all_paths;
	int		i;

	all_paths = 4;
	line = ft_strdup("");
	while (line)
	{
		free(line);
		line = get_next_line(fd, CONTINUE);
		if (line)
			ide = check_ide_and_format(line, &i);
		if (!line || ide < 0)
			continue ;
		assign_texture_path(elements, line, i, ide);
		all_paths--;
	}
	get_next_line(fd, RESET);
	if (all_paths != 0)
		return (false);
	return (true);
}
