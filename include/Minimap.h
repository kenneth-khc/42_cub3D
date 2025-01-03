/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:34:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/15 23:11:56 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdbool.h>
# include "Map.h"
# include "Image.h"
# include "Vector.h"

# ifndef MINIMAP_SCALE
#  define MINIMAP_SCALE 0.3
# endif

/* A camera overlooking the 2D map */
typedef struct s_camera
{
	t_vec2d	centre;
	t_vec2d	centred_at; // the player's position
	double			half_dimension; // how much from the centre to view until
	t_vec2d	top_left; // top left point of the box
	t_vec2d	bot_right; // bottom right point of the box
}	t_camera;

typedef struct s_minimap
{
	bool			display; // should the minimap be displayed, default to true
	t_image			img;
	int				width;
	int				height;
	t_camera		camera;
}	t_minimap;

void	update_minimap(t_minimap *minimap, t_game *game);
void	update_camera(t_camera *camera, t_minimap *minimap, t_player *player);
void	fill_minimap(t_image *img, t_camera camera, t_map *map,
			t_game *game, t_player *player);
void	draw_fov(t_image *img, t_minimap *minimap,
			t_player *player, t_game *game);

#endif
