/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:07:58 by kytan             #+#    #+#             */
/*   Updated: 2025/03/05 18:24:29 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "Game.h"

static char	**retrieve_file_data(int fd, t_game *game)
{
	char	*raw_data;
	char	**file_data;
	char	*line;

	raw_data = ft_calloc(1, sizeof(char));
	if (!raw_data)
		return (exit_free("MEMORY-ALLOC", game, 0));
	line = get_next_line(fd);
	while (1)
	{
		if (!line)
			break;
		raw_data = ft_strfjoin(raw_data, line);
		if (!raw_data)
			return (exit_free("MEMORY-ALLOC", game, line));
		free(line);
		line = get_next_line(fd);
	}
	file_data = ft_split(raw_data, '\n');
	free(raw_data);
	close(fd);
	return (file_data);
}

void	parse_file_data(t_parse *parser, char *cub_file, t_game *game)
{
	int				fd;

	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		exit_free("MEMORY-ALLOC", game, 0);
	parser->data_file = retrieve_file_data(fd, game);
	if (!game->parser.data_file)
		exit_free("MEMORY-ALLOC", game, 0);
}