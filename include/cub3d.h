/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:23:46 by odruke-s          #+#    #+#             */
/*   Updated: 2025/06/24 11:35:52 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <limits.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# define KILL 1
# define CONTINUE 0
# define TRUE 1
# define FALSE 0
/*# define __FILE__, __LINE__ __FILE__, __LINE__*/
# define ESC_KEY 65307
# define UP_KEY_W 119
# define DOWN_KEY_S 115
# define LEFT_KEY_A 97
# define RIGHT_KEY_D 100
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

typedef enum e_error
{
	ERR_BAD_ARGS,
	ERR_MALLOC,
	ERR_MLX,
	ERR_UNKNOWN
}	t_error;

typedef struct s_errinfo
{
	t_error		error;
	int			exit_code;
	const char	*str_format;
}	t_errinfo;

typedef struct s_errarg
{
	t_error	error;
	char	*cmd;
	char	*file;
	int		line;
	int		terminate;
}	t_errarg;

typedef struct s_data
{
	void		*mlx;
	void		*window;
}	t_data;

/* V data management funcitons V*/

void	init_data(t_data *data, char *map_to_load);
t_data	*recover_data_address(t_data *data);

/* error handeling and exiting functions*/

int		error_handle(t_errarg err_args);
void	free_table(char **table);
void	free_data(t_data *data);
int		free_and_exit(t_data *data);
void	free_list(t_list **list, void (*del)(void *));//?

/* error controled functions */

void	*safe_malloc(size_t bytes, char *file, int line);
void	*safe_calloc(size_t bytes, size_t size, char *file, int line);

/*game control functions*/

int		handle_keypress(int keycode, t_data *data);
int		count_table(char **table);//?

#endif
