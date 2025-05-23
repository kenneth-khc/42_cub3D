/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:25:39 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 23:20:33 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>
# include "Vector.h"
# include "Colours.h"

/* A wrapper for an mlx image */
typedef struct s_image
{
	void		*instance; // the image instance used by mlx
	int			width;
	int			height;
	char		*addr; // the start of the address where the image is stored
	uint64_t	pixels; // the number of pixels in this image
	int			bits_per_pixel; // how many bits is used to store a pixel
	uint8_t		bytes_per_pixel;
	uint64_t	bytes; // the number of bytes used for this image
	int			size_line; // how many pixels in 1 line horizontally across
	int			endian;
	t_vec2i		pos; // where this image should be placed on the screen
}	t_image;

typedef struct s_game	t_game;

t_image		create_image(void *mlx, int width, int height);
void		destroy_image(void *mlx, t_image *img);
void		load_image(t_game *game, t_image *img, const char *filename);
uint32_t	*get_pixel_addr(const t_image *img, int x, int y);
bool		draw_pixel(t_image *img, int x, int y, t_colour colour);
void		draw_line_in_image(t_image *img, t_vec2i start,
				t_vec2i end, t_colour colour);
void		put_image(t_game *game, t_image *img, t_vec2i *point);
void		fill_image(t_image *img, const t_colour color);
void		draw_box(t_image *img, const t_vec2i centre,
				const int half_dimension, const t_colour colour);
void		draw_border(t_image *img, const int thiccness,
				const t_colour colour);

#endif
