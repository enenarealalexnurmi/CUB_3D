/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:24:57 by enena             #+#    #+#             */
/*   Updated: 2021/12/15 21:13:25 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

static void	map_setup(t_map *map)
{
	map->player_set = false;
	map->yx = NULL;
	map->mx_y = 0;
	map->mx_x = 0;
	map->count_sprite = 0;
	map->tmp->bgn_ind = 0;
	map->tmp->end_ind = 0;
	map->tmp->len = 0;
	map->tmp->listsize = 0;
	map->tmp->list = NULL;
}

static t_bool	alloc_map(t_map **map, char **line)
{
	*map = malloc(sizeof(t_map));
	if (!(*map))
	{
		*line = ft_sec_free(*line);
		return (error_handler(err_alloc_fail));
	}
	(*map)->tmp = malloc(sizeof(t_map_list));
	if (!((*map)->tmp))
	{
		*line = ft_sec_free(*line);
		return (error_handler(err_alloc_fail));
	}
	return (true);
}

t_bool	init_map(t_map **map, char **line)
{
	t_bool	only_fill;

	if (!(alloc_map(map, line)))
		return (false);
	map_setup(*map);
	only_fill = true;
	if (!(check_junk(*line, err_first_line_map,
				&(*map)->player_set, &only_fill)))
	{
		*line = ft_sec_free(*line);
		return (false);
	}
	if (!only_fill)
	{
		if (!(add_map_line_to_list((*map)->tmp, *line)))
		{
			*line = ft_sec_free(*line);
			return (false);
		}
	}
	*line = ft_sec_free(*line);
	return (true);
}

static void	took_param(const char *base, t_map_list *ml)
{
	const char	*bgn;
	const char	*end;
	size_t		calc_bgn_ind;
	size_t		calc_end_ind;

	bgn = base;
	end = base + ft_strlen(base) - 1;
	while (ft_strchr(VALID_FILL_MAP_CHAR, *bgn))
		++bgn;
	while (ft_strchr(VALID_FILL_MAP_CHAR, *end))
		--end;
	calc_bgn_ind = bgn - base;
	calc_end_ind = end - base;
	if (!(ml->listsize) || ((ml->listsize) && (ml->bgn_ind >= calc_bgn_ind)))
		ml->bgn_ind = calc_bgn_ind;
	if (!(ml->listsize) || ((ml->listsize) && (ml->bgn_ind >= calc_bgn_ind)))
		ml->end_ind = calc_end_ind;
	ml->len = ml->end_ind - ml->bgn_ind + 1;
}

t_bool	add_map_line_to_list(t_map_list *ml, const char *map_line)
{
	char	*content;
	t_list	*new;

	content = ft_strdup(map_line);
	if (!(content))
		return (error_handler(err_alloc_fail));
	new = ft_lstnew(content);
	if (!(new))
	{
		content = ft_sec_free(content);
		return (error_handler(err_alloc_fail));
	}
	took_param(content, ml);
	++(ml->listsize);
	ft_lstadd_back(&ml->list, new);
	return (true);
}
