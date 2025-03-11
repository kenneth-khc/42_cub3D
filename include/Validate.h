/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:30:27 by kytan             #+#    #+#             */
/*   Updated: 2025/03/11 20:37:48 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FULFILLED 63

void	validate_file_data(t_parse *parser, t_game *game);




int		id_idx(char *id_token, t_game *game);
int		empty_line(char *s);