/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 09:18:42 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/30 14:43:50 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_modification(t_env *e, int y, char *text, int color)
{
	int i;
	int j;

	i = 50;
	while (i < 199)
	{
		j = 0;
		while (j < 20)
		{
			mlx_pixel_put(e->mlx, e->win, i, y + j, 0x00000);
			j++;
		}
		i++;
	}
	mlx_string_put(e->mlx, e->win, 50, y, color, text);
	mlx_do_sync(e->mlx);
}

void	selection(t_env *e, int y)
{
	if (y >= 100 && y <= 160)
		e->menu->selected = (y - 100) / 20 + 1;
	else
		e->menu->selected = (y - 200) / 20 + 4;
	if (e->menu->selected > 3)
		e->menu->text = ft_itoa(*(e->menu->data[e->menu->selected - 1])
				/ RADIAN);
	else
		e->menu->text = ft_itoa(*(e->menu->data[e->menu->selected - 1]));
	print_modification(e, y - (y % 20), e->menu->text, 0xFF0000);
}

void	switch_obj(t_env *e, int ind)
{
	e->menu->ind_elem += ind;
	get_elem(e);
	print_menu(e);
}

char	get_char(int keycode)
{
	if (keycode >= 82 && keycode <= 89)
		return (48 + keycode % 82);
	if (keycode == 91)
		return ('8');
	if (keycode == 92)
		return ('9');
	if (keycode == 78)
		return ('-');
	return ('\0');
}

void	get_elem(t_env *e)
{
	int		i;
	t_obj	*obj_tmp;
	t_obj	*previous;

	if (e->menu->ind_elem == 0)
		get_cam(e);
	else if (e->menu->ind_elem <= e->nb_lights && e->menu->ind_elem > 0)
		find_light(e);
	else
	{
		i = e->nb_lights + 1;
		obj_tmp = e->obj_lst;
		previous = obj_tmp;
		while (obj_tmp && (i < e->menu->ind_elem || e->menu->ind_elem == -1))
		{
			i++;
			previous = obj_tmp;
			obj_tmp = obj_tmp->next;
		}
		find_object(e, obj_tmp, i, previous);
	}
}
