/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:43:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 16:07:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "Image.h"
#include "Vector.h"
#include "Game.h"
#include <stdio.h>

void	create_image(void *mlx, t_image *img, int width, int height)
{
	img->instance = mlx_new_image(mlx, width, height);
	img->width = width;
	img->height = height;
	img->pixels = img->width * height;
	img->addr = mlx_get_data_addr(img->instance,
			&img->bits_per_pixel, &img->size_line, &img->endian);
}

uint32_t	*get_pixel_addr(t_image *img, int x, int y)
{
	const int	bytes_per_pixel = img->bits_per_pixel / 8;
	char		*pixel;

	if (x < img->width && y < img->height)
	{
		pixel = &img->addr[(x * bytes_per_pixel) + (y * img->size_line)];
		return ((uint32_t *)pixel);
	}
	else
	{
		return (NULL);
	}
}

/* Wrapper for mlx_put_image, taking in an Image object and the point
 * on the screen to display it at */
void	put_image(t_game *game, t_image *img, t_vector_int *screen)
{
	mlx_put_image_to_window(game->mlx, game->window, img->instance,
						 screen->x, screen->y);
}
