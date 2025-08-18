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
		error_handle(ERR_MAP_ELEM, "colour codes", __FILE__, __LINE__);
	if (all_codes == 3)
		all_codes = 0;
	if (!found_coma)
		return (false);
	return (true);
}
