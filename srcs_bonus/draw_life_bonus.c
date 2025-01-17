








void    draw_health(t_game *game)
{
    t_health h;

    h.width = game->player->screeen_width / 10;
    h.height = h.width / 2;
    h.start_y = game->player->screen_height / 10;
    h.start_x = game->player->screen_width - (h.width*2);
    h.border_c = 0xdb03fc;
    h.life_c = 0xfcba03;
    h.damage_c = 0x89818a;
    h.border_width = 2;
    h.end_y = h.start_y + h.height;
    h.end_x = h.start_x + h.width;

    int curr_x;
    int curr_y;

    curr_y = h.start_y;
    while(curr_y <= h.end_y)
    {
        curr_x = h.start_x;
        while (curr_x <= h.end_x)
        {
            if (pixel_is_border)
                put_pixel_to_image(game->conn, curr_x, curr_y, h.border_c);
            else
            {
                //find health bar width [((x_end - x_start - 2 * border_thickness)]
                // find x_limit [ x_start + border_thickness + health_width]
                // if curr_x <= x_limit then health color else damage color

            }
            curr_x++;
        }
        curr_y++;
    }



    //TODO:
    /*
    * bar-life-color: #fcba03
    * bar-damage-color: #89818a
    * bar's-border color: #db03fc 
    *bar will be a rectangle of size: 
        1 - screen_width / 10
        2 - screen_height / 20
    *where in the image to be drawn: 
        y coordinates: start at 1/10th of screen_height from top
        x coordinates: start at a point where x0 + bar width still has like 10% margin from right
    *if pixel corresponds to bar's-border, put border color, 
     else: take into consideration the life value (100 max = full bar colored) to color the 
     inner of the bars accordingly (bar-life-color or bar-damage-color).
    */
}