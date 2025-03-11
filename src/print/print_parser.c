/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:40:31 by kytan             #+#    #+#             */
/*   Updated: 2025/03/05 13:01:48 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "Game.h"

void	print_split(char **split, char *title)
{
	int		i;

	i = -1;
	printf("%s", title);
	while (split[++i])
		printf("[%s]", split[i]);
	printf("\n");
}

void	print_split(char **textures)
{
	int		i;

	i = -1;
	printf("DATA TEXTURES\n");
	while (textures[++i])
		if (!textures[i])
			printf("[%s]", textures[i]);
	printf("\n");
}

void	print_parser(t_game *game)
{
	t_parse parser;

	parser = game->parser;
	print("breakpoint_index = %i\n", parser.breakpoint_idx);
	print_split(parser.data_file, "DATA FILE\n");
	print_split(parser.data_map, "DATA MAP\n");
	print_textures(parser.data_textures);
}