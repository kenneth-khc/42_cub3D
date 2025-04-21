/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 04:15:56 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 05:45:45 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include <stdlib.h>
#include <math.h>

void	error(const char *err_msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	ft_dprintf(STDERR_FILENO, err_msg);
	exit(1);
}

/* Converts an angle in degrees to an angle in radians because C functions
 * work with radians only */
double	radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

/* Converts an angle in radians into degrees */
double	degrees(double radians)
{
	return (radians * 180.0 / M_PI);
}
