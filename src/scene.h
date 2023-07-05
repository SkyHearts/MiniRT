#ifndef SCENE_H
# define SCENE_H

#include "mlx.h"

typedef struct  s_scene
{
    t_object object;
    struct s_object *next;

    
}               t_scene;

typedef struct  s_object
{
    int type;
    int index;
}               t_object;

#endif