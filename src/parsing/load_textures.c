#include "cub3d.h"

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
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
    if (!is_dir(elements->path_texture_ea))
		error_handle(ERR_TXTUR_EXT,  elements->path_texture_ea, __FILE__, __LINE__);
	if (!is_dir(elements->path_texture_no))
		error_handle(ERR_TXTUR_EXT,  elements->path_texture_no, __FILE__, __LINE__);
	if (!is_dir(elements->path_texture_so))
		error_handle(ERR_TXTUR_EXT,  elements->path_texture_so, __FILE__, __LINE__);
	if (!is_dir(elements->path_texture_we))
		error_handle(ERR_TXTUR_EXT,  elements->path_texture_we, __FILE__, __LINE__);
	if (!valid_txtur_ext(elements->path_texture_ea))
		error_handle(ERR_TXTUR_EXT,  elements->path_texture_ea, __FILE__, __LINE__);
	if (!valid_txtur_ext(elements->path_texture_no))
		error_handle(ERR_TXTUR_EXT,  elements->path_texture_no, __FILE__, __LINE__);
	if (!valid_txtur_ext(elements->path_texture_so))
		error_handle(ERR_TXTUR_EXT,  elements->path_texture_so, __FILE__, __LINE__);
	if (!valid_txtur_ext(elements->path_texture_we))
		error_handle(ERR_TXTUR_EXT,  elements->path_texture_we, __FILE__, __LINE__);

}

void	get_textures(t_data *data, t_elements *elements)
{
	valid_textures(elements);
	elements->textures->E_Wall.img = safe_xpm_to_img(data->mlx.mlx_tunnel, elements->path_texture_ea, &(int){0}, &(int){0});
	elements->textures->N_Wall->img = safe_xpm_to_img(data->mlx.mlx_tunnel, elements->path_texture_no, &(int){0}, &(int){0});
	elements->textures->S_Wall.img = safe_xpm_to_img(data->mlx.mlx_tunnel, elements->path_texture_so, &(int){0}, &(int){0});
	elements->textures->W_Wall.img = safe_xpm_to_img(data->mlx.mlx_tunnel, elements->path_texture_we, &(int){0}, &(int){0});
}



