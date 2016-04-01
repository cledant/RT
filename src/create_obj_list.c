/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:32:14 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 16:36:03 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			xml_check_obj_type(int value)
{
	if (value < 1 || value > 7)
		xml_error_texture(2, 4, value);
}

static void		add_obj_sub(char *ret, t_obj *new)
{
	if (xml_cmp(ret, "<type") == 0)
		new->type = rec_int_value(ret);
	if (xml_cmp(ret, "<crd") == 0)
		new->crd = rec_vec(ret);
	if (xml_cmp(ret, "<rotation") == 0)
		rec_rot(ret, new);
	if (xml_cmp(ret, "<sign") == 0)
		new->sign = rec_sign(ret);
	if (xml_cmp(ret, "<radius") == 0)
		new->r = rec_int_value(ret);
	if (xml_cmp(ret, "<coef") == 0)
		rec_coef(new, ret);
	if (xml_cmp(ret, "<sizeX") == 0)
		new->size_x = rec_int_value(ret) / 100.0;
	if (xml_cmp(ret, "<sizeY") == 0)
		new->size_y = rec_int_value(ret) / 100.0;
	if (xml_cmp(ret, "<sizeZ") == 0)
		new->size_z = rec_int_value(ret) / 100.0;
	if (xml_cmp(ret, "<translateX") == 0)
		new->tr_x = rec_int_value(ret);
	if (xml_cmp(ret, "<translateY") == 0)
		new->tr_y = rec_int_value(ret);
	if (xml_cmp(ret, "<translateZ") == 0)
		new->tr_z = rec_int_value(ret);
}

static void		add_obj_init(t_obj *new)
{
	new->size_x = 1;
	new->size_y = 1;
	new->size_z = 1;
	new->tr_x = 0;
	new->tr_y = 0;
	new->tr_z = 0;
	new->norm_type = 0;
	new->bump_img = NULL;
	new->norm_freq = 0.4;
	new->next = NULL;
}

t_obj			*add_obj(int fd, char *ret, t_obj *obj, t_env *e)
{
	t_obj *new;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		malloc_error();
	new->id = rec_int_value(ret);
	add_obj_init(new);
	init_rot(&new);
	while (get_next_line(fd, &ret))
	{
		add_obj_sub(ret, new);
		if (xml_cmp(ret, "<texture") == 0)
			new->tex = rec_texture(ret, e->tex_lst);
		if (xml_cmp(ret, "<normal") == 0)
			new->norm_type = rec_int_value(ret);
		if (xml_cmp(ret, "<freq") == 0)
			new->norm_freq = rec_int_value(ret) / 100.0;
		if (xml_cmp(ret, "<bump_img") == 0)
			new->bump_img = rec_img_addr(ret, e->img_lst, 2);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!obj)
		return (new);
	new->next = obj;
	return (new);
}
