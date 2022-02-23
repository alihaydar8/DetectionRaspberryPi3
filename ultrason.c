#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>

#include "message.c"

#define TRIGGER 23
#define ECHO 24

void setup()
{
  wiringPiSetupGpio();
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  digitalWrite(TRIGGER, LOW);
  delay(500);
}

int main()
{
  double start;
  double fin;
  char *str =(char*)malloc(100*sizeof(char));
  char *email =(char*)malloc(20*sizeof(char));
  printf("Debut\n");
  setup();

  while (1)
  {

    digitalWrite(TRIGGER, HIGH);
    delay(20);
    digitalWrite(TRIGGER, LOW);
    while (digitalRead(ECHO) == LOW);//tant qu'il reçois rien
    start = micros();// demarre timer
    while (digitalRead(ECHO) == HIGH);//tant qu'il reçois quelque chose
    long fin = micros() - start;//calcul le temps de voyage
    int distance = fin / 58;//calcul la distance
    
    printf("Distance : %d cm\n", distance);
    if (distance>0 && distance<250) {
      system("raspistill -ts -o photo%d.png");//// je prends la photo
      message(str,"alihaydar3223@gmail.com");//// j'ecrit la commande qui envoie le maill
      delay(5000);///j'attends 5s le temps de prendre la photo
      system(str);//// j'envoie le maill
    }

  }

  return 0;
}
