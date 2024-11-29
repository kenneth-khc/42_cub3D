/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:24:35 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/14 18:25:26 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colours.h"

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

void	set_colour_table(t_colours *table)
{
	table->red = create_colour(0x00, 0xFF, 0x00, 0x00);
	table->green = create_colour(0x00, 0x00, 0xFF, 0x00);
	table->blue = create_colour(0x00, 0x00, 0xFF, 0xFF);
	table->black = create_colour(0x00, 0x00, 0x00, 0x00);
	table->cyan = create_colour(0x00, 0x54, 0x88, 0xF7);
	table->white = create_colour(0x00, 0xFF, 0xFF, 0xFF);
	table->purple = create_colour(0x00, 0xAE, 0x71, 0xF5);
	table->grey = create_colour(0x00, 0xAC, 0xA6, 0xB3);
	table->yellow = create_colour(0x00, 0xFF, 0xFF, 0x00);
	table->violet = create_colour(0x00, 0x74, 0x43, 0xFA);
}

