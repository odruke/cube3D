#include "cub3d.h"

int str_append_mem(char **s1, char *s2, size_t size2)//refactor this | use ft_strjoin. move to libft
{
	size_t size1 = (*s1) ? ft_strlen(*s1) : 0;//ternary not norminette compliant
	char *tmp = malloc(size1 + size2 + 1);//make it with safe function
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



static char	**get_grid(t_fd fd)
{
	char	**map;
	int		size;
	int		i;

	i = 0;
	size = check_grid(fd);
	if (!size)
		error_handle(ERR_LOAD_MAP, "grid", __FILE__, __LINE__);
	map = (char **)safe_calloc(sizeof(char *), size + 1, __FILE__, __LINE__);
	map[0] = skip_until_grid(fd);
	while (map[i])
	{
		zeroing_endstring(&map[i]);
		i++;
		map[i] = get_next_line(fd, CONTINUE);
	}
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

static void	get_elements(t_elements *elements, t_fd fd)
{
	if (!get_texture_paths(elements, fd))
		error_handle(ERR_MAP_ELEM, "texture paths", __FILE__, __LINE__);
	if (!get_colours(elements, fd))
		error_handle(ERR_MAP_ELEM, "colour codes", __FILE__, __LINE__);
}

void	square_grid(char **grid, int max_x)
{
	int		y;
	char	*tmp;

	y = -1;
	while (grid[++y])
		while ((int)ft_strlen(grid[y]) < max_x)
		{
			tmp = grid[y];
			grid[y] = ft_strjoin(grid[y], " ");
			free(tmp);
		}
}

float	get_player_angle(char **grid, t_coords coords)
{
	if(grid[(int)coords.y][(int)coords.x] == 'N')
		return (90);
	if(grid[(int)coords.y][(int)coords.x] == 'E')
		return (0);
	if(grid[(int)coords.y][(int)coords.x] == 'S')
		return (270);
	if(grid[(int)coords.y][(int)coords.x] == 'W')
		return (180);
	return (-1);
}

void	init_map(t_camera *player, t_map *map, char *filemap)
{
	t_fd	fd;
	char	**ff_grid;

	ff_grid = NULL;
	if (!valid_ext(filemap))
		error_handle(ERR_MAP_EXT, filemap, __FILE__, __LINE__);
	fd.fd = open(filemap, O_RDONLY);
	if (fd.fd < 0)
		error_handle(ERR_LOAD_MAP, filemap, __FILE__, __LINE__);
	fd.filename = filemap;
	//add a function here that checks that any line without elements or grid is \n or space
	get_elements(map->elements, fd);
	map->grid = get_grid(fd);
	map->height = get_map_height(map->grid);
	map->width = get_map_width(map->grid);
	square_grid(map->grid, map->width);
	ff_grid = copy_grid(map->grid, map->height);
	player->pos = valid_grid(ff_grid, map->height, map->width);
	player->angle = torad(get_player_angle(map->grid, player->pos));
	free_table(ff_grid);
	close(fd.fd);
}
