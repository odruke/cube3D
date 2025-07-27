/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:00:17 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/27 22:00:19 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	color_code(char	*line)
{
	static int	i;
	int			j;
	int			nb;
	char		*number;

	nb = 0;
	j = 0;
	while (line[i + j] && ft_isdigit(line[i + j]))
		j++;
	number = ft_substr(line, i, j);
	nb = ft_atoi(number);
	free(number);
	number = NULL;
	i += j;
	i++;
	if (!line[i] || line_is_only_spaces(line + i))
		i = 0;
	return (nb);

}

static bool	is_valid_color_code(char *code)
{
	int	i;
	int	j;
	int	comas;

	i = -1;
	comas = 0;
	if (!code || !code[0] || !ft_isdigit(code[0]))
		return (false);
	while (code[++i] && comas < 3)
	{
		j = 0;
		while (code[i + j] && ft_isdigit(code[i + j]))
			j++;
		if (comas < 2 && (code[i + j] != ',' || j > 3))
			return (false);
		else if (comas >= 2 && (!line_is_only_spaces(code + (i + j)) || j > 3))
			return (false);
		comas++;
		if (!color_is_in_range(code, i, j))
			return (false);
		i += j;
	}
	return (true);
}

static int	check_ide_and_format_c(char *line, int *i)
{
	static char	*ide[3];
	int			id;

	*i = -1;
	id = -1;
	ide[0] = "F";
	ide[1] = "C";
	ide[2] = NULL;
	while (ft_isblank(line[++(*i)]))
		;
	while (++id < 2)
		if (!ft_strncmp(line + *i, ide[id], 1))
			break ;
	if (id == 2)
		return (-1);
	fordward_index(line, i);
	if (!is_valid_color_code(line + *i))
		return (-1);
	ide[id] = '\0';
	return (id);
}

static void	assign_colors(t_elements *elements, char *line, int i, int ide)
{
	if (ide == 0)
	{
		elements->f_color->r = color_code(line + i);
		elements->f_color->g = color_code(line + i);
		elements->f_color->b = color_code(line + i);
	}
	else if (ide == 1)
	{
		elements->c_color->r = color_code(line + i);
		elements->c_color->g = color_code(line + i);
		elements->c_color->b = color_code(line + i);
	}

}

bool	get_colours(t_elements *elements, t_fd fd)//rename function
{
	char	*line;
	int		ide;
	int		all_colors;
	int		i;

	all_colors = 2;
	line = ft_strdup("");
	while (line)
	{
		free(line);
		line = get_next_line(fd, CONTINUE);
		if (line)
			ide = check_ide_and_format_c(line, &i);
		if (!line || ide < 0)
			continue ;
		assign_colors(elements, line, i, ide);
		all_colors--;
	}
	get_next_line(fd, RESET);
	if (all_colors != 0)
		return (false);
	return (true);
}
