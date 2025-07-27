/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:02:54 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/28 01:02:57 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*reset_gnl(char buffer[], int *buff_len, int *buff_pos, t_fd *fd)
{
	buffer[0] = 0;
	*buff_len = 0;
	*buff_pos = 0;
	close(fd->fd);
	fd->fd = open(fd->filename, O_RDONLY);
	if (fd->fd < 0)
	{
		printf("why would you erase the file in the middle of the load??\
 OMG you are such a tryhard.\n");
		exit(1);
	}
	return (NULL);
}

static char	*gnl_loop(char buffer[], int *buff_len, int *buff_pos, t_fd *fd)
{
	char	c;
	int		byte_read;
	char	*line;

	line = NULL;
	while (1)
	{
		if (*buff_pos < *buff_len)
		{
			c = buffer[(*buff_pos)++];
			if (!str_append_mem(&line, &c, 1))
				return (NULL);
			if (c == '\n')
				return (line);
		}
		else
		{
			byte_read = read(fd->fd, buffer, BUFFER_SIZE);
			if (byte_read < 0 || (byte_read == 0))
				return (line);
			*buff_pos = 0;
			*buff_len = byte_read;
		}
	}
	return (line);
}

char	*get_next_line(t_fd fd, int reset)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	static int	buff_pos;
	static int	buff_len;

	if (reset)
		return (reset_gnl(buffer, &buff_len, &buff_pos, &fd));
	return (gnl_loop(buffer, &buff_len, &buff_pos, &fd));
}
