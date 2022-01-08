/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 03:39:26 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 18:44:11 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization_bonus.h"

/*
** Checking that all setting finded after read part with setting
** and initialization map
*/

static t_bool	check_all_settings(t_settings *settings)
{
	ssize_t		i;

	i = -1;
	settings->is_all_set = true;
	while (++i < CNT_SETTING)
		settings->is_all_set &= settings->link[i].is_set;
	if (settings->is_all_set)
		return (true);
	else
		return (error_handler(err_missing_setting));
}

t_bool	parser(t_game_master *gm, int fd, char **line)
{
	if (!(read_part(gm->sl, fd, line, &analyze_setting))
		|| !(init_map(&gm->map, line)) || !(check_all_settings(gm->sl))
		|| !(read_part(gm->map, fd, line, &analyze_map))
		|| !(convert_map_player_init(gm->map, &gm->pl)))
		return (true);
	else
		return (false);
}
