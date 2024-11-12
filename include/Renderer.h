/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:31:28 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/30 22:34:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

#include "Game.h"

void	render(t_game *game, t_raycaster *raycaster);
void	init_world2D(t_game *game, t_map *map);
void	init_world3D(t_game *game);
void	draw_vertical(t_image *img, t_vector_int start, t_vector_int end,
				t_colour colour);
void	clear_walls(t_game *game);
void	draw_wall(t_image *world, int screen_x, double wall_height, t_game *game);
void	draw_vertical(t_image *img, t_vector_int start, t_vector_int end,
				t_colour colour);

#endif
