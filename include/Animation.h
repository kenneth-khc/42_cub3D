/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:57:35 by kecheong          #+#    #+#             */
/*   Updated: 2025/01/03 17:13:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "Image.h"

typedef struct s_animation
{
	t_image	frames[2];
	int		frame_count;
	int		frame_index;
	int		ticks;
	int		ticks_to_advance;
}	t_animation;

t_animation	animation(t_game *game,
		const char *img1_filename, const char *img2_filename);
t_image	*get_current_frame(t_animation *animation);

#endif
