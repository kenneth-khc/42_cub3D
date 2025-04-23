/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 02:31:10 by kecheong          #+#    #+#             */
/*   Updated: 2025/04/24 02:36:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.h"
#include "libft.h"
#include <stdlib.h>

/* For animations split into individual frames, we assume their filename
 * (before the .xpm file extension) is suffixed with a number counting up
 * from 0. We use access() to count up and check how many frames exist, 
 * before allocating an array of Images and loading each frame into it */
int	count_animation_frames(const char *filename)
{
	int		count;
	int		num;
	char	*num_suffix;
	char	*frame_filename;

	num = 0;
	count = 0;
	num_suffix = ft_itoa(num);
	frame_filename = ft_strjoin_multiple(3, filename, num_suffix, ".xpm");
	while (access(frame_filename, F_OK | R_OK) == 0)
	{
		count++;
		num++;
		free(num_suffix);
		free(frame_filename);
		num_suffix = ft_itoa(num);
		frame_filename = ft_strjoin_multiple(3, filename, num_suffix, ".xpm");
	}
	free(num_suffix);
	free(frame_filename);
	return (count);
}

/* Extracts the filename portion of the filepath, discarding the .xpm suffix */
char	*extract_xpm_filename(const char *filepath)
{
	char	*filename;

	if (!ft_str_endswith(filepath, ".xpm"))
	{
		error("Texture does not end with .xpm\n");
	}
	filename = ft_substr(filepath, 0, ft_strlen(filepath) - 4);
	return (filename);
}
