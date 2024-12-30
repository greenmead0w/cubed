#include "cubed.h"

/*
** solving for the adjacent
*/
static void horz_find_point_a(t_ray *ray, t_player *player, char flag)
{
    double x;
    double y;
    double adjacent;
    double opposite;

    if (flag == 'u')
        y = (int)player->play_pos[0];
    else
        y = (int)player->play_pos[0] +1;
    opposite = y - player->play_pos[0]; //opposite is negative when upwards
    adjacent = opposite / tan(ray->angle); //what happens if tan(ray->angle) is almost 0?
    x = player->play_pos[1] + adjacent;
    ray->pos[0] = x;
    ray->pos[1] = y;
    ray->distance = sqrt(pow(adjacent, 2) + pow(opposite, 2));
}


static void upwards_facing_ray(t_ray *ray, t_player *player, t_vars *vars)
{
    double delta_x; //adjacent
    double delta_y; //opposite
    double tile_increment;
    
    delta_y = -1; //TILE_SIZE decrease in horz borders
    horz_find_point_a(ray, player, 'u');
    if (is_wall2(ray->pos[0], ray->pos[1] - 1, vars, ray))
        return;
    delta_x = delta_y / tan(ray->angle);
    tile_increment = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    while(!is_wall2(ray->pos[0], ray->pos[1] - 1, vars, ray))
    {
        ray->pos[0] += delta_x;
        ray->pos[1] += delta_y;
        ray->distance += tile_increment;
    }
}

static void downwards_facing_ray(t_ray *ray, t_player *player, t_vars *vars)
{
    double delta_x; //adjacent
    double delta_y; //opposite
    double tile_increment;
    
    delta_y = 1; //TILE_SIZE increase in horz borders
    horz_find_point_a(ray, player, 'd');
    if (is_wall3(ray->pos[0], ray->pos[1], vars, ray))
        return;
    delta_x = delta_y / tan(ray->angle);
    tile_increment = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    while(!is_wall3(ray->pos[0], ray->pos[1], vars, ray))
    {
        ray->pos[0] += delta_x;
        ray->pos[1] += delta_y;
        ray->distance += tile_increment;
    }
    
}

void horizontal_border(t_ray *ray, t_player *player, t_vars *vars)
{
    printf("ray->angle is: %d\n", (int)(ray->angle * 180 / M_PI));
    if (ray->angle == 0 * M_PI / 180 || ray->angle == 180 * M_PI / 180) 
    {
        ray->distance = INT_MAX;
        return;
    }
    if (ray->angle > 180* M_PI/180) //!!
        upwards_facing_ray(ray, player, vars);
    else
        downwards_facing_ray(ray, player, vars);
}