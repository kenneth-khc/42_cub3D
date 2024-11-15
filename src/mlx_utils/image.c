/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:43:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/14 18:25:21 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "Image.h"
#include "Vector.h"
#include "Game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

/* Fill an Image with a certain colour, think memset but for Images */
void	fill_image(t_image *img, const t_colour colour)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			draw_pixel(img, x, y, colour);
			x++;
		}
		y++;
	}
}

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
