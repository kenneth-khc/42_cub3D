/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:31:28 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/02 10:01:40 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "Vector.h"
# include "Raycaster.h"
# include "Map.h"

typedef struct s_renderer
{
	t_dimensions	screen;
	int				current_x; // which column of the screen it is now rendering
	t_vector_int	draw_start; // the position to start drawing at
	t_vector_int	draw_end; // the position to end drawing at
	double			line_height; // the height of the current line to draw
	t_image			*img; // the image to render onto
	t_image			textures[4]; // array of wall textures to use
	t_image			*current_texture;
}	t_renderer;

typedef struct s_game	t_game;

void	render(t_renderer *renderer, t_game *game, t_raycaster *raycaster);
void	init_world2D(t_game *game, t_map *map);
void	init_world_3d(t_game *game);
void	draw_vertical(t_image *img, t_vector_int start, t_vector_int end,
			t_colour colour);
void	clear_walls(t_image *world, t_dimensions screen,
			t_colour ceiling, t_colour floor);
void	draw_wall(t_image *world, int screen_x, double wall_height,
			t_game *game, t_colour colour);
void	render_wall_slice(t_renderer *renderer, t_game *game, t_ray *ray);
void	draw_vertical(t_image *img, t_vector_int start, t_vector_int end,
			t_colour colour);
void	calculate_draw_pos(t_renderer *renderer);
double	calculate_wall_hitpoint(t_ray *ray);
int		calculate_texture_column(t_image *texture, double wall_hit_x,
			t_ray *ray);

#endif
