/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:03:40 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/30 15:04:21 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		textures_init(int fd, char *ret, t_env *e)
{
	e->tex_lst = NULL;
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "</textures>") == 0)
			break ;
		if (xml_cmp(ret, "<item") == 0)
			e->tex_lst = add_tex(fd, ret, e->tex_lst, e);
	}
}

void		images_init(int fd, char *ret, t_env *e)
{
	e->img_lst = NULL;
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "</images>") == 0)
			break ;
		if (xml_cmp(ret, "<item") == 0)
			e->img_lst = add_img(fd, ret, e->img_lst, e->mlx);
	}
}
