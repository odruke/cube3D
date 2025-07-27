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
	str[0][len - 1] = '\0';
}

char	*skip_until_grid(t_fd fd)
{
	char	*line;

	line = get_next_line(fd, CONTINUE);
	while (!line_is_grid(line) || line[0] == '\n')
	{
		free (line);
		line = get_next_line(fd, CONTINUE);
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
