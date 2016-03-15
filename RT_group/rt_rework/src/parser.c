/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 12:53:45 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/14 15:30:17 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void parameters_init(int fd, char *ret, t_env *e)
{
  while (get_next_line(fd, &ret))
  {
    if (xml_cmp(ret, "</parameters>") == 0)
      break;
    if (xml_cmp(ret, "<resolution") == 0)
    {
      e->width = rec_int_value(ret);
      e->height = rec_int_value(&ret[24]);
    }
    if (xml_cmp(ret, "<ambient") == 0)
      e->ambient = rec_float_value(ret) / 100;
    if (xml_cmp(ret, "<background") == 0)
      e->background = rec_color(ret);
    if (xml_cmp(ret, "<camera>") == 0)
      rec_cam(fd, ret, e);
  }
}

static void textures_init(int fd, char *ret, t_env *e)
{
  e->tex_lst = NULL;
  while (get_next_line(fd, &ret))
  {
    if (xml_cmp(ret, "</textures>") == 0)
      break;
    if (xml_cmp(ret, "<item") == 0)
      e->tex_lst = add_tex(fd, ret, e->tex_lst, e->mlx);
  }
}

static void materials_init(int fd, char *ret, t_env *e)
{
  e->mat_lst = NULL;
  while (get_next_line(fd, &ret))
  {
    if (xml_cmp(ret, "</materials>") == 0)
      break;
    if (xml_cmp(ret, "<item") == 0)
      e->mat_lst = add_mat(fd, ret, e->mat_lst, e->tex_lst);
  }
}

static void lights_init(int fd, char *ret, t_env *e)
{
  int in_comment;

  in_comment = 0;
  e->light_lst = NULL;
  while (get_next_line(fd, &ret))
  {
    if (xml_cmp(ret, "<!--#") == 0)
      in_comment = 1;
    if (xml_cmp(ret, "</lights>") == 0)
      break;
    if (in_comment == 0 && xml_cmp(ret, "<item") == 0)
      e->light_lst = add_light(fd, ret, e->light_lst);
    if (xml_cmp(ret, "#-->") == 0)
      in_comment = 0;
  }
}

static void objects_init(int fd, char *ret, t_env *e)
{
  int in_comment;

  in_comment = 0;
  e->obj_lst = NULL;
  while (get_next_line(fd, &ret))
  {
    if (xml_cmp(ret, "<!--#") == 0)
      in_comment = 1;
    if (xml_cmp(ret, "</objects>") == 0)
      break;
    if (in_comment == 0 && xml_cmp(ret, "<item") == 0)
      e->obj_lst = add_obj(fd, ret, e->obj_lst, e->mat_lst);
    if (xml_cmp(ret, "#-->") == 0)
      in_comment = 0;
  }
}

void   parsing(int fd, t_env *e)
{
  int   i;
  char  *ret;
  i = 0;

  while (get_next_line(fd, &ret))
  {
    if (xml_cmp(ret, "<scene") == 0)
      e->scene_name = rec_name(ret);
    if (i == 0)
    {
      parameters_init(fd, ret, e);
	  init_mlx(e);
      i++;
    }
    if (i == 1)
	{
      textures_init(fd, ret, e);
      i++;
    }
    if (i == 2)
    {
      materials_init(fd, ret, e);
      i++;
    }
    if (i == 3)
    {
      lights_init(fd, ret, e);
      i++;
    }
    if (i == 4)
    {
      objects_init(fd, ret, e);
      i++;
    }
  }
}
