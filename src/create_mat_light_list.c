/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mat_light_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:58:39 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:22:05 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		add_mat_sub(char *ret, t_mat *new)
{
	if (xml_cmp(ret, "<specular") == 0)
		new->spec = rec_int_value(ret);
	if (xml_cmp(ret, "<reflection") == 0)
		new->refl = rec_int_value(ret);
	if (xml_cmp(ret, "<transparency") == 0)
		new->trans = rec_int_value(ret);
}

t_mat			*add_mat(int fd, char *ret, t_mat *mat)
{
	t_mat *new;

	if (!(new = (t_mat *)malloc(sizeof(t_mat))))
		malloc_error();
	new->next = NULL;
	new->id = rec_int_value(ret);
	new->trans = 0;
	new->spec = 0;
	new->refl = 0;
	new->ind_trans = 0;
	while (get_next_line(fd, &ret))
	{
		add_mat_sub(ret, new);
		if (xml_cmp(ret, "<refraction") == 0)
			new->ind_trans = rec_int_value(ret) / 100.0;
		if (xml_cmp(ret, "<color") == 0)
			new->color = rec_color(ret);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!mat)
		return (new);
	new->next = mat;
	return (new);
}

static void		add_light_sub(t_light *new)
{
	new->next = NULL;
	new->crd = NULL;
	new->vec = NULL;
	new->type = 0;
	new->intensity = 1;
}

t_light			*add_light(int fd, char *ret, t_light *light)
{
	t_light *new;

	if (!(new = (t_light *)malloc(sizeof(t_light))))
		malloc_error();
	add_light_sub(new);
	new->id = rec_int_value(ret);
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<type") == 0)
			new->type = rec_int_value(ret);
		if (xml_cmp(ret, "<crd") == 0)
			new->crd = rec_vec(ret);
		if (xml_cmp(ret, "<vector") == 0)
			new->vec = rec_vec(ret);
		if (xml_cmp(ret, "<intensity") == 0)
			new->intensity = rec_int_value(ret);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!light)
		return (new);
	new->next = light;
	return (new);
}
