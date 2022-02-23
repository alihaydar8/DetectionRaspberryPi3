#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
struct tm clock_now()
{
    time_t secondes;
    struct tm instant;

    time(&secondes);
    instant=*localtime(&secondes);

    return instant;
}

double return_timestamp(){
    time_t timestamp = time( NULL );
    return timestamp;
}

void message(char *str, char *email) {

    struct tm instant = clock_now();
    char  text[7];
    sprintf(text, "%d",instant.tm_mday);
    strcpy(str, "echo 'individue repère chez toi le ");
    strcat(str,text);
    strcat(str, "/");
    sprintf(text, "%d",instant.tm_mon+1);
    strcat(str,text);
    strcat(str, " à ");
    sprintf(text, "%d",instant.tm_hour+1);
    strcat(str,text);
    strcat(str, ":");
    sprintf(text, "%d",instant.tm_min);
    strcat(str,text);
    strcat(str," ' | mutt -s 'photo' -a '/home/pi/ali/photo");
    sprintf(text, "%ld",return_timestamp());
    strcat(str,text);
    strcat(str,".png ' -- ");
    strcat(str,email);
    printf("%s",str);
}