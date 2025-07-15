#include "cub3d.h"

bool	is_grid_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == '\n')
		return (true);
	return (false);
}

bool	line_is_grid(char *line)
{
	if (!line)
		return (false);
	while (*line)
	{
		if (!is_grid_char(*line))
			return (false);
		line++;
	}
	return (true);
}

bool	line_is_only_spaces(char *line)
{
	while (*line || *line == '\n')
	{
		if (*line != ' ' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

int	check_grid(t_fd fd)
{
	char	*line;
	int		size;

	size = 0;
	line = skip_until_grid(fd);
	if (line)
		size = 1;
	while (line)
	{
		free (line);
		line = get_next_line(fd, CONTINUE);
		if (line && (!line_is_grid(line) || line_is_only_spaces(line)))
		{
			free(line);
			size = 0;
			break;
		}
		size++;
	}
	get_next_line(fd, RESET);
	return size;
}

bool	valid_ext(char *filemap)
{
	int		len;

	len = ft_strlen(filemap);
	if (len <= 4)
		return (false);
	if (!ft_strcmp(".cub", filemap + (len - 4)))
		return (true);
	return (false);
}
