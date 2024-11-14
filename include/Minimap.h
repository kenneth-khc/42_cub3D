/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:34:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/14 18:14:54 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdbool.h>
# include "Map.h"
# include "Image.h"
#include "Vector.h"

# ifndef MINIMAP_SCALE
#  define MINIMAP_SCALE 0.2
# endif

/* A camera overlooking the 2D map */
typedef struct s_camera
{
	t_vector_double	centre;
	t_vector_double offset;
	double			half_dimension; // how much from the centre to view until
	t_vector_double	top_left;
	t_vector_double	top_right;
	t_vector_double	bot_left;
	t_vector_double	bot_right;

}	t_camera;

typedef struct s_minimap
{
	bool			display; // should the minimap be displayed, default to true
	t_image			img;
	int				width;
	int				height;
	t_camera		camera;


}	t_minimap;

#endif
