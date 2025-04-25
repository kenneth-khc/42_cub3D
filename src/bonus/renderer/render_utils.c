/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:02:15 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 02:29:02 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animation.h"
#include "Image.h"
#include "Vector.h"
#include "Renderer.h"

/* Clear away walls on the screen by redrawing the ceiling and floor */
void	clear_walls(t_renderer *renderer)
{
	int	y;
	int	x;

	x = 0;
	while (x < renderer->screen.width)
	{
		y = 0;
		while (y < renderer->midpoint)
		{
			draw_pixel(renderer->img, x, y, renderer->ceiling);
			y++;
		}
		while (y < renderer->screen.height)
		{
			draw_pixel(renderer->img, x, y, renderer->floor);
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
		= (int)-renderer->line_height / 2 + (int)midpoint;
	renderer->draw_end.x = renderer->current_x;
	renderer->draw_end.y = (int)renderer->line_height / 2 + (int)midpoint;
	if (renderer->draw_end.y > renderer->screen.height)
	{
		renderer->draw_end.y = renderer->screen.height;
	}
}

void	reset_draw_line(t_renderer *renderer)
{
	renderer->draw_start.x = 0;
	renderer->draw_start.y = 0;
	renderer->draw_end.x = 0;
	renderer->draw_end.y = 0;
	renderer->line_height = 0;
	renderer->texture_pos.x = 0;
	renderer->texture_pos.y = 0;
}

void	decide_current_texture(t_renderer *renderer, t_ray *ray)
{
	if (ray->hit_door)
	{
		renderer->curr_texture = &renderer->door_animation.frames[0];
	}
	else if (ray->hit_side == HIT_SOUTH)
	{
		renderer->curr_texture = &renderer->wall_textures[SOUTH];
	}
	else if (ray->hit_side == HIT_NORTH)
	{
		renderer->curr_texture = &renderer->wall_textures[NORTH];
	}
	else if (ray->hit_side == HIT_EAST)
	{
		renderer->curr_texture = &renderer->wall_textures[EAST];
	}
	else if (ray->hit_side == HIT_WEST)
	{
		renderer->curr_texture = &renderer->wall_textures[WEST];
	}
}
