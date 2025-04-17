/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:35:40 by kytan             #+#    #+#             */
/*   Updated: 2025/03/12 16:39:38 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validate.h"
#include "libft.h"
#include "Exit.h"

/**
 * @return If empty, return `TRUE(1)`. Else, return `FALSE(1)`
 */
int	empty_line(char *s)
{
	while (*s)
		if (!ft_isspace(*s++))
			return (0);
	return (1);
}


/**
 * @return The index for the `id_token`
 */
int	id_idx(char *id_token, t_game *game)
{
	if (!ft_strcmp(id_token, "NO"))
		return (0);
	else if (!ft_strcmp(id_token, "SO"))
		return (1);
	else if (!ft_strcmp(id_token, "EA"))
		return (2);
	else if (!ft_strcmp(id_token, "WE"))
		return (3);
	else if (!ft_strcmp(id_token, "F"))
		return (4);
	else if (!ft_strcmp(id_token, "C"))
		return (5);
	exit_free("INVALID-ELEMENTS", game, id_token);
	return (-1);
}