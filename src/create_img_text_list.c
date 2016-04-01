/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img_text_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:09:49 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 16:36:19 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			xml_check_texture_type(int value)
{
	if (value < 1 || value > 5)
		xml_error_texture(1, 3, value);
}

static void		add_tex_sub(char *ret, t_tex *new)
{
	if (xml_cmp(ret, "<type") == 0)
	{
		new->type = rec_int_value(ret);
		xml_check_texture_type(new->type);
	}
	if (xml_cmp(ret, "<size") == 0)
		new->size = rec_int_value(ret);
	if (xml_cmp(ret, "<grad_r") == 0)
		new->grad_r = rec_int_value(ret);
	if (xml_cmp(ret, "<grad_g") == 0)
		new->grad_g = rec_int_value(ret);
	if (xml_cmp(ret, "<grad_b") == 0)
		new->grad_b = rec_int_value(ret);
	if (xml_cmp(ret, "<octave") == 0)
		new->octa = rec_int_value(ret);
	if (xml_cmp(ret, "<frequency") == 0)
		new->freq = rec_int_value(ret) / 100.0;
}

static void		add_tex_init(t_tex *new)
{
	new->type = 1;
	new->next = NULL;
	new->mat_1 = NULL;
	new->mat_2 = NULL;
	new->size = 2;
	new->grad_r = 0;
	new->grad_g = 0;
	new->grad_b = 0;
	new->freq = 0.5;
	new->octa = 4;
}

t_tex			*add_tex(int fd, char *ret, t_tex *tex, t_env *e)
{
	t_tex *new;

	if (!(new = (t_tex *)malloc(sizeof(t_tex))))
		malloc_error();
	add_tex_init(new);
	new->id = rec_int_value(ret);
	while (get_next_line(fd, &ret))
	{
		add_tex_sub(ret, new);
		if (xml_cmp(ret, "<material1") == 0)
			new->mat_1 = rec_mat_addr(ret, e->mat_lst);
		if (xml_cmp(ret, "<material2") == 0)
			new->mat_2 = rec_mat_addr(ret, e->mat_lst);
		if (xml_cmp(ret, "<material_img") == 0)
			new->mat_img = rec_mat_addr(ret, e->mat_lst);
		if (xml_cmp(ret, "<image") == 0)
			new->img = rec_img_addr(ret, e->img_lst, 1);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!tex)
		return (new);
	new->next = tex;
	return (new);
}

t_img			*add_img(int fd, char *ret, t_img *image, void *mlx)
{
	t_img *new;

	if (!(new = (t_img *)malloc(sizeof(t_img))))
		malloc_error();
	new->next = NULL;
	new->id = rec_int_value(ret);
	new->img = NULL;
	new->data = NULL;
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<file") == 0)
			rec_image_file(&new, ret, mlx);
		if (xml_cmp(ret, "</item>") == 0)
			break ;
	}
	if (!image)
		return (new);
	new->next = image;
	return (new);
}
