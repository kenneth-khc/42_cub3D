/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:15:54 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 23:09:13 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

# include <stdint.h>

/* 32 bits to store a RGBA value, access each component through the struct */
typedef union u_colour
{
	uint32_t	value;
	struct
	{
		/* little endian */
		uint8_t	blue;
		uint8_t	green;
		uint8_t	red;
		uint8_t	alpha;
	}	s_component;
}	t_colour;

/* Some common colours used throughout debugging */
typedef struct s_colours
{
	t_colour	red;
	t_colour	green;
	t_colour	blue;
	t_colour	black;
	t_colour	white;
	t_colour	cyan;
	t_colour	purple;
	t_colour	grey;
	t_colour	yellow;
	t_colour	violet;
}	t_colours;

typedef struct s_image	t_image;

t_colours	init_colours(void);
t_colour	create_colour(uint8_t alpha, uint8_t red, uint8_t green,
				uint8_t blue);
t_colour	rgb_string_to_colour(const char *rgb_string);
t_colour	pixel_to_colour(uint32_t *pixel);
t_colour	get_pixel_addr_to_colour(const t_image *img, int x, int y);

#endif
