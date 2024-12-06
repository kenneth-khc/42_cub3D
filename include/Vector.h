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
}	t_vector_double;

typedef struct s_vector_int
{
	int	x;
	int	y;
}	t_vector_int;

typedef struct s_dimensions
{
	int	width;
	int	height;
}	t_dimensions;

t_vector_double	copy_vector_double(t_vector_double *src);
t_vector_int	copy_vector_int(t_vector_int *src);
t_vector_int	v2d_to_v2i(t_vector_double d);
bool			compare_vectors(t_vector_int *v1, t_vector_int *v2);

#endif
