#include "cub3d.h"

static void	debug_print_grid(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
		printf("%s", grid[1]);
}

static bool	valid_grid(int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = get_next_line(fd, CONTINUE);
	while (!line_is_grid)
	{
		free (line);
		line = get_next_line(fd, CONTINUE);
	}
	if (line)
		ret = true;
	while (line)
	{
		free (line);
		line = get_next_line(fd, CONTINUE);
		if (!line_is_grid(line))
		{
			ret = false;
			break;
		}
	}
	get_next_line(fd, RESET);
	return ret;
}

static void	free_single_line(char *temp, int fd)//is this necesary?
{
	char	*free_me;

	free_me = get_next_line(fd, CONTINUE);
	free(temp);
	while (free_me)
	{
		free(free_me);
		free_me = get_next_line(fd, CONTINUE);
	}
}

static char	**get_grid(int fd)
{
	char	*line;
	char	*tmp;
	char	**map;

	line = ft_strdup("");
	if (!valid_grid(fd))
		error_handle(ERR_LOAD_MAP, "grid", __FILE__, __LINE__);
	tmp = get_next_line(fd, CONTINUE);
	while (!line_is_grid(tmp))
	{
		free(tmp);
		tmp = get_next_line(fd, CONTINUE);
	}
	while (tmp)
	{

		tmp = get_next_line(fd, CONTINUE);
		if (!tmp || tmp[0] == '\n')
			break ;
		line = ft_strjoin(line, tmp);
		free(tmp);
	}
	map = ft_split(line, '\n');
	if (tmp)
		free_single_line(tmp, fd);
	close(fd);
	free(line);
	return (map);
}

static int	get_map_lenght(char **grid)
{
	int	lenght;

	lenght = -1;
	while (grid[++lenght])
		;
	return (lenght);
}

static int	get_map_width(int **grid)
{
	int	witdth;
	int	i;

	witdth = 0;
	i = -1;
	while (grid[++i])
		if (ft_strlen(grid[i]) > witdth)
			witdth = ft_strlen(grid[i]);
	return (witdth);
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
	if (!line)
		return (false);
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

static bool	get_texture_paths(t_elements elements, int fd)//TODO
{

}

static bool	get_colours(t_elements elements, int fd)//TODO
{

}

static void	get_elements(t_elements elements, int fd)//bad approach, could must refactor. getline will update the buffer position,
{													//and the elements could be mixed on the file so it could miss some elements
	if (!get_texture_paths(elements, fd))			//posible solutions: unify both texture and colors search in one function | reset getline somehow. check the until <line_is_grid> or EOF
		error_handle(ERR_MAP_ELEM, "texture paths", __FILE__, __LINE__);
	if (!get_colours(elements, fd))
		error_handle(ERR_MAP_ELEM, "colour codes", __FILE__, __LINE__);
}

int str_append_mem(char **s1, char *s2, size_t size2)//refactor this | use ft_strjoin. move to libft
{
	size_t size1 = (*s1) ? ft_strlen(*s1) : 0;//ternary not norminette compliant
	char *tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return 0;
	if (*s1)
	{
		ft_memcpy(tmp, *s1, size1);
		free(*s1);
	}
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	*s1 = tmp;
	return 1;
}

char	*get_next_line(int fd, int reset)//refactor this to comply with norminette. move to libft
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	static int	buff_pos;
	static int	buff_len;
	char 		*line;
	char		c;
	int 		byte_read;

	if (reset)
	{
		buffer[0] = NULL;
		buff_len = 0;
		buff_pos = 0;
		return (NULL);
	}
	line = NULL;
	byte_read = 0;
	while (1)
	{
		if(buff_pos < buff_len)
		{
			c = buffer[buff_pos++];
			if (!str_append_mem(&line, &c, 1))
				return (NULL);
			if (c == '\n')
				return (line);
		}
		else
		{
			byte_read = read(fd, buffer, BUFFER_SIZE);
			if(byte_read < 0)
				return (NULL);
			if (byte_read == 0)
				return (line);
			buff_pos = 0;
			buff_len = byte_read;
		}
	}
	return line;
}

void	init_map(t_map map, char *filemap)
{
	int fd;

	if (!valid_ext(filemap))
		error_handle(ERR_MAP_EXT, filemap, __LINE__, __FILE__);
	fd = open(filemap, O_RDONLY);
	if (fd < 0)
		error_handle(ERR_LOAD_MAP, filemap, __LINE__, __FILE__);//will a file named ".cub" pass from here?
	get_elements(map.elements, fd);
	map.grid = get_grid(fd);
	map.length = get_map_length(map.grid);
	map.width = get_map_width(map.grid);
	if (DEBUG)
	{
		debug_print_grid(map.grid);
		printf("map width is %i, height is %i", map.width, map.length);
	}
}
