/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:59:49 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/26 09:22:34 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "Map.h"
# include <stddef.h>

typedef struct s_configurable
{
	char		*line;
	const char	*type_identifier;

	size_t		identifier_offset;
	size_t		identifier_len;

	size_t		value_offset;
	size_t		value_len;
}	t_configurable;

# define MAX_CONFIGURABLE 6

typedef struct s_config
{
	char			*(*get_next_line)(int);
	t_configurable	configurables[MAX_CONFIGURABLE];
	int				configurables_completed;
	t_map			map;
}	t_config;

void			destroy_config(t_config *config);
const char		*validate_type_identifier(char *line);
t_configurable	set(const char *type_identifier, char *line);

#endif
