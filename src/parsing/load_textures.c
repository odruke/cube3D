#include "cub3d.h"

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, __O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

static bool	valid_txtur_ext(char *filemap)
{
	int		len;

	len = ft_strlen(filemap);
	if (len <= 4)
		return (false);
	if (!ft_strcmp(".xpm", filemap + (len - 4)))
		return (true);
	return (false);
}

static void	valid_textures(t_elements *elements)
{
	if (is_dir(elements->path_texture_ea))
		error_handle(ERR_TXTUR_DIR, elements->path_texture_ea,
			__FILE__, __LINE__);
	if (is_dir(elements->path_texture_no))
		error_handle(ERR_TXTUR_DIR, elements->path_texture_no,
			__FILE__, __LINE__);
	if (is_dir(elements->path_texture_so))
		error_handle(ERR_TXTUR_DIR, elements->path_texture_so,
			__FILE__, __LINE__);
	if (is_dir(elements->path_texture_we))
		error_handle(ERR_TXTUR_DIR, elements->path_texture_we,
			__FILE__, __LINE__);
	if (!valid_txtur_ext(elements->path_texture_ea))
		error_handle(ERR_TXTUR_EXT, elements->path_texture_ea,
			__FILE__, __LINE__);
	if (!valid_txtur_ext(elements->path_texture_no))
		error_handle(ERR_TXTUR_EXT, elements->path_texture_no,
			__FILE__, __LINE__);
	if (!valid_txtur_ext(elements->path_texture_so))
		error_handle(ERR_TXTUR_EXT, elements->path_texture_so,
			__FILE__, __LINE__);
	if (!valid_txtur_ext(elements->path_texture_we))
		error_handle(ERR_TXTUR_EXT, elements->path_texture_we,
			__FILE__, __LINE__);

}

void	alloc_textures(t_texture *textures)
{
	textures->n_Wall = (t_texture_img *)safe_calloc(sizeof(t_texture_img), 1,
			__FILE__, __LINE__);
	textures->s_Wall = (t_texture_img *)safe_calloc(sizeof(t_texture_img), 1,
			__FILE__, __LINE__);
	textures->e_Wall = (t_texture_img *)safe_calloc(sizeof(t_texture_img), 1,
			__FILE__, __LINE__);
	textures->w_Wall = (t_texture_img *)safe_calloc(sizeof(t_texture_img), 1,
			__FILE__, __LINE__);
}

void	get_texture_images(t_data *data, t_elements *elements)
{
	t_texture	*textures;

	textures = elements->textures;
	textures->n_Wall->img = safe_xpm_to_img(data, elements->path_texture_no,
			&textures->n_Wall->img_w, &textures->n_Wall->img_h);
	textures->s_Wall->img = safe_xpm_to_img(data, elements->path_texture_so,
			&textures->s_Wall->img_w, &textures->s_Wall->img_h);
	textures->e_Wall->img = safe_xpm_to_img(data, elements->path_texture_ea,
			&textures->e_Wall->img_w, &textures->e_Wall->img_h);
	textures->w_Wall->img = safe_xpm_to_img(data, elements->path_texture_we,
			&textures->w_Wall->img_w, &textures->w_Wall->img_h);
}

void	get_pixel_array(t_texture *textures)
{
	t_texture_img	*current;

	current = textures->n_Wall;
	current->pixel_arr = safe_mlx_get_data_addr(current->img, &current->bpp,
			&current->line, &current->endian);
	current = textures->s_Wall;
	current->pixel_arr = safe_mlx_get_data_addr(current->img, &current->bpp,
			&current->line, &current->endian);
	current = textures->e_Wall;
	current->pixel_arr = safe_mlx_get_data_addr(current->img, &current->bpp,
			&current->line, &current->endian);
	current = textures->w_Wall;
	current->pixel_arr = safe_mlx_get_data_addr(current->img, &current->bpp,
			&current->line, &current->endian);
}

void	init_textures(t_data *data, t_elements *elements)
{

	valid_textures(elements);
	alloc_textures(elements->textures);
	get_texture_images(data, elements);
	get_pixel_array(elements->textures);

}



