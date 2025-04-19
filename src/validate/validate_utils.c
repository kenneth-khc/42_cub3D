/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 06:10:04 by kytan             #+#    #+#             */
/*   Updated: 2025/04/18 12:49:57 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.h"
#include "libft.h"

/**
 * @return If `token` is a valid identifier ie. "NO", "SO",
 * "EA" & "WE", returns TRUE(1). Else, return FALSE(0).
 */
int	valid_identifier(char *token)
{
	if (!token)
		return (0);
	else if (!ft_strcmp(token, "NO") || !ft_strcmp(token, "SO"))
		return (1);
	else if (!ft_strcmp(token, "EA") || !ft_strcmp(token, "WE"))
		return (1);
	else if (!ft_strcmp(token, "F") || !ft_strcmp(token, "C"))
		return (1);
	return (0);
}


/**
 * @return The index for the `id_token`
 */
int	id_idx(char *id_token, t_parse *parser)
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
	exit_free("INVALID TEXTURES", parser, id_token);
	return (6);
}

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