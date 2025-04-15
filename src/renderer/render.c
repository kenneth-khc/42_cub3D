/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:31:10 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 06:10:17 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colours.h"
#include "Game.h"
#include "Image.h"
#include "Raycaster.h"
#include "Renderer.h"
#include "Vector.h"
#include "Animation.h"
#include <mlx.h>
#include <math.h>

#ifndef TEXTURES_DIR
# define TEXTURES_DIR "../../textures"
#endif

/* Load up the textures needed by the renderer */
void	init_renderer(t_renderer *renderer,
	t_game *game, t_image *world, t_dimensions screen)
{
	renderer->img = world;
	renderer->screen = screen;
	renderer->midpoint = game->screen.height / 2;
	renderer->animations[EAST] = animation(game,
			"textures/cat_happy/cat_happy");
	renderer->animations[NORTH] = animation(game,
			"textures/cat_angry/cat_angry");
	renderer->animations[WEST] = animation(game,
			"textures/cat_omg/cat_omg");
	renderer->animations[SOUTH] = animation(game,
			"textures/cat_playing/cat_playing");
}

/* Called each frame of the game to render the world onto the screen
 * The renderer is responsible for scanning through the screen horizontally
 * and drawing each column vertically line by line */
void	render(t_game *game, t_renderer *renderer, t_raycaster *raycaster)
{
	t_ray	*ray;

	clear_walls(renderer, renderer->img, renderer->screen, game->colours.purple,
		game->colours.cyan);
	renderer->current_x = 0;
	advance_animations(renderer, renderer->animations);
	while (renderer->current_x < game->screen.width)
	{
		reset_draw_line(renderer);
		ray = &raycaster->rays[renderer->current_x];
		decide_current_texture(renderer, ray);
		renderer->line_height = game->screen.height
				/ ray->distance_from_camera;
		render_wall_slice(renderer, ray);
		renderer->current_x++;
	}
	put_image(game, renderer->img, &renderer->img->pos);
	if (game->minimap.img.instance && game->minimap.display)
	{
		put_image(game, &game->minimap.img, &game->minimap.img.pos);
	}
}

void	render_wall_slice(t_renderer *renderer, t_ray *ray)
{
	const double	wall_x = calculate_wall_hitpoint(ray);
	double			step;
	int				text_y_index;
	t_colour		colour;
	uint32_t		*pixel;

	calculate_draw_pos(renderer);
	step = renderer->curr_texture->height / renderer->line_height;
	renderer->texture_pos.x = wall_x * renderer->curr_texture->width;
	renderer->texture_pos.y = 0;
	if (renderer->draw_start.y < 0)
	{
		renderer->texture_pos.y = (step * -renderer->draw_start.y);
		renderer->draw_start.y = 0;
	}
	while (renderer->draw_start.y < renderer->draw_end.y)
	{
		text_y_index = (int)renderer->texture_pos.y;
		pixel = get_pixel_addr(renderer->curr_texture,
				renderer->texture_pos.x, text_y_index);
		colour = pixel_to_colour(pixel);
		draw_pixel(renderer->img,
			renderer->draw_start.x, renderer->draw_start.y, colour);
		renderer->texture_pos.y += step;
		renderer->draw_start.y++;
	}
}

double	calculate_wall_hitpoint(t_ray *ray)
{
	double	wall_x;

	wall_x = 1;
	if (ray->hit_side == HIT_NORTH || ray->hit_side == HIT_SOUTH)
	{
		wall_x = ray->tile_offset.x + ray->distance_from_player * ray->dir.x;
	}
	else if (ray->hit_side == HIT_EAST || ray->hit_side == HIT_WEST)
	{
		wall_x = ray->tile_offset.y + ray->distance_from_player * ray->dir.y;
	}
	return (wall_x - floor(wall_x));
}
