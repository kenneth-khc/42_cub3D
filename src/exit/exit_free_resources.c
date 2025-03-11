/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_resources.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:02:58 by kytan             #+#    #+#             */
/*   Updated: 2025/03/05 15:53:37 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "Game.h"

static void	free_split(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static void	free_textures(char **textures)
{
	int		i;

	i = -1;
	if (!textures)
		return ;
	while (++i < 6)
		if (textures[i])
			free(textures[i]);
	free(textures);
}

void	free_parser(t_game *game)
{
	t_parse parser;

	parser = game->parser;
	if (parser.data_file)
		free_split(parser.data_file);
	if (parser.data_map)
		free_split(parser.data_map);
	if (parser.data_textures)
		free_textures(parser.data_textures);
}

void	exit_free(char *error, t_game *game, char *arg)
{
	if (arg)
	{
		printf("%s ", arg);
		free(arg);
	}
	if (error)
		printf("%s", error);
	free_parser(game);
}