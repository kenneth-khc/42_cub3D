/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:31:28 by kecheong          #+#    #+#             */
/*   Updated: 2025/01/03 17:15:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "Vector.h"
# include "Raycaster.h"
# include "Map.h"
# include "Image.h"
# include "Animation.h"

typedef struct s_renderer
{
	t_dimensions	screen;
	// the center line where the ceiling and floor collides
	int				midpoint;
	// which column of the screen it is now rendering
	int				current_x;
	t_vec2i			draw_start; // the position to start drawing at
	t_vec2i			draw_end; // the position to end drawing at
	double			line_height; // the height of the current line to draw
	t_image			*img; // the image to render onto
	t_animation		animations[4]; // wall textures that are animated
	t_image			textures[4]; // which textures to use for the curr frame
	t_animation		north_anim;
	t_animation		south_anim;
	t_animation		west_anim;
	t_animation		east_anim;
	t_image			debug_texture; // TODO: remove this
	t_image			*curr_texture;
	t_vec2d			texture_pos;
}	t_renderer;

typedef struct s_game	t_game;

void	render(t_game *game, t_renderer *renderer, t_raycaster *raycaster);
void	init_world2D(t_game *game, t_map *map);
void	init_world_3d(t_game *game);
void	clear_walls(t_renderer *renderer, t_image *world, t_dimensions screen,
			t_colour ceiling, t_colour floor);
void	render_wall_slice(t_renderer *renderer, t_ray *ray);
void	calculate_draw_pos(t_renderer *renderer);
double	calculate_wall_hitpoint(t_ray *ray);
int		calculate_texture_column(t_image *texture, double wall_hit_x,
			t_ray *ray);
void	reset_draw_line(t_renderer *renderer);
void	decide_current_texture(t_renderer *renderer, t_ray *ray);

#endif
