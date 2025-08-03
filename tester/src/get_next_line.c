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

#include "cube_test.h"


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cast_dst;
	unsigned char	*cast_src;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	cast_dst = (unsigned char *)dst;
	cast_src = (unsigned char *)src;
	while (n > i)
	{
		cast_dst[i] = cast_src[i];
		i++;
	}
	return (dst);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	if (*s1)
		size1 = strlen(*s1);
	else
		size1 = 0;
	tmp = calloc(size1 + size2 + 1, sizeof(char));
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

static void	*reset_gnl(char buffer[], int *buff_len, int *buff_pos, t_fd *fd)
{
	buffer[0] = 0;
	*buff_len = 0;
	*buff_pos = 0;
	close(fd->fd);
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
