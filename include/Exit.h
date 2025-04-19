/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:25:27 by kytan             #+#    #+#             */
/*   Updated: 2025/04/19 15:39:52 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "Game.h"

void	exit_free(char *error_msg, t_parse *parser, char *mem);

void	free_parser(t_parse *parser);