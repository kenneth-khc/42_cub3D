/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:34:30 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 00:01:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "Config.h"
# include "Map.h"
# include <stdbool.h>
# include <stddef.h>

t_config	parse(char *filename);
int			open_file(char *filename);
char		*gnl_trim_whitespaces_skip_empty(int fd);
char		*gnl_trim_newline(int fd);
char		*gnl_trim_newline_skip_empty(int fd);
void		validate_element(t_config *config, char *line);
size_t		identify_type_identifier(char *line, char **type_identifier);
bool		is_whitespace(char c);
bool		is_player(char c);
bool		is_floor(char c);
bool		identified(const char *line, const char *identifier);
void		parse_map_content(t_config *config, char *line);
void		validate_map(t_map *map);
bool		validate_configurables(t_configurable *configurables);

#endif
