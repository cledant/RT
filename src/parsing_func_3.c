/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:11:58 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 16:23:25 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	*rec_color(char *str)
{
	int		i;
	char	s[3];
	t_color	*ret;

	i = 0;
	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		malloc_error();
	while (str[i] != '"')
		i++;
	i++;
	s[2] = '\0';
	ret->r = ft_xtoi(ft_memcpy(s, &str[i], 2));
	ret->g = ft_xtoi(ft_memcpy(s, &str[i + 2], 2));
	ret->b = ft_xtoi(ft_memcpy(s, &str[i + 4], 2));
	ret->r /= 255;
	ret->g /= 255;
	ret->b /= 255;
	return (ret);
}

char	*rec_name(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i] != '"')
		i++;
	i++;
	j = i;
	while (str[i] != '"')
		i++;
	ret = ft_strdup(&str[j]);
	i = 0;
	while (ret[i] != '"')
		i++;
	ret[i] = '\0';
	return (ret);
}

int		rec_texture_type(char *ret)
{
	char	*name;

	name = rec_name(ret);
	if (ft_strcmp("img", name) == 0)
	{
		free(name);
		return (0);
	}
	else if (ft_strcmp("proc", name) == 0)
	{
		free(name);
		return (1);
	}
	else
	{
		free(name);
		return (1);
	}
}

t_tex	*rec_texture(char *str, t_tex *lst_tex)
{
	int		i;
	t_tex	*cpy;

	i = rec_int_value(str);
	cpy = lst_tex;
	while (cpy != NULL && cpy->id != i)
		cpy = cpy->next;
	if (cpy == NULL)
		xml_error_texture(2, 5, i);
	return (cpy);
}

t_img	*rec_img_addr(char *str, t_img *lst_img, int where)
{
	int		i;
	t_img	*cpy;

	i = rec_int_value(str);
	cpy = lst_img;
	while (cpy != NULL && cpy->id != i)
	{
		if (cpy->id == i)
			break ;
		cpy = cpy->next;
	}
	if (cpy == NULL)
		xml_error_texture(where, 2, i);
	return (cpy);
}
