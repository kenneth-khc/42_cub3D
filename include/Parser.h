/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:34:07 by kytan             #+#    #+#             */
/*   Updated: 2025/03/18 13:59:22 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TOTAL_TEXTURES 6

typedef struct s_parse
{
	char	**data_file;
	char	**data_textures;
	char	**data_map;

	int	breakpoint_idx;
	int	map_start_i;
	int	map_start_j; 
	int	map_width;
	int	map_height;
}	t_parse;

void	welcome_msg();
void	init_parser(t_game *game);
void	start_parser(t_game *game, char *cub_file);

void	parse_file_data(t_parse *parser, char *cub_file, t_game *game);

void	find_breakpoint_idx(t_parse *parser, t_game *game);