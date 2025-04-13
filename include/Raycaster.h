/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:43:08 by kecheong          #+#    #+#             */
/*   Updated: 2024/12/02 10:00:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdbool.h>
# include "Player.h"
# include "Vector.h"
# include "Map.h"

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1000
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1000
# endif

typedef enum e_hit_side
{
	HIT_HORIZONTAL,
	HIT_VERTICAL,
	HIT_NORTH,
	HIT_SOUTH,
	HIT_WEST,
	HIT_EAST
}	t_hit_side;

/* A single ray being casted */
typedef struct s_ray
{
	int		id; // the index of the current ray within the array
	t_vec2i	tile_index;
	t_vec2d	tile_offset;
	t_vec2d	world_pos;
	double	angle_in_radians;
	t_vec2d	dir; // normalized direction by cos/sine'ing angles
	double	x_step; // how much worldX to step by when it goes 1 mapY
	double	y_step; // how much worldY to step by when it goes 1 mapX
	bool	hit;
	uint8_t	hit_side;

	double	dx; // distance it travels when going from 1 X to the next
	double	dy; // distance it travels when going from 1 Y to the next
	double	x_axis_distance; // distance to the first initial X
	double	y_axis_distance; // distance to the first initial Y
	double	distance_from_player; // total dist travelled till a hit
	double	distance_from_camera; // corrected distance for rendering
}	t_ray;

typedef struct s_raycaster
{
	bool	init;
	int		ray_count;
	t_ray	rays[SCREEN_WIDTH];
	double	angle_increment;
	double	leftmost_ray_angle;
	double	rightmost_ray_angle;

	// TODO: implement projection plane maybe
	t_vec2d	projection_plane;
}	t_raycaster;

typedef struct s_game	t_game;

void	init_raycaster(t_raycaster *raycaster, t_player *player, t_game *game);
void	update_raycaster(t_raycaster *raycaster, t_player *player,
			t_game *game);
void	raycast(t_raycaster *raycaster, t_player *player, t_game *game);
void	cast(t_ray *ray, t_player *player, t_map *map);
void	init_dda(t_ray *ray);
void	get_distance(t_ray *ray, t_player *player);
void	check_wall_side_hit(t_ray *ray);

double	degrees_to_radians(double degrees);
double	radians_to_degrees(double radians);

#endif
