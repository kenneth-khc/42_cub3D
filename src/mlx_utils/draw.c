/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:15:54 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/15 23:31:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Image.h"

/* Draws a square with a length of 2*half_dimensions based on the centre point */
void	draw_box(t_image *img,
				const t_vector_int centre,
				const int half_dimension,
				const t_colour colour)
{
	const t_vector_int	end
		= {.x = centre.x + half_dimension, .y = centre.y + half_dimension};
	t_vector_int		start;
	int					x;

	start.x = centre.x - half_dimension;
	start.y = centre.y - half_dimension;
	x = start.x;
	while (start.y != end.y)
	{
		start.x = x;
		while (start.x != end.x)
		{
			draw_pixel(img, start.x, start.y, colour);
			start.x++;
		}
		start.y++;
	}
}

/* Draws a border around an Image using the given thiccness */
void	draw_border(t_image *img, const int thiccness, const t_colour colour)
{
	int	x;
	int	y;
	int	thicc;

	thicc = 0;
	while (thicc < thiccness)
	{
		x = 0;
		while (x < img->width)
		{
			draw_pixel(img, x, 0 + thicc, colour);
			draw_pixel(img, x, img->height - 1 - thicc, colour);
			x++;
		}
		y = 0;
		while (y < img->height)
		{
			draw_pixel(img, 0 + thicc, y, colour);
			draw_pixel(img, img->width - 1 - thicc, y, colour);
			y++;
		}
		thicc++;
	}
}
