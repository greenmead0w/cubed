
// cuenta el número de lineas
int count_map_lines(char **map) 
{
    int lines;
    
    lines = 0;
    while (map[lines] != NULL) 
        lines++;
    return lines;
}

//cuenta la linea más larga
int map_max_length(char **map)
{
    int temp;
    int len;
    int i;

    len = 0;
    i = 0;
    while(map[i] != NULL)
    {
        temp = ft_strlen(map[i]);
        if (temp > len)
            len = temp;
        i++;
    }
    return len;
}


//retorna 1 si el mapa contiene caracteres válidos, -1 en caso contrario y 0 si el mapa es nulo (por si acaso)
int map_valid_chars(char **map)
{
    const char *valid_chars = "01 NSEW";
    int i;
    int j;

    i = 0;
    j = 0;
    if (map == NULL || map[i] == NULL)
        return 0;
    while (map[i] != NULL)
    {
        while(map[i][j] != '\0')
        {
            if(ft_strchr(valid_chars, map[i][j]) == NULL)
                return -1;
            j++;
        }
        i++;
    }
    return 1;
}

//cuenta cantidad de start positions en el mapa
int map_start_position(char **map)
{
    int pos_counter;
    const char *start_chars = "NSEW";
    int i;
    int j;

    pos_counter = 0;
    i = 0;
    j = 0;
    while(map[i] != NULL)
    {
        while(map[i][j] != '\0')
        {
            if(ft_strchr(start_chars, map[i][j]) != NULL)
                pos_counter++;
            j++;
        }
        i++;
    }
    return pos_counter;
}

//crea una matriz rectangular
char **make_rectangular_map(char **map, int lines, int max_len)
{
    char **rect;
    int i;

    i = 0;
    rect = malloc(sizeof(char *) * lines + 1);
    if (rect == NULL)
        return rect;
    while (i < lines)
    {
        rect[i] = malloc(sizeof(char) * max_len +1);
        if (rect[i] == NULL)
            //free_char**
        ft_strlcpy(rect[i], map[i], ft_strlen(map[i]));
        ft_memset(rect[i] + ft_strlen(map[i]), ' ', max_len - ft_strlen(map[i]));
        rect[i][max_len] = '\0';
        i++;
    }
    rect[lines] = NULL;
    return rect;
}


/*
**  el mapa no estará sellado (y esta función retornará 1) si:
**  1 - hay un '0' o posición de inicio en el borde del mapa
**  2-  hay un '0' o posición de inicio al lado de un espacio
*/
int not_sealed_map(char **map, int lines, int max_len)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(map[i] != NULL)
    {
        while(map[i][j] != '\0')
        {
            if (map[i][j] != '1' || map[i][j] != ' ')
            {
                if (i == 0 || i == lines -1 ||j == 0 || j == max_len -1)
                    return 1;
                if(map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' ' || map[i - 1][j + 1] == ' '
                || map[i][j - 1] == ' ' || map[i][j + 1] == ' '
                || map[i + 1][j - 1] == ' ' || map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

/*
**  suponiendo que:
**  1- no se me pasa como parametro la cantidad de lineas
**  2- no se me pasa como parametro la linea más larga
**  3- caracteres válidos: "0,1, ,N,S,E,W"
**  4- 
*/
int check_map(char **map)
{
    int lines;
    int max_len;
    char **rect_map;

    lines = count_map_lines(map);
    max_len = map_max_length(map);
    if (map_valid_chars(map) == -1 || map_start_position(map) != 1)
        return -1;
    rect_map = make_rectangular_map(map);
    if (rect_map == NULL)
        return -1;
    if (not_sealed_map(rect_map, lines, max_len) == 1)
        return -1;
    return 1;
}

