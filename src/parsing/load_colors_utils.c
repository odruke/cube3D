/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_colors_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:15:33 by odruke-s          #+#    #+#             */
/*   Updated: 2025/08/04 18:15:35 by odruke-s         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	fordward_next_color_code(char *code, int *i, int *comas)
{
	bool	found_coma;

	found_coma = false;
	while (code[*i] && (ft_isblank(code[*i]) || code[*i] == ','))
	{
		if (code[*i] == ',')
		{
			if (found_coma)
				return (false);
			found_coma = true;
			*comas += 1;
			*i += 1;
			continue ;
		}
		*i += 1;
	}
	return (true);
}
