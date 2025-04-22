/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:46:11 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 22:46:33 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include <math.h>

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

t_vec2i	vec2i(t_vec2d dv)
{
	t_vec2i	iv;

	iv.x = dv.x;
	iv.y = dv.y;
	return (iv);
}
