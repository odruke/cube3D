/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stripet <stripet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:55:24 by stripet           #+#    #+#             */
/*   Updated: 2025/07/11 14:00:03 by stripet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_check(char *map)
{
    char    *buffer;

    buffer = ft_split(map, '.');
    if (!buffer)
        error_handle((t_errarg){ERR_BAD_ARGS, map, __FILE__, __LINE__, KILL});
    
}