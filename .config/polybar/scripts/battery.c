#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BAT_PREFIX_PERCENT "/sys/class/power_supply/BAT1/capacity"
#define BAT_PREFIX_STATUS "/sys/class/power_supply/BAT1/status"
#define LOW_POWER 15
#define POWER_CHAR {"","","","","","","","",""}
#define NB_POWER_CHAR 9
#define CHARGING_CHAR ""
#define COLOR1 "#010C5F"
#define COLOR_LOW_BATTERY "#FFFB00"
#define COLOR2 "#72E1F8"

int main(int argc,char **arg){
  FILE * f;
  int percentage;
  char * unprocessedStatus;
  char status;
  f = fopen(BAT_PREFIX_PERCENT,"r");
  if(f==NULL){
    fprintf(stderr,"Echec de l'ouverture du fichier");
    exit(1);
  }
  fscanf(f,"%d",&percentage);
  fclose(f);
  f = fopen(BAT_PREFIX_STATUS,"r");
  if(f==NULL){
    fprintf(stderr,"Echec de l'ouverture du fichier");  
    exit(1);
  }
  fscanf(f,"%s",unprocessedStatus);
  if(strcmp(unprocessedStatus,"Discharging"))
    status = 1;
  else
    status = 0;
  fclose(f);

  char* discharging_char[NB_POWER_CHAR] = POWER_CHAR;
  if(status){
    printf("%%{F%s}%%{B%s}%%{T2} |%%{T-} %s %d%% %%{F- B-}", COLOR2, COLOR1, CHARGING_CHAR, percentage);
  }else{
    if(percentage<=LOW_POWER){
      printf("%%{F%s}%%{B%s}%%{T2}%%{T-}%%{F%s B%s} %s %d%%%%{F- B-}", COLOR_LOW_BATTERY, COLOR1, COLOR1, COLOR_LOW_BATTERY, discharging_char[NB_POWER_CHAR*percentage/100], percentage);
    }
    else{
      printf("%%{F%s}%%{B%s}%%{T2} |%%{T-} %s %d%% %%{F- B-}", COLOR2, COLOR1, discharging_char[NB_POWER_CHAR*percentage/100], percentage);
    }
  }

  return 0;
}
