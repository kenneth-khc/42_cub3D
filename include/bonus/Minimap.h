/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:34:27 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/21 03:28:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdbool.h>
# include "Image.h"
# include "Vector.h"

/* A camera overlooking the 2D map */
typedef struct s_camera
{
	t_vec2d	centre;
	t_vec2d	centred_at; // the player's position
	double	half_dimension; // how much from the centre to view until
	t_vec2d	top_left; // top left point of the box
	t_vec2d	bot_right; // bottom right point of the box
}	t_camera;

typedef struct s_minimap
{
	bool		display; // should the minimap be displayed, default to true
	t_image		img;
	t_camera	camera;
	t_colour	border_colour;
	int			border_thickness;
	t_colour	background_colour;
	t_colour	wall_colour;
	t_colour	player_indicator_colour;
	int			player_box_half_dimension;
	t_colour	direction_indicator_colour;
}	t_minimap;

t_minimap	init_minimap(t_game *game);
void		update_minimap(t_minimap *minimap, t_vec2d *pos, t_game *game);

#endif
