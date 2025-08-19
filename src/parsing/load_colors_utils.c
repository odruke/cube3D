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
	bool		found_coma;
	static int	all_codes;

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
	all_codes += 1;
	if (*comas == 2 && !code[*i] && all_codes != 3)
		return (false);
	if (!found_coma && all_codes != 3)
		return (false);
	if (all_codes == 3)
		all_codes = 0;
	return (true);
}

void	init_char_color_id(char *ide[3])
{
	static bool	initialized;

	if (!initialized)
	{
		ide[0] = "F";
		ide[1] = "C";
		ide[2] = NULL;
		initialized = true;
	}
}
