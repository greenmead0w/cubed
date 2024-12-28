#include "cubed.h"




static void find_point_a(t_ray *ray, t_player *player, char flag)
{
    double x;
    double y;
    double adjacent;
    double opposite;

    // doubts: what happens if ray facing down?
    if (flag == 'r')
    {
        x = (int)(player->play_pos[1] +1);
        adjacent = x - player->play_pos[1];
        opposite = tan(ray->angle) * adjacent;
        y = player->play_pos[0] + opposite;
        ray->point_a[0] = x;
        ray->point_a[1] = y;
    }
    else
    {
        x = (int)player->play_pos[1];
        adjacent = player->play_pos[1] - x;
        opposite = tan(ray->angle) * adjacent;
        y = player->play_pos[0] + opposite;

    }
}

static void right_facing_ray(t_ray *ray, t_player *player, char **map)
{

    //find point A
    find_point_a(ray, player, 'r')
  
    first_border_y = tan(ray->angle) * first_border_x + player->play_pos[0];

}

/*
** INT_MAX to prevent infinite loop if ray doesn't hit any vertical border,
**  when angle is either 90 or 270 degrees
*/
void vert_border(t_ray *ray, t_player *player, char **map)
{
    if (ray->angle == 90 * M.PI / 180 || ray->angle == 270 * M.PI / 180) 
    {
        ray->distance = INT_MAX;
        return;
    }
    if (ray->angle > 270 * M.PI/180  || ray->angle < 90 * M.PI/180)
        right_facing_ray(ray, player, map);
    else
        left_facing_ray(ray, player, map);
}