/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:28:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/11/01 15:22:03 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdbool.h>

typedef struct s_vector_double
{
	double	x;
	double	y;
}	t_vec2d;

typedef struct s_vector_int
{
	int	x;
	int	y;
}	t_vec2i;

typedef struct s_dimensions
{
	int	width;
	int	height;
}	t_dimensions;

t_vec2d	copy_vector_double(t_vec2d *src);
t_vec2i	copy_vector_int(t_vec2i *src);
t_vec2i	v2d_to_v2i(t_vec2d d);
bool			compare_vectors(t_vec2i *v1, t_vec2i *v2);

#endif
