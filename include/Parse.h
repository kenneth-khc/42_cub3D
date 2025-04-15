/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:34:30 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/17 06:09:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct s_configurable
{
	char	*line;
	char	*type_identifier;

	size_t	identifier_offset;
	size_t	identifier_len;

	size_t	value_offset;
	size_t	value_len;
}	t_configurable;

#define MAX_CONFIGURABLE 6

typedef struct s_config
{
	char			*(*get_next_line)(int);
	t_configurable	configurables[MAX_CONFIGURABLE];
	int				configurables_completed;
	bool			configurables_complete;
}	t_config;

void		parse(char *filename);
t_config	init_blank_config(void);
int			open_file(char *filename);
char		*get_next_line_trim_whitespaces(int fd);
char		*get_next_line_trim_newline(int fd);
char		*get_next_line_skip_empty_lines(int fd);
void		validate_element(t_config *config, char *line);
size_t		identify_type_identifier(char *line, char **type_identifier);
bool		is_whitespace(char c);
bool		identified(const char* line, const char *identifier);
void		parse_map_content(t_config *config, char *line);

#endif
