#include "map.h"

void free_array2d(char **str)
{
    char **temp = str; // Geçici bir pointer oluştur ve str'nin adresini atayarak başla

    // temp NULL değilse ve temp'in gösterdiği adres NULL değilse
    while (temp && *temp)
    {
        //printf("free edilen temp -> %s\n",*temp);
        free(*temp); // Her bir string için belleği serbest bırak
        temp++;      // Sonraki stringe geçmek için temp'i artır
    }

    free(str); // Dizinin kendisini serbest bırak
}

