#include "cub3d.h"

// static void	free_single_line(char *temp, t_fd fd)//is this necesary?
// {
// 	char	*free_me;

// 	free_me = get_next_line(fd, CONTINUE);
// 	free(temp);
// 	while (free_me)
// 	{
// 		free(free_me);
// 		free_me = get_next_line(fd, CONTINUE);
// 	}
// }

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

char	*get_next_line(t_fd fd, int reset)//refactor this to comply with norm. move to libft
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	static int	buff_pos;
	static int	buff_len;
	char 		*line;
	char		c;
	int 		byte_read;

	if (reset)
	{
		buffer[0] = 0;
		buff_len = 0;
		buff_pos = 0;
		close(fd.fd);
		fd.fd = open(fd.filename, O_RDONLY);
		if (fd.fd < 0)
		{
			printf("why would you erase the file in the middle of the load, OMG you are such a tryhard");//how will we handle this?
			exit(1);
		}
		return (NULL); // return reset function that returns null. that keeps this statement in only 2 line
	}
	line = NULL;
	byte_read = 0;
	while (1)
	{
		if(buff_pos < buff_len)//we need to somehow make this onto an aux function that returs line or NULL
		{
			c = buffer[buff_pos++];
			if (!str_append_mem(&line, &c, 1))
				return (NULL);
			if (c == '\n')
				return (line);
		}
		else
		{
			byte_read = read(fd.fd, buffer, BUFFER_SIZE);
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

static bool	is_grid_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == '\n')
		return (true);
	return (false);
}

static bool	line_is_grid(char *line)
{
	if (!line)
		return (false);
	while (*line)//*line == '\n'  can this happen?
	{
		if (!is_grid_char(*line))
			return (false);
		line++;
	}
	return (true);
}

static void	debug_print_grid(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
		printf("%s\n", grid[i]);
}

static bool	valid_grid(t_fd fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = get_next_line(fd, CONTINUE);
	while (!line_is_grid(line))
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
		if (line && !line_is_grid(line))
		{
			ret = false;
			break;
		}
	}
	get_next_line(fd, RESET);
	return ret;
}

static char	**get_grid(t_fd fd)
{
	char	*line;
	char	*tmp;
	char	*temp;
	char	**map;

	line = ft_strdup("");
	if (!valid_grid(fd))
		error_handle(ERR_LOAD_MAP, "grid", __FILE__, __LINE__);
	tmp = get_next_line(fd, CONTINUE);//from 149 to 154 transform onto an aux funcion to comply with norm
	while (!line_is_grid(tmp))
	{
		free(tmp);
		tmp = get_next_line(fd, CONTINUE);
	}
	while (tmp)
	{
		temp = line;
		line = ft_strjoin(line, tmp);//can we create a more eficient function that uses the same memory so we dont have to free
		free(tmp);
		free(temp);
		tmp = get_next_line(fd, CONTINUE);
		if (!tmp || tmp[0] == '\n')
			break ;
	}
	map = ft_split(line, '\n');
	if (tmp)
	{
		get_next_line(fd, RESET);
		free(tmp);
		// free_single_line(tmp, fd.fd);
	}
	close(fd.fd);
	free(line);
	return (map);
}

static int	get_map_height(char **grid)
{
	int	height;

	height = -1;
	while (grid[++height])
		;
	return (height);
}

static int	get_map_width(char **grid)
{
	size_t	witdth;
	int	i;

	witdth = 0;
	i = -1;
	while (grid[++i])
		if (ft_strlen(grid[i]) > witdth)
			witdth = ft_strlen(grid[i]);
	return (witdth);
}



static bool	valid_ext(char *filemap)
{
	int		len;

	len = ft_strlen(filemap);
	if (len <= 4)
		return (false);
	if (!ft_strcmp(".cub", filemap + (len - 4)))
		return (true);
	return (false);
}

static bool	get_texture_paths(t_elements *elements, t_fd fd)//TODO
{
	(void)elements;
	(void)fd.fd;
	return (true);
}

static bool	get_colours(t_elements *elements, t_fd fd)//TODO
{
	(void)elements;
	(void)fd;
	return (true);
}

static void	get_elements(t_elements *elements, t_fd fd)//add all allocated files to free_map when implemented
{
	if (!get_texture_paths(elements, fd))
		error_handle(ERR_MAP_ELEM, "texture paths", __FILE__, __LINE__);
	if (!get_colours(elements, fd))
		error_handle(ERR_MAP_ELEM, "colour codes", __FILE__, __LINE__);
}

void	init_map(t_map *map, char *filemap)
{
	t_fd fd;

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
	if (DEBUG)
	{
		debug_print_grid(map->grid);
		printf("\n\nmap width is %i, height is %i\n", map->width, map->height);
	}
}
