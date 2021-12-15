/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   naming_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:14:55 by enena             #+#    #+#             */
/*   Updated: 2021/11/28 05:20:01 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "naming_utils.h"

static t_bool	name_resolution(char **filename, int value)
{
	char	*value_str;
	char	*tmp;

	value_str = ft_lltoa_base(value, BASE_10);
	tmp = *filename;
	*filename = ft_strjoin(*filename, "_");
	if (!(*filename))
		return (error_handler(err_alloc_fail));
	tmp = ft_sec_free(tmp);
	tmp = *filename;
	*filename = ft_strjoin(*filename, value_str);
	if (!(*filename))
		return (error_handler(err_alloc_fail));
	tmp = ft_sec_free(tmp);
	value_str = ft_sec_free(value_str);
	return (true);
}

t_bool	add_name_image_resolution(char **filename, t_image *data)
{
	if (!(name_resolution(filename, data->width)))
		return (false);
	if (!(name_resolution(filename, data->height)))
		return (false);
	return (true);
}

t_bool	put_name_screenshot(char **dst, const char *map, t_image *data)
{
	char	*tmp1;

	tmp1 = ft_substr(map, 0, ft_strrchr(map, '.') - map);
	if (!(tmp1))
		return (error_handler(err_alloc_fail));
	*dst = ft_strjoin(BASENAME, tmp1);
	if (!(*dst))
		return (error_handler(err_alloc_fail));
	tmp1 = ft_sec_free(tmp1);
	if (!(add_name_image_resolution(dst, data)))
		return (false);
	return (true);
}
