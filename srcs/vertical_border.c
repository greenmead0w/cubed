#include "cubed.h"

/*
**  solving for the opposite
**  find x,y coordinates of point a, which is first vertical border the ray hits
**  stores the rays distance to the border
*/
static void vert_find_point_a(t_ray *ray, t_player *player, char flag)
{
    double x;
    double y;
    double adjacent;
    double opposite;

    if (flag == 'r')
        x = (int)(player->play_pos[1] +1);
    else
        x = (int)player->play_pos[1];
    adjacent = x - player->play_pos[1];
    opposite = tan(ray->angle) * adjacent;
     y = player->play_pos[0] + opposite;
    ray->pos[0] = x;
    ray->pos[1] = y;
    ray->distance = sqrt(pow(adjacent, 2) + pow(opposite, 2));
}

static void right_facing_ray(t_ray *ray, t_player *player, t_vars *vars)
{
    double delta_x; //adjacent
    double delta_y; //opposite
    double tile_increment;
    
    delta_x = 1; //TILE_SIZE increment in vertical borders
    vert_find_point_a(ray, player, 'r');
    if (ray_is_wall(ray->pos[0], ray->pos[1], vars, ray))
        return;
    delta_y = tan(ray->angle) * delta_x;
    tile_increment = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    while(!ray_is_wall(ray->pos[0], ray->pos[1], vars, ray))
    {
        ray->pos[0] += delta_x;
        ray->pos[1] += delta_y;
        ray->distance += tile_increment;
    }
    // printf("vert_ray->pos[0] is %f\n",  ray->pos[0]);
    // printf("vert_ray->pos[1] is %f\n",  ray->pos[1]);

}

/*
**  different from a righ_facing_ray in :
**  1 - how to find point a
**  2 - adjacent is negative
**  3 - the border is part of which tile?
*/
static void left_facing_ray(t_ray *ray, t_player *player, t_vars *vars)
{
    double delta_x; //adjacent
    double delta_y; //opposite
    double tile_increment;
    
    delta_x = -1; //TILE_SIZE decrease in vertical borders
    vert_find_point_a(ray, player, 'l');
    if (ray_is_wall(ray->pos[0] -1, ray->pos[1], vars, ray))
        return;
    delta_y = tan(ray->angle) * delta_x;
    tile_increment = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    while(!ray_is_wall(ray->pos[0] - 1, ray->pos[1], vars, ray))
    {
        ray->pos[0] += delta_x;
        ray->pos[1] += delta_y;
        ray->distance += tile_increment;
    }

}

/*
** INT_MAX to prevent infinite loop if ray doesn't hit any vertical border,
**  when angle is either 90 or 270 degrees
*/
void vertical_border(t_ray *ray, t_player *player, t_vars *vars)
{
    //can we run into rounding problems due to floating imprecision??
    if (ray->angle == 90 * M_PI / 180 || ray->angle == 270 * M_PI / 180) 
    {
        ray->distance = INT_MAX;
        return;
    }
    if (ray->angle > 270 * M_PI/180  || ray->angle < 90 * M_PI/180)
        right_facing_ray(ray, player, vars);
    else
        left_facing_ray(ray, player, vars);
}