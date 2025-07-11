/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:23:46 by odruke-s          #+#    #+#             */
/*   Updated: 2025/07/11 14:07:48 by stripet          ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
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

typedef struct s_data
{
	void		*mlx;
	void		*window;
}	t_data;

/* V data management funcitons V*/

void	init_data(t_data *data, char *map_to_load);
t_data	*recover_data_address(t_data *data);

/* error handeling and exiting functions*/

int		error_handle(t_error error, char *msg, char *file, int line);
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
