/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_junk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 04:37:51 by enena             #+#    #+#             */
/*   Updated: 2021/12/15 20:55:08 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

/*
** My garbage check function at the line reading stage. Check string {line}.
** @The type of check is determined depending on the transmitted error
** {what_is_err} and set in {is_top_or_bottom}.
** Top or bottom line maps are checked only for fill or wall symbols.
** Otherwise, an error.
** On going from checking padding characters onwards,
** the outer flag {only_fill} is set to false.
** If the flag is false, the check continues
** for valid characters inside the map, excluding the player characters.
** The player's symbol is assumed to be the only one in the entire map.
** Therefore, even when the character is determined as a player and
** the flag {find_pl} is set, whether or not the outer flag {set_pl}
** is set to the player is considered.
** Which causes the repeated player symbol error. [err_too_much_player]
** It work in one if into while.
** Returns true if no garbage was found and
** an error handler was called with the passed error
** or too many player error if this case was handled.
*/
static t_bool	make_back(t_bool find_pl, t_error what_is_err)
{
	if (find_pl)
		return (error_handler(err_too_much_player));
	else
		return (error_handler(what_is_err));
}

t_bool	check_junk(const char *line, const t_error what_is_err,
			t_bool *set_pl, t_bool *only_fill)
{
	ssize_t			i;
	t_bool			find_pl;
	t_bool			is_top_or_bot;

	is_top_or_bot = ((what_is_err == err_first_line_map)
			|| (what_is_err == err_last_line_map));
	i = -1;
	while (line[++i])
	{
		find_pl = !!(ft_strchr(VALID_PLAYER_MAP_CHAR, line[i]));
		if (!(ft_strchr(VALID_FILL_MAP_CHAR, line[i])))
		{
			*only_fill = false;
			if (!(ft_strchr(VALID_WALL_MAP_CHAR, line[i]))
				&& (is_top_or_bot
					|| (!(ft_strchr(VALID_INSIDE_MAP_CHAR, line[i]))
						&& !((find_pl) && !(*set_pl)))))
				return (make_back(find_pl, what_is_err));
		}
		if (find_pl)
			*set_pl = true;
	}
	return (true);
}
