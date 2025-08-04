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
