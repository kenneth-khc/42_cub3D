/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:11:35 by kytan             #+#    #+#             */
/*   Updated: 2025/04/16 14:00:56 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

/**
 * @brief Extracts and stores raw file data into `s_parse::file_extract`
 *
 * Opens and reads from file descriptor `fd`. Concatenates each line into
 * one single string inside `raw_data`. Performs `ft_split()` to create
 * to separate the lines delimited by `\n`.
 */
void	extract_file_data(int fd, t_parse *parser)
{
	char	*raw_data;
	char	**file_data;
	char	*line;

	raw_data = ft_calloc(1, sizeof(char));
	if (!raw_data)
		exit_free("MEMORY-ALLOC", parser, 0);
	line = get_next_line(fd);
	while (1)
	{
		if (!line)
			break;
		raw_data = ft_strfjoin(raw_data, line);
		if (!raw_data)
			exit_free("MEMORY-ALLOC", parser, 0);
		free(line);
		line = get_next_line(fd);
	}
	file_data = ft_split(raw_data, '\n');
	if (!file_data)
		exit_free("MEMORY-ALLOC", parser, 0);
	close(fd);
	parser->file_extract = file_data;
}
