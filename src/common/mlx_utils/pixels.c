/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:58:54 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 02:03:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Image.h"
#include <stddef.h>
#include <stdint.h>

/* Index into the pixel array of the image to grab the exact pixel
 * If out of bounds, return NULL instead */
uint32_t	*get_pixel_addr(t_image *img, int x, int y)
{
	const uint64_t	offset = (x * img->bytes_per_pixel) + (y * img->size_line);
	char			*pixel;

	if (offset < img->bytes)
	{
		pixel = &img->addr[offset];
		return ((uint32_t *)pixel);
	}
	else
	{
		return (NULL);
	}
}

/* Converts an address of a pixel into a Colour object */
t_colour	pixel_to_colour(uint32_t *pixel)
{
	t_colour	ret;

	ret.value = *pixel;
	return (ret);
}

t_colour	get_pixel_addr_to_colour(t_image *img, int x, int y)
{
	uint32_t *const	pixel = get_pixel_addr(img, x, y);
	const t_colour	colour = pixel_to_colour(pixel);

	return (colour);
}

/* Draw on an Image's XY by accessing it and changing the pixel value
 * Return true if successful and false otherwise (eg if XY is out of bounds) */
bool	draw_pixel(t_image *img, int x, int y, t_colour colour)
{
	uint32_t	*pixel;

	if (x < img->width && y < img->height)
	{
		pixel = get_pixel_addr(img, x, y);
		if (pixel)
		{
			*pixel = colour.value;
			return (true);
		}
		else
		{
			return (false);
		}
	}
	else
	{
		return (false);
	}
}
