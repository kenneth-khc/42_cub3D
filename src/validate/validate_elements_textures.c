/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements_textures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:46:54 by kytan             #+#    #+#             */
/*   Updated: 2025/03/12 01:06:13 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Validate.h"
#include "libft.h"


/**
 * @return The index for the `id_token`
 */
static int	id_idx(char *id_token, t_game *game)
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

/**
 * @return If `token` is a valid identifier ie. "NO", "SO",
 * "EA" & "WE", returns TRUE(1). Else, return FALSE(0).
 */
static int	valid_identifier(char *token)
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

void	validate_data_textures(char **file_data, t_game *game)
{
	int		i;
	char	*token;
	int		txtr_flags;

	i = -1;
	token = 0;
	txtr_flags  = 0;
	while (file_data[++i] && txtr_flags != FULFILLED)
	{
		if (empty_line(file_data[i]))
			continue ;
		token = ft_strtok(file_data[i], ' ');
		if (!token)
			exit_free("MEMORY-ALLOC", game, 0);
		if (!valid_identifier(token))
			exit_free("INVALID-ELEMENTS", game, token);
		if (txtr_flags & (1 << id_idx(token, game)))
			exit_free("INVALID-ELEMENTS", game, token);
		txtr_flags ^= 1 << id_idx(token, game);
		free(token);
	}
	if (txtr_flags != FULFILLED)
		exit_free("INVALID-ELEMENTS", game, 0);
	game->parser.breakpoint_idx = i;
}