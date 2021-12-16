/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_part_with_analyzer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:21:46 by enena             #+#    #+#             */
/*   Updated: 2021/12/16 22:35:51 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

/*
** Function reading and analyze with analyzer function
*/

t_bool	read_part(void *part, const int fd,
									char **line, const t_analyzer analyzer)
{
	int			retgnl;
	t_bool		lastline_drop;

	lastline_drop = false;
	retgnl = ft_get_next_line(fd, line);
	if (!((retgnl > 0)))
		lastline_drop = (!(lastline_drop) && (retgnl == 0));
	while ((retgnl > 0) || (lastline_drop))
	{
		if (!(analyzer(part, *line, &lastline_drop)))
		{
			if (!(lastline_drop))
				*line = ft_sec_free(*line);
			return (lastline_drop);
		}
		*line = ft_sec_free(*line);
		retgnl = ft_get_next_line(fd, line);
		if (!((retgnl > 0)))
			lastline_drop = (!(lastline_drop) && (retgnl == 0));
	}
	*line = ft_sec_free(*line);
	if (retgnl)
		return (error_handler(err_read_fail));
	return (true);
}

/*
** Analyzer for setting line
*/

t_bool	analyze_setting(void *psettings, const char *line, t_bool *ll_dr)
{
	char			**tab_line;
	ssize_t			i;
	t_bool			retset;
	t_setting_link	*l;

	l = ((t_settings *)psettings)->link;
	if (*ll_dr)
		return (*ll_dr = error_handler(err_missing_map));
	if (!(*line))
		return (true);
	tab_line = ft_split(line, ' ');
	if (!(tab_line))
		return (error_handler(err_alloc_fail));
	i = -1;
	while (++i < CNT_SETTING)
	{
		if (!(ft_strncmp(l[i].idntf, *tab_line, SIZE_IDNTF_SETTING)))
		{
			retset = l[i].set(&l[i], tab_line);
			tab_line = ft_free_tab(tab_line);
			return (retset);
		}
	}
	tab_line = ft_free_tab(tab_line);
	return (!(*ll_dr = true));
}

/*
** Analyzer for reading in list map
*/

t_bool	analyze_map(void *pmap, const char *line, t_bool *ll_dr)
{
	t_map	*map;
	t_bool	only_fill;
	t_error	took_er;

	if (!(*line))
	{
		if (*ll_dr)
			return (true);
		else
			return (*ll_dr = error_handler(err_empty_line_in_map));
	}
	map = pmap;
	only_fill = true;
	if (*ll_dr)
		took_er = err_last_line_map;
	else
		took_er = err_middle_line_map;
	if (!(check_junk(line, took_er, &map->player_set, &only_fill)))
		return (*ll_dr = false);
	if (!only_fill)
		if (!(add_map_line_to_list(map->tmp, line)))
			return (*ll_dr = false);
	return (true);
}
