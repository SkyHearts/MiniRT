#include "vector3.h"

t_vec3  *create_vec3(float _x, float _y, float _z)
{
    t_vec3 *new_vec3;

    new_vec3 = malloc (sizeof(t_vec3) * 1);
    new_vec3->x = _x;
    new_vec3->y = _y;
    new_vec3->y = _y;
    return (new_vec3);
}

t_vec3  add_vec3(t_vec3 vector1, t_vec3 vector2)
{
    t_vec3  result;

    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;
    return (result);
}

t_vec3  sub_vec3(t_vec3 vector1, t_vec3 vector2)
{
    t_vec3  result;

    result.x = vector1.x - vector2.x;
    result.y = vector1.y - vector2.y;
    result.z = vector1.z - vector2.z;
    return (result);
}

float  dot_vec3(t_vec3 vector1, t_vec3 vector2)
{
    float result;
    
    result = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
    return (result);
}