/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:24:35 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/23 23:00:14 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colours.h"
#include "Image.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "Utils.h"

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

/* Parse a string of the format "[0-255],[0-255],[0-255]" into its RGB
 * components and create a colour from that, exiting when an error is
 * encountered */
t_colour	rgb_string_to_colour(const char *rgb_string)
{
	size_t	size;
	char	**components;
	int		r;
	int		g;
	int		b;

	if (count_occurences(',', rgb_string) != 2)
		error("Invalid RGB format\n");
	components = ft_split(rgb_string, ',');
	if (components == NULL)
		error("Memory allocation failed at ft_split()\n");
	size = 0;
	while (components[size])
		size++;
	if (size != 3)
		error("Invalid RGB colour\n");
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		error("Invalid RGB value\n");
	}
	free_2d_array(components);
	return (create_colour(0, r, g, b));
}
