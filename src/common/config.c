/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:00:55 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 00:01:29 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.h"
#include <stdlib.h>

void	destroy_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < MAX_CONFIGURABLE)
	{
		free(config->configurables[i].line);
		i++;
	}
}

