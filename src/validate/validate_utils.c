/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:35:40 by kytan             #+#    #+#             */
/*   Updated: 2025/03/12 01:05:48 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validate.h"
#include "libft.h"
#include "Exit.h"

/**
 * @return If empty, return `TRUE(1)`. Else, return `FALSE(1)`
 */
int	empty_line(char *s)
{
	while (*s)
		if (!ft_isspace(*s++))
			return (0);
	return (1);
}