/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tienshi <tienshi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:55:24 by stripet           #+#    #+#             */
/*   Updated: 2025/07/14 09:53:52 by tienshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool map_check(char *map)
{
    char    **buffer;

    buffer = ft_split(map, '.');
    if (!buffer)
        error_handle(ERR_BAD_ARGS, map, __FILE__, __LINE__);
    return (false);
}
