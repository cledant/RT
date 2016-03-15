#include "rt.h"

void reflection(t_env *env, t_obj *hit_obj, t_hit_pt *hit_pt)
{
  t_vector3 normal;
  t_hit_pt  *hit_pt_refl;
  t_ray ray_refl;

  if (hit_obj->mat->refl > 0 && env->nb_refle < MAX_REFLE)
  {
    env->nb_refle++;
    hit_pt->color->r *= (100.0 - hit_obj->mat->refl) / 100.0;
    hit_pt->color->g *= (100.0 - hit_obj->mat->refl) / 100.0;
    hit_pt->color->b *= (100.0 - hit_obj->mat->refl) / 100.0;
    get_normal(&normal, hit_obj, hit_pt->root_ray->vec);
    ray_refl.vec = refle_vec(&normal, hit_pt->root_ray->vec);
    ray_refl.crd = hit_pt->crd;
    hit_pt_refl = get_color(&ray_refl, env);
    cap_color(hit_pt_refl->color);
    hit_pt->color->r += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->r;
    hit_pt->color->g += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->g;
    hit_pt->color->b += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->b;
  }
}
