/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:04:43 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/22 03:39:24 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "Vector.h"

double	radians(double degrees);
double	degrees(double radians);
void	error(const char *err_msg);
t_vec2i	vec2i(t_vec2d dv);
int		count_occurences(char c, const char *string);
void	free_2d_array(char **arr);

#endif
