/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:52:38 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 05:34:42 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include "Utils.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

int	open_file(char *filename)
{
	int	fd;

	if (ft_str_endswith(filename, ".cub") == false)
	{
		error("Expecting file extension .cub\n");
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		error("Failed to open file\n");
	}
	return (fd);
}

/* Calls get_next_line(), trims away leading and trailing white spaces,
 * and discard empty lines */
char	*gnl_trim_whitespaces_skip_empty(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	trimmed = ft_strtrim(line, " \f\n\r\t\v");
	while (trimmed && trimmed[0] == '\0')
	{
		free(line);
		free(trimmed);
		line = get_next_line(fd);
		trimmed = ft_strtrim(line, " \f\n\r\t\v");
	}
	free(line);
	return (trimmed);
}

/* Calls get_next_line() and trims away the ending newline character */
char	*gnl_trim_newline(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	trimmed = ft_strtrim(line, "\n");
	free(line);
	return (trimmed);
}

/* Calls get_next_line(), trimming away ending newline characters and
 * discarding empty lines. The goal is to skip across all empty lines between
 * the last configurable and the first line of the map description */
char	*gnl_trim_newline_skip_empty(int fd)
{
	char	*line;

	line = gnl_trim_newline(fd);
	while (line && line[0] == '\0')
	{
		free(line);
		line = gnl_trim_newline(fd);
	}
	return (line);
}
