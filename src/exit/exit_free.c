/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:10:11 by kytan             #+#    #+#             */
/*   Updated: 2025/04/18 12:14:12 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/**
 * Prints out all strings in a null terminated array of strings `split`
 *
 * @note: `split` must be a null-terminated array of strings and every
 * string inside the array must be null-terminated as well
 */
void	free_aos_n(char **split)
{
	int		i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	free_parser(t_parse *parser)
{
	if (!parser)
		exit_free("INVALID FREE", 0, 0);
	if (parser->file_extract)
		free_aos_n(parser->file_extract);
	if (parser->raw_data)
		free(parser->raw_data);
	if (parser->map_textures)
		free_aos_n(parser->map_textures);
	if (parser->map_layout)
		free_aos_n(parser->map_layout);
}


/**
 * @note THIS EXIT_FREE() is originally suppose to just take n free an `t_parse` struct ONLY
 * @note If you'll be using this you need to use it to take in and free up `t_game`
 *
 * @brief Exits the program with an error message and frees the allocated resources
 */
void	exit_free(char *error_msg, t_parse *parser, char *mem)
{
	ft_printf("Error\n");
	if (mem)
		printf("%s ", mem);
	if (error_msg)
		printf(": %s\n", error_msg);
	print_parser(parser);
	free_parser(parser);
	exit(1);
}