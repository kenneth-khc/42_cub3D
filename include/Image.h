/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:25:39 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 14:28:32 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>

/* A wrapper for an mlx image */
typedef struct s_Image
{
	void	*instance; // the image instance used by mlx
	int		width;
	int		height;
	char	*addr; // the start of the address where the image is stored
	int		pixels; // the number of pixels in this image
	int		bits_per_pixel; // how many bits is used to store a pixel
	int		size_line; // how many pixels in 1 line horizontally across
	int		endian;
}	t_Image;

/* 32 bits to store a RGBA value, access each component through the struct */
typedef union u_Colour
{
	uint32_t	value;
	struct
	{
		uint8_t	blue;
		uint8_t	green;
		uint8_t	red;
		uint8_t	alpha;
	}	s_Component;
}	t_Colour;

void		create_image(void *mlx, t_Image *img, int width, int height);
uint32_t	*get_pixel_addr(t_Image *img, int x, int y);

#endif
