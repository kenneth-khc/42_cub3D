/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:43:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/11 20:55:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdbool.h>
# include "Player.h"
# include "Vector.h"
# include "Map.h"

#ifndef SCREEN_WIDTH
# define SCREEN_WIDTH 1000
#endif
#ifndef SCREEN_HEIGHT
# define SCREEN_HEIGHT 1000
#endif

/* A single ray being casted */

typedef struct s_ray
{
	int				id; // the index of the current ray within the array
	t_vector_int	map_pos;
	t_vector_double	world_pos;
	double			angle_in_radians;
	t_vector_double	direction; // normalized direction by cos/sine'ing angles
	// the point where the ray intersects an X boundary for the first time
	t_vector_double	horizontal_intersect;
	// the point where the ray intersects an Y boundary for the first time
	t_vector_double	vertical_intersect;
	double			x_step; // how much worldX to step by when it goes 1 mapY
	double			y_step; // how much worldY to step by when it goes 1 mapX
	/*bool			hit_wall;*/
	double			distance_to_h_wall;
	double			distance_to_v_wall;
	double			distance_travelled; // total distance travelled until a wall is hit
}	t_ray;

// temp for debugging whether dda is finding vertical or horizontal intercept
typedef enum e_dda_axis
{
	FIND_HORIZONTAL,
	FIND_VERTICAL
}	t_dda_axis;

typedef struct s_raycaster
{
	bool		init;
	int			number_of_rays;
	t_ray		rays[SCREEN_WIDTH];
	double		angle_increment;
	double		leftmost_ray_angle;
	double		rightmost_ray_angle;
}	t_raycaster;

typedef struct s_game	t_game;

void			init_raycaster(t_raycaster *raycaster, t_player *player, t_game *game);
void			raycast(t_raycaster *raycaster, t_player *player, t_game *game);
void			find_first_horizontal_intersect(t_ray *ray, t_game *game);
void			find_first_vertical_intersect(t_ray *ray, t_game *game);
t_vector_double	dda(t_ray *ray, t_dda_axis find, t_vector_double ray_start_pos, t_map *map);

double			degrees_to_radians(double degrees);
double			radians_to_degrees(double radians);
t_vector_int	world_to_map_pos(t_vector_double *world_pos);

#endif
