/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:11:35 by kytan             #+#    #+#             */
/*   Updated: 2025/04/17 15:47:40 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"


/**
 * @brief Finds the width of map horizontal boundaries excluding whitespaces
 *
 * Finds the west boundary wall index as `west_boundary_idx`.
 * Finds the east boundary wall index as `east_boundary_idx`.
 * Calculates map width as (east_boundary_idx - west_boundary_idx + 1)
 *
 * @return length of map width
 */
size_t	find_width(char **map_extract, t_parse *parser)
{
	size_t		i;
	size_t		j;
	size_t		west_boundary_idx;
	size_t		east_boundary_idx;

	i = -1;
	west_boundary_idx = -1;
	east_boundary_idx = -1;
	while (map_extract[++i])
	{
		j = 0;
		while (ft_isspace(map_extract[i][j]))
			j++;
		if (j < west_boundary_idx || west_boundary_idx == -1)
			west_boundary_idx = j;
		j = ft_strlen(map_extract[i]);
		while (j && ft_isspace(map_extract[i][j]))
			j--;
		if (j > east_boundary_idx || east_boundary_idx == -1)
			east_boundary_idx = j;
	}
	parser->west_boundary_idx = west_boundary_idx;
	parser->east_boundary_idx = east_boundary_idx;
	return (east_boundary_idx - west_boundary_idx + 1);
}

/**
 * @brief Finds the depth of map vertical boundaries excluding whitespaces
 *
 * Finds the north boundary wall index as `west_boundary_idx`.
 * Finds the south boundary wall index as `east_boundary_idx`.
 * Calculates map depth as (south_boundary_idx - north_boundary_idx + 1)
 *
 * @return length of map depth
 */
size_t	find_depth(char **map_extract, t_parse *parser)
{
	size_t		i;
	size_t		north_boundary_idx;
	size_t		south_boundary_idx;

	i = -1;
	while (map_extract[i] && empty_line(map_extract[i]))
		i++;
// if (!map_extract[i])
// 	exit_free("WHERES THE MAP?", parser, 0);
	north_boundary_idx = i;
	while (map_extract[i] && !empty_line(map_extract[i]))
		i++;
	south_boundary_idx = i - 1;
	while (map_extract[i] && empty_line(map_extract[i]))
		i++;
	if (map_extract[i])
		exit_free("MAP INTEGRITY", parser, 0);
}

static void	map_extraction(int fd, char *line, t_parse *parser)
{
	char	*map_data;
	char	*map_token;

	while (1)
	{
		if (!line)																/* Loop through each line until EOF */
			break ;
		map_token = ft_strtrim(line, " \n");			/* Create token delimited by ' ' & '\n' */
		if (!map_token)														/* Check if token is NULL */
			break ;																	/* Break Condition : If token is NULL */
		map_data = ft_strfjoin(map_data, line);		/* If token is NOT NULL */
		if (!map_data)														/* 	Append line into map_data */
			exit_free("MEMORY-ALLOC", parser, line);
		free(map_token);
		free(line);
		line = get_next_line(fd);
	}
	while (line)																/* If not EOF but there was an empty line break */
	{
		map_token = ft_strtrim(line, " \n");
		if (map_token)														/* Check for no more map elements left in the file */
			exit_free("INVALID MAP INTEGRITY", parser, map_token);
		free(map_token);
		free(line);
		line = get_next_line(fd);
	}
	parser->map_extract = ft_split(map_data, '\n');
}

/**
 * @brief Extracts map data into`s_parse::map_extract`
 *
 * Skips the empty lines between textures and map section.
 * Find pointer to start / head of map section. Clean up
 * tail of map trim '\n' characters. Loop through '\n'
 * characters to check for '\n' character pairs and empty
 * whitespace lines. Extract refined data and free allocated
 * resources.
 *
 * @param raw_data
 * @param parser
 */
void	extract_map_data(int fd, t_parse *parser)
{
	char	*line;
	char	*map_head;
	char	*map_ptr;

	map_head = find_map_head(parser->file_extract, parser->breakpoint_idx);
	line = get_next_line(fd);
	while (1)
	{
		if (!line)
			exit_free("WHERE'S THE MAP?", parser, 0);
		if (ft_strnstr(line, map_head, ft_strlen(line)))
		{
			map_extraction(fd, line, parser);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	parser->map_width = find_width(parser->map_extract, parser);
	parser->map_depth = find_depth(parser->map_extract, parser);
}
