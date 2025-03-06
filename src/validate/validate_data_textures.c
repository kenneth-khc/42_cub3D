/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:11:10 by kytan             #+#    #+#             */
/*   Updated: 2025/03/07 05:15:04 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @return If `token` is a valid identifier ie. "NO", "SO",
 * "EA" & "WE", returns TRUE(1). Else, return FALSE(0).
 */
int	valid_identifier(char *token)
{
	if (!token)
		return (0);
	else if (!ft_strcmp(token, "NO") || !ft_strcmp(token, "SO"))
		return (1);
	else if (!ft_strcmp(token, "EA") || !ft_strcmp(token, "WE"))
		return (1);
	else if (!ft_strcmp(token, "F") || !ft_strcmp(token, "C"))
		return (1);
	return (0);
}