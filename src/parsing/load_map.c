#include "cub3d.h"

static char	**get_grid(int fd)//TODO
{

}

static int	get_map_lenght(int fd)//TODO?
{

}

static int	get_map_width(int fd)//TODO?
{

}

static bool	is_grid_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

static bool	line_is_grid(char *line)
{
	while (*line)
	{
		if (!is_grid_char)
			return (false);
		line++;
	}
	return (true);
}

static bool	valid_ext(char *filemap)
{
	char	*check;
	int		len;

	len = ft_strlen(filemap);
	check = ft_strnstr(filemap, ".cub", ft_strlen(filemap));
	if (check == filemap + (len - 4))
		return (true);
	return (false);
}

char	*get_next_line(int fd)
{
	
}

void	init_map(t_map map, char *filemap)
{
	int fd;

	if (!valid_ext(filemap))
		error_handle(ERR_MAP_EXT, filemap, __LINE__, __FILE__);
	fd = open(filemap, O_RDONLY);
	if (fd < 0)
		error_handle(ERR_LOAD_MAP, filemap, __LINE__, __FILE__);//will a file named ".cub" pass from here?
	map.grid = get_grid(fd);
	map.length = get_map_length(fd);
	map.width = get_map_width(fd);
}
