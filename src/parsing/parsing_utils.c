/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:13:51 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/27 17:13:54 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	zeroing_endstring(char **str)
{
	size_t	len;

	len = ft_strlen(*str);
	if (str[0][len - 1] == '\n')
		str[0][len - 1] = '\0';
}

char	*skip_until_grid(t_fd fd)
{
	char	*line;
	int		line_pos;

	line_pos = 1;
	line = get_next_line(fd, CONTINUE);
	while (line && (!line_is_grid(line) || line[0] == '\n'))
	{
		if (!is_element_line_position(line_pos))
		{
			if (!line_is_only_spaces(line))
			{
				free(line);
				error_handle(ERR_MAP_LINE, NULL,
					__FILE__, __LINE__);
			}
		}
		free (line);
		line = get_next_line(fd, CONTINUE);
		line_pos++;
	}
	return (line);
}

bool	color_is_in_range(char *code, int start, int len)
{
	int		nb;
	char	*number;

	nb = 0;
	number = ft_substr(code, start, len);
	nb = ft_atoi(number);
	free(number);
	number = NULL;
	if (nb < 0 || nb > 255)
		return (false);
	return (true);
}

void	fordward_index(char *line, int *i)
{
	while (line[*i] && !ft_isblank(line[++(*i)]))
		;
	while (line[*i] && ft_isblank(line[++(*i)]))
		;
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	if (*s1)
		size1 = ft_strlen(*s1);
	else
		size1 = 0;
	tmp = safe_calloc(size1 + size2 + 1, sizeof(char), __FILE__, __LINE__);
	if (!tmp)
		return (0);
	if (*s1)
	{
		ft_memcpy(tmp, *s1, size1);
		free(*s1);
	}
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	*s1 = tmp;
	return (1);
}
