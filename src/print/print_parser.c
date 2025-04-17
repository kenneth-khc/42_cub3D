/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:11:28 by kytan             #+#    #+#             */
/*   Updated: 2025/04/13 22:20:52 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/**
 * @brief Prints integer `num`'s binary representation
 */
void	printBinary(int num)
{
	for (int i = 31; i >= 0; i--) {
			printf("%d", (num >> i) & 1);
	}
	printf("\n");
}

/**
 * Prints out all strings in a null terminated array of strings `split`
 *
 * @note: `split` must be a null-terminated array of strings and every
 * string inside the array must be null-terminated as well
 */
void	print_aos_n(char **split)
{
	int		i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
		printf("%s\n", split[i]);
}

void	print_texture_paths(char **textures)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (textures[i] == NULL)
			printf("NO TEXTURE PATH FOLLOWING TOKEN\n");
		printf("%s\n", textures[i]);
		i++;
	}
}

void	print_raw_data(char *raw_data)
{
	if (!raw_data)
		return ;
	while (*raw_data)
	{
		if (*raw_data == '\n')
			printf("[\n]");
		else
			printf("%c", *raw_data);
		raw_data++;
	}
}

void	print_parser(t_parse *parser)
{
	static int	th_print;

	th_print = 0;
	if (!parser)
		exit_free("INVALID PRINT", 0, 0);
	printf("\nPrinting Parser Info #%i...\n", th_print);
	if (parser->file_extract)
	{
		printf("file_extract {\n");
		print_aos_n(parser->file_extract);
		printf("}\n");
	}
	if (parser->raw_data)
	{
		printf("raw_data {\n");
		print_raw_data(parser->raw_data);
		printf("}\n");
	}
	if (parser->map_textures)
	{
		printf("map_textures {\n");
		print_texture_paths(parser->map_textures);
		printf("}\n");
	}
	if (parser->map_layout)
	{
		printf("map_layout {\n");
		print_aos_n(parser->map_layout);
		printf("}\n");
	}
	printf("map_width: %i\n", parser->map_width);
	printf("map_length: %i\n", parser->map_length);
	printf("breakpoint_idx: %i\n", parser->breakpoint_idx);
}