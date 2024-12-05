/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:31:10 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/05 23:17:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "Game.h"
#include "Image.h"
#include "Raycaster.h"
#include "Renderer.h"
#include "Vector.h"
#include <assert.h>

#ifndef TEXTURES_DIR
# define TEXTURES_DIR "../../textures"
#endif

void	init_renderer(t_renderer *renderer,
	t_game *game, t_image *world, t_dimensions screen)
{
	renderer->img = world;
	renderer->screen = screen;
	load_image(game, &renderer->textures[EAST], "textures/greystone.xpm");
	load_image(game, &renderer->textures[NORTH], "textures/eagle.xpm");
	load_image(game, &renderer->textures[WEST], "textures/colorstone.xpm");
	load_image(game, &renderer->textures[SOUTH], "textures/bluestone.xpm");
}

void	update_renderer(t_renderer *renderer)
{
	renderer->draw_start.x = 0;
	renderer->draw_start.y = 0;
	renderer->draw_end.x = 0;
	renderer->draw_end.y = 0;
	renderer->line_height = 0;
}

void	render(t_renderer *renderer, t_game *game, t_raycaster *raycaster)
{
	t_ray	*ray;

	clear_walls(renderer->img, renderer->screen,
		game->colours.purple, game->colours.cyan);
	renderer->current_x = 0;
	while (renderer->current_x < game->screen.width)
	{
		update_renderer(renderer);
		ray = &raycaster->rays[renderer->current_x];
		renderer->current_texture = &renderer->textures[EAST];
		renderer->line_height
			= (int)game->screen_height * 2 / ray->distance_travelled * 0.5;
		render_wall_slice(renderer, game, ray);
		renderer->current_x++;
	}
	put_image(game, renderer->img, &renderer->img->pos);
	if (game->minimap.img.instance && game->minimap.display)
	{
		put_image(game, &game->minimap.img, &game->minimap.img.pos);
	}
}

void	render_wall_slice(t_renderer *renderer, t_game *game, t_ray *ray)
{
	double	wall_x; // where exactly the wall was hit
	t_image	*t = renderer->current_texture;
	int		texture_x;
	double	step = t->height / renderer->line_height;
	double	texture_y = 0;
	int		texture_y_index;
	t_colour	colour;

	(void)game;
	calculate_draw_pos(renderer);
	wall_x = calculate_wall_hitpoint(ray);
	texture_x = calculate_texture_column(t, wall_x, ray);
	while (renderer->draw_start.y < renderer->draw_end.y)
	{
		texture_y_index = (int)texture_y;
		colour = pixel_to_colour(get_pixel_addr(t, texture_x, texture_y_index));
		draw_pixel(renderer->img,
			renderer->draw_start.x, renderer->draw_start.y, colour);
		renderer->draw_start.y++;
		texture_y += step;
	}
}

int	calculate_texture_column(t_image *texture, double wall_hit_x, t_ray *ray)
{
	int	texture_x;

	texture_x = wall_hit_x * texture->width;
	if (ray->side == HIT_HORIZONTAL && ray->dir.x < 0)
	{
		texture_x = texture->width - texture_x - 1;
	}
	if (ray->side == HIT_VERTICAL && ray->dir.y > 0)
	{
		texture_x = texture->width - texture_x - 1;
	}
	return (texture_x);
}

double	calculate_wall_hitpoint(t_ray *ray)
{
	double	wall_x;

	if (ray->side == HIT_HORIZONTAL)
	{
		wall_x = ray->frac_map_pos.y + ray->distance_travelled * ray->dir.y;
	}
	else
	{
		wall_x = ray->frac_map_pos.x + ray->distance_travelled * ray->dir.x;
	}
	return (wall_x -= floor(wall_x));
}
