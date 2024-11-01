/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:43:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 17:48:03 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdbool.h>
# include "Player.h"
# include "Vector.h"

# define SCREEN_WIDTH 1280

/* A single ray being casted */

typedef struct s_ray
{
	t_vector_int	map_pos;
	t_vector_double	world_pos;
	double			angle_in_radians;
	t_vector_double	direction; // normalized direction by cos/sine'ing angles
	// the point where the ray intersects an X boundary for the first time
	t_vector_double	first_x_intersect;
	// the point where the ray intersects an Y boundary for the first time
	t_vector_double	first_y_intersect;
	double			x_step; // how much worldX to step by when it goes 1 mapY
	double			y_step; // how much worldY to step by when it goes 1 mapX
	bool			hit_wall;
	t_vector_double	horizontal_wall_pos; // the world_pos of a horizontal wall hit
	t_vector_double	vertical_wall_pos; // the world_pos of a vertical wall hit
}	t_ray;

typedef struct s_raycaster
{
	int			number_of_rays;
	t_ray		rays[SCREEN_WIDTH];
	double		angle_increment;
	double		leftmost_ray_angle;
	double		rightmost_ray_angle;
}	t_raycaster;

typedef struct s_game	t_game;

void	raycast(t_raycaster *raycaster, t_game *game, t_player *player);
void	init_raycaster(t_raycaster *raycaster, t_player *player, t_game *game);
void	find_first_x_intersect(t_ray *ray, t_game *game);

double	degrees_to_radians(double degrees);
double	radians_to_degrees(double radians);
t_vector_int	world_to_map_pos(t_vector_double *world_pos);

#endif
