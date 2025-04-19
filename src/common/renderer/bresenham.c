/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:38:12 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 02:54:07 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <mlx.h>
#include "Image.h"
#include "Vector.h"

static void	draw_low(t_image *img, t_vec2i start,
		t_vec2i end, t_colour colour)
{
	int	dx;
	int	dy;
	int	dir;
	int	decision;

	dx = end.x - start.x;
	dy = end.y - start.y;
	dir = 1;
	if (dy < 0)
	{
		dir = -1;
		dy = -dy;
	}
	decision = (2 * dy) - dx;
	while (start.x < end.x)
	{
		draw_pixel(img, start.x, start.y, colour);
		if (decision > 0)
		{
			start.y += dir;
			decision = decision + (2 * (dy - dx));
		}
		else
		{
			decision = decision + (2 * dy);
		}
		start.x++;
	}
}

static void	draw_high(t_image *img, t_vec2i start,
		t_vec2i end, t_colour colour)
{
	int	dx;
	int	dy;
	int	dir;
	int	decision;

	dx = end.x - start.x;
	dy = end.y - start.y;
	dir = 1;
	if (dx < 0)
	{
		dir = -1;
		dx = -dx;
	}
	decision = (2 * dx) - dy;
	while (start.y < end.y)
	{
		draw_pixel(img, start.x, start.y, colour);
		if (decision > 0)
		{
			start.x += dir;
			decision = decision + (2 * (dx - dy));
		}
		else
		{
			decision = decision + (2 * dx);
		}
		start.y++;
	}
}

void	draw_line_in_image(t_image *img, t_vec2i start,
							t_vec2i end, t_colour colour)
{
	const int	x0 = start.x;
	const int	y0 = start.y;
	const int	x1 = end.x;
	const int	y1 = end.y;

	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
		{
			draw_low(img, end, start, colour);
		}
		else
		{
			draw_low(img, start, end, colour);
		}
	}
	else
	{
		if (y0 > y1)
		{
			draw_high(img, end, start, colour);
		}
		else
		{
			draw_high(img, start, end, colour);
		}
	}
}
