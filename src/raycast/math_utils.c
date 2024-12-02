/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:03:30 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/17 00:19:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Vector.h"

/* Converts an angle in degrees to an angle in radians because C functions
 * work with radians only */
double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

/* Converts an angle in radians into degrees */
double	radians_to_degrees(double radians)
{
	return (radians * 180.0 / M_PI);
}
