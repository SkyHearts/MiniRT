#ifndef VECTOR3_H
# define VECTOR3_H


typedef struct  s_vec3
{
    float   x;
    float   y;
    float   z;
}               t_vec3;

t_vec3  *create_vec3(float _x, float _y, float _z);
t_vec3  add_vec3(t_vec3 vector1, t_vec3 vector2);


#endif