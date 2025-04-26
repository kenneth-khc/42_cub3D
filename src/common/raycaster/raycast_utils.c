/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:46:54 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/14 00:59:31 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycaster.h"
#include <math.h>

static void	calculate_ray_x_step(t_ray *ray);
static void	calculate_ray_y_step(t_ray *ray);

/* Initialize parameters for DDA (digital differential analyzer)
 * Depending on the direction of the ray, we step through x and y positive or
 * negatively
 * dx dy are the distances travelled when moving from one unit to the next
 * the distance to the first intersection is calculated by taking the difference
 * between the truncated map position and the fractional map position, giving
 * us a portion within the cell, then multiplied by the dx or dy to scale it
 * down */

// INFO: The following are equivalent.
// Do a bunch of derivations to find out why they're equivalent.
// ray->dx = fabs(1 / ray->dir.x);
// ray->dy = fabs(1 / ray->dir.y);
// ---------------------------------------------------------------------------
/* ray->dx = sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));*/
/* ray->dy = sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));*/
void	init_dda(t_ray *ray)
{
	ray->hit = false;
	ray->dx = fabs(1 / ray->dir.x);
	ray->dy = fabs(1 / ray->dir.y);
	calculate_ray_x_step(ray);
	calculate_ray_y_step(ray);
}

void	calculate_ray_x_step(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->x_step = -1;
		ray->x_axis_distance = (ray->tile_offset.x - ray->tile_index.x)
			* ray->dx;
	}
	else
	{
		ray->x_step = +1;
		ray->x_axis_distance = (ray->tile_index.x + 1 - ray->tile_offset.x)
			* ray->dx;
	}
}

void	calculate_ray_y_step(t_ray *ray)
{
	if (ray->dir.y < 0)
	{
		ray->y_step = -1;
		ray->y_axis_distance = (ray->tile_offset.y - ray->tile_index.y)
			* ray->dy;
	}
	else
	{
		ray->y_step = +1;
		ray->y_axis_distance = (ray->tile_index.y + 1 - ray->tile_offset.y)
			* ray->dy;
	}
}

// HACK: fisheye correction. implement a proper projection plane so this
// isn't necessary
/*ray->distance_travelled*/
/*	= ray->distance_travelled*/
/*		* cos(player->angle - ray->angle);*/
void	get_distance(t_ray *ray, t_player *player)
{
	if (ray->hit_side == HIT_EAST || ray->hit_side == HIT_WEST)
	{
		ray->distance_from_player = ray->x_axis_distance - ray->dx;
	}
	else if (ray->hit_side == HIT_NORTH || ray->hit_side == HIT_SOUTH)
	{
		ray->distance_from_player = ray->y_axis_distance - ray->dy;
	}
	ray->distance_from_camera = ray->distance_from_player
		* cos(player->angle - ray->angle);
}

void	check_wall_side_hit(t_ray *ray)
{
	if (ray->hit_side == HIT_HORIZONTAL)
	{
		if (ray->dir.y > 0)
			ray->hit_side = HIT_SOUTH;
		else
			ray->hit_side = HIT_NORTH;
	}
	else if (ray->hit_side == HIT_VERTICAL)
	{
		if (ray->dir.x > 0)
			ray->hit_side = HIT_EAST;
		else
			ray->hit_side = HIT_WEST;
	}
}
