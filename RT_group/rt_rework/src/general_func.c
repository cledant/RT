/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:12:19 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/07 13:15:00 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void normalise(t_vector3 *vec)
{
  float tmp;

  tmp = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
  if (tmp != 0)
  {
    vec->x /= tmp;
    vec->y /= tmp;
    vec->z /= tmp;
  }
}
