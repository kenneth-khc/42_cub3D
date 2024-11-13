/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:43:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/12 13:53:44 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "Image.h"
#include "Vector.h"
#include "Game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Create a colour by passing in components of alpha, red, green and blue
 * The components are 8 bit each, packed together in a union to form a 32 bit
 * colour pixel */
t_colour	create_colour(uint8_t alpha, uint8_t red, uint8_t green,
					uint8_t blue)
{
	t_colour	colour;

	colour.s_component.alpha = alpha;
	colour.s_component.red = red;
	colour.s_component.green = green;
	colour.s_component.blue = blue;
	return (colour);
}

/* Create an Image object wrapping an MLX image object, along with data
 * required to manipulate it 
 * Instance is the void* handler of the image passed into/from MLX image
 * functions */
void	create_image(void *mlx, t_image *img, int width, int height)
{
	img->instance = mlx_new_image(mlx, width, height);
	img->width = width;
	img->height = height;
	img->pixels = img->width * img->height;
	img->addr = mlx_get_data_addr(img->instance,
			&img->bits_per_pixel, &img->size_line, &img->endian);
	img->bytes_per_pixel = img->bits_per_pixel / 8;
	img->bytes = img->pixels * img->bytes_per_pixel;
}

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

/* Wrapper for mlx_put_image, taking in an Image object and the point
 * on the screen to display it at */
void	put_image(t_game *game, t_image *img, t_vector_int *screen)
{
	mlx_put_image_to_window(game->mlx, game->window, img->instance,
						 screen->x, screen->y);
}
