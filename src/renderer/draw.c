/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:37:20 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/12 13:54:07 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.h>
#include "Image.h"

/* Draws a line of pixels vertically onto an Image */
void	draw_vertical(t_image *img, t_vector_int start, t_vector_int end,
				t_colour colour)
{
	const int	x = start.x;
	int			step;

	if (start.y > end.y)
	{
		step = -1;
	}
	else
	{
		step = +1;
	}
	while (start.y != end.y)
	{
		draw_pixel(img, x, start.y, colour);
		start.y += step;
	}
}
