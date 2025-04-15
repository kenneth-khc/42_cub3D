/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:52:38 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/17 06:22:39 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"
#include "libft.h"
#include "ft_dprintf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

int	open_file(char *filename)
{
	int	fd;

	if (ft_str_endswith(filename, ".cub") == false)
	{
		ft_dprintf(STDERR_FILENO, "Error\n" "Expecting file extension .cub\n");
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error\n" "Failed to open file\n");
		exit(1);
	}
	return (fd);
}

char	*get_next_line_trim_whitespaces(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	trimmed = ft_strtrim(line, " \f\n\r\t\v");
	while (trimmed && trimmed[0] == '\0')
	{
		free(line);
		line = get_next_line(fd);
		trimmed = ft_strtrim(line, " \f\n\r\t\v");
	}
	free(line);
	return (trimmed);
}

char	*get_next_line_trim_newline(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	trimmed = ft_strtrim(line, "\n");
	free(line);
	return (trimmed);
}

char	*get_next_line_skip_empty_lines(int fd)
{
	char	*line;
	size_t	line_len;
	size_t	i;

	line = get_next_line_trim_newline(fd);
	while (line)
	{
		i = 0;
		line_len = ft_strlen(line);
		while (i < line_len)
		{
			if (!is_whitespace(line[i]))
			{
				return (line);
			}
			i++;
		}
		free(line);
		line = get_next_line_trim_newline(fd);
	}
	return (line);
}
