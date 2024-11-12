/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:37:20 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/12 13:54:07 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.h>
#include "Image.h"

void	draw_vertical(t_image *img, t_vector_int start, t_vector_int end,
				t_colour colour)
{
	const int y = start.y;

	while (start.x != end.x)
	{
		draw_pixel(img, start.x, y, colour);
		start.x++;
	}
}
