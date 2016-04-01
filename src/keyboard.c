/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 09:18:42 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/31 13:40:03 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	escape(t_env *e)
{
	if (e->menu->selected == 0)
		free_env(e);
	e->menu->text = ft_itoa(*(e->menu->data[e->menu->selected - 1]));
	print_modification(e, (((e->menu->selected - 1) / 3 + 1) * 100 + 20 *
		((e->menu->selected - 1) % 3)), e->menu->text, 0xFFFFFF);
	e->menu->selected = 0;
}

static void	enter(t_env *e)
{
	if (e->menu->selected > 3)
	{
		*(e->menu->data[e->menu->selected - 1]) = ft_atoi(e->menu->text)
			* RADIAN;
		e->menu->data[e->menu->selected - 1][1] =
			cos(e->menu->data[e->menu->selected - 1][0]);
		e->menu->data[e->menu->selected - 1][2] =
			sin(e->menu->data[e->menu->selected - 1][0]);
	}
	else
		*(e->menu->data[e->menu->selected - 1]) = ft_atoi(e->menu->text);
	print_modification(e, (((e->menu->selected - 1) / 3 + 1) * 100 + 20 *
		((e->menu->selected - 1) % 3)),
		ft_itoa(ft_atoi(e->menu->text)), 0xFFFFFF);
	e->menu->selected = 0;
}

static void	add_number(char c, t_env *e)
{
	int i;

	i = 0;
	while (e->menu->text[i] != '\0')
		i++;
	if (i < 14)
	{
		e->menu->text[i] = c;
		e->menu->text[i + 1] = '\0';
	}
}

static void	del_number(t_env *e)
{
	int i;

	i = 0;
	while (e->menu->text[i] != '\0')
		i++;
	if (i > 0)
		e->menu->text[i - 1] = '\0';
}

int			ft_key_hook(int keycode, t_env *e)
{
	if (keycode == 53)
		escape(e);
	if (e->menu->selected != 0 && keycode == 51)
		del_number(e);
	else if (e->menu->selected != 0 && keycode == 36)
		enter(e);
	else if (e->menu->selected != 0)
		add_number(get_char(keycode), e);
	if (e->menu->selected != 0)
		print_modification(e, (((e->menu->selected - 1) / 3 + 1) * 100 + 20 *
			((e->menu->selected - 1) % 3)), e->menu->text, 0xFF0000);
	return (0);
}
