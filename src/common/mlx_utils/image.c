/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:43:29 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 01:47:50 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Image.h"
#include "Vector.h"
#include "Game.h"
#include "Utils.h"
#include "ft_dprintf.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

/* Create an Image object wrapping an MLX image object, along with data
 * required to manipulate it 
 * Instance is the void* handler of the image passed into/from MLX image
 * functions */
t_image	create_image(void *mlx, int width, int height)
{
	t_image	img;

	img.instance = mlx_new_image(mlx, width, height);
	if (img.instance == NULL)
	{
		error("mlx_new_image() failed\n");
	}
	img.width = width;
	img.height = height;
	img.pixels = img.width * img.height;
	img.addr = mlx_get_data_addr(img.instance,
			&img.bits_per_pixel, &img.size_line, &img.endian);
	img.bytes_per_pixel = img.bits_per_pixel / 8;
	img.bytes = img.pixels * img.bytes_per_pixel;
	img.pos.x = 0;
	img.pos.y = 0;
	return (img);
}

void	destroy_image(void *mlx, t_image *img)
{
	mlx_destroy_image(mlx, img->instance);
}

/* Wrapper for mlx_put_image, taking in an Image object and the point
 * on the screen to display it at */
void	put_image(t_game *game, t_image *img, t_vec2i *screen)
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

/* Load an XPM file into an Image object */
void	load_image(t_game *game, t_image *img, const char *filename)
{
	img->instance = mlx_xpm_file_to_image(game->mlx, (char *)filename,
			&img->width, &img->height);
	if (img->instance == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Error\nInvalid image filepath\n");
		exit(1);
	}
	img->pixels = img->width * img->height;
	img->addr = mlx_get_data_addr(img->instance,
			&img->bits_per_pixel, &img->size_line, &img->endian);
	img->bytes_per_pixel = img->bits_per_pixel / 8;
	img->bytes = img->pixels * img->bytes_per_pixel;
}
