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
void	clear_walls(t_renderer* renderer, t_image *world, t_dimensions screen,
	t_colour ceiling, t_colour floor)
{
	int	y;
	int	x;

	x = 0;
	while (x < screen.width)
	{
		y = 0;
		while (y < renderer->midpoint)
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

/* Calculate where on the screen to draw the line based on its height */
void	calculate_draw_pos(t_renderer *renderer)
{
	double	midpoint;

	midpoint = renderer->midpoint;
	renderer->draw_start.x = renderer->current_x;
	renderer->draw_start.y
		= (int)-renderer->line_height / 2 + midpoint;
	renderer->draw_end.x = renderer->current_x;
	renderer->draw_end.y = (int)renderer->line_height / 2 + midpoint;
	if (renderer->draw_end.y > renderer->screen.height)
	{
		renderer->draw_end.y = renderer->screen.height;
	}
}

/*void	draw_wall(t_image *world, int screen_x, double wall_height, t_game *game, t_colour colour)*/
/*{*/
/*	t_vector_int	draw_start;*/
/*	draw_start.y = (int)-wall_height / 2 + game->screen.height / 2;*/
/*	draw_start.x = screen_x;*/
/*	if (draw_start.y < 0)*/
/*	{*/
/*		draw_start.y = 0;*/
/*	}*/
/*	t_vector_int	draw_end;*/
/*	draw_end.y = (int)wall_height / 2 + game->screen.height / 2;*/
/*	draw_end.x = screen_x;*/
/*	if (draw_end.y > game->screen.height)*/
/*	{*/
/*		draw_end.y = game->screen.height - 1;*/
/*	}*/
/*	draw_vertical(world, draw_start, draw_end, colour);*/
/*}*/
/**/
