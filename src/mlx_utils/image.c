/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:43:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 15:22:38 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "Image.h"
#include <stdio.h>

void	create_image(void *mlx, t_Image *img, int width, int height)
{
	img->instance = mlx_new_image(mlx, width, height);
	img->width = width;
	img->height = height;
	img->pixels = img->width * height;
	img->addr = mlx_get_data_addr(img->instance,
			&img->bits_per_pixel, &img->size_line, &img->endian);
}

uint32_t	*get_pixel_addr(t_Image *img, int x, int y)
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
