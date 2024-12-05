/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:02:15 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/05 23:13:23 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Image.h"
#include "Colours.h"
#include "Vector.h"
#include "Renderer.h"

/* Clear away walls on the screen by redrawing the ceiling and floor */
void	clear_walls(t_image *world, t_dimensions screen,
	t_colour ceiling, t_colour floor)
{
	int	y;
	int	x;

	x = 0;
	while (x < screen.width)
	{
		y = 0;
		while (y < screen.height / 2)
		{
			draw_pixel(world, x, y, ceiling);
			y++;
		}
		while (y < screen.height)
		{
			draw_pixel(world, x, y, floor);
			y++;
		}
		x++;
	}
}

void	draw_wall(t_image *world, int screen_x, double wall_height, t_game *game, t_colour colour)
{
	t_vector_int	draw_start;
	draw_start.y = (int)-wall_height / 2 + game->screen_height / 2;
	draw_start.x = screen_x;
	if (draw_start.y < 0)
	{
		draw_start.y = 0;
	}
	t_vector_int	draw_end;
	draw_end.y = (int)wall_height / 2 + game->screen_height / 2;
	draw_end.x = screen_x;
	if (draw_end.y > game->screen_height)
	{
		draw_end.y = game->screen_height - 1;
	}
	draw_vertical(world, draw_start, draw_end, colour);
}

/* Calculate where on the screen to draw the line based on its height */
void	calculate_draw_pos(t_renderer *r)
{
	r->draw_start.x = r->current_x;
	r->draw_start.y
		= (int)-r->line_height / 2 + r->screen.height / 2;
	if (r->draw_start.y < 0)
	{
		r->draw_start.y = 0;
	}
	r->draw_end.x = r->current_x;
	r->draw_end.y = (int)r->line_height / 2 + r->screen.height / 2;
	if (r->draw_end.y > r->screen.height)
	{
		r->draw_end.y = r->screen.height - 1;
	}
}
