#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>

#define STATE_FILE_PATH "/tmp/state_info_menu"
#define MENU_STRING "%{F#434553 T2}%{F- T-}%{F#D5D8D4 B#434553}%{A1:~/.config/polybar/scripts/info-menu -v:}  %{A}|%{A1:~/.config/polybar/scripts/info-menu -t:}  %{A}|%{A1:~/.config/polybar/scripts/info-menu -b:}%{A}%{F- B-}"
#define DISKS_MNT {"/","/home"}
#define DISKS_MNT_ICONS {"",""}
#define NB_DISK_MNT 2

void exec(char* command, char * result,int size){
  FILE *fp;
  /* Open the command for reading. */
  system(command);
  fp = fopen("/tmp/stdout", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  fgets(result, sizeof(char)*size, fp);

  /* close */
  fclose(fp);
}

void doVolume(){
  printf("%%{F#847F85 T2}%%{F- T-}%%{B#847F85 F#D5D8D4} ");
  const unsigned int GB = (1024 * 1024) * 1024;
  struct statvfs buffer;
  char * disks_names[NB_DISK_MNT] = DISKS_MNT_ICONS;
  char * disks[NB_DISK_MNT] = DISKS_MNT;
  for(int i = 0; i<NB_DISK_MNT;i++){
    int ret = statvfs(disks[i], &buffer);
    if (!ret) {
      const double total = (double)(buffer.f_blocks * buffer.f_frsize) / GB;
      const double available = (double)(buffer.f_bfree * buffer.f_frsize) / GB;
      const double used = total - available;
      const double percentage = 100-(int)((double)(used / total) * (double)100);
      const double usedPercentage = (double)(used / total) * (double)100;
      printf("%s %0.1fG/%0.1fG ",disks_names[i], available, total);
      printf("%%{u#D5D8D4}%%{o#D5D8D4}%%{+o}%%{+u}%%{T6}");
      int i;
      for (i = 0; i < usedPercentage-10; i+=10) {
        printf("█");
      }
      if(usedPercentage-i<1.25){
        printf("  ");
      }else if(usedPercentage-i<2.5){
        printf("▏");
      }else if(usedPercentage-i<3.75){
        printf("▎");
      }else if(usedPercentage-i<5){
        printf("▍");
      }else if(usedPercentage-i<6.25){
        printf("▌");
      }else if(usedPercentage-i<7.5){
        printf("▋");
      }else if(usedPercentage-i<8.75){
        printf("▊");
      }else {
        printf("▉");
      }
      for (int i = 0; i < percentage-1; i+=8) {
        printf("  ");
      }/*
      for (int i = 0; i < usedPercentage; i+=10) {
        printf("#");
      }
      for (int i = 0; i < percentage; i+=10) {
        printf("--");
      }*/
      printf("%%{-o}%%{-u}%%{T-} ");
    }
  }
  printf("%%{B#847F85}%s\n",MENU_STRING);
}

void doTemps(){
  printf("%%{F#847F85 T2}%%{F- T-}%%{B#847F85 F#D5D8D4}");
  FILE * tempf = fopen("/sys/devices/platform/coretemp.0/hwmon/hwmon3/temp3_input", "r");
    int temp;
    fscanf(tempf, "%i", &temp);
    temp = temp/1000;
    printf("  %i°C",temp);
  fclose(tempf);
  printf("%%{B#847F85}%s\n",MENU_STRING);
}

void doBT(){
  printf("%%{F#847F85 T2}%%{F- T-}%%{B#847F85 F#D5D8D4}%%{A1:blueman-manager:} ");
  char enable[1024];

  exec("bluetoothctl show | grep 'Powered: yes' | cut -d ':' -f 2 > /tmp/stdout",enable,1024);  

  if (strlen(enable)==5) {
    char name[1024];

    exec("echo info | bluetoothctl | grep Name | cut -d ':' -f 2 > /tmp/stdout", name, 1024);
    
    if (strlen(name)!=0) {
      char type[1024];

      exec("echo info | bluetoothctl | grep Icon | cut -d ':' -f 2 > /tmp/stdout", type, 1024);
      
      if (strcmp(type," audio-card\n")==0) {
        printf(" :");
      } else {
        printf(" :");
      }
      name[strlen(name)-1] = '\0';
      printf("%s",name);
    } else {
      printf(" : Disconnected");
    }

  }else {
    printf(" : Disabled");
  }

  printf("%%{A}");
  printf("%%{B#847F85} %s\n",MENU_STRING);

}

int main(int argc, char ** argv)
{
  FILE * f;
  char mode[10];
  if (argc==2&&argv[1][0]=='-') {
    switch (argv[1][1]) {
      case 'v':
        f = fopen(STATE_FILE_PATH, "r");
        if (f!=NULL) {
          fgets(mode, 8, f);
        }
        if(mode != NULL && strcmp(mode,"VOLUMES")){
          f = fopen(STATE_FILE_PATH, "w");
            fprintf(f, "VOLUMES");
          fclose(f);
        }else{
          f = fopen(STATE_FILE_PATH, "w");
            fprintf(f, "NONE");
          fclose(f);
        }
        break;
      case 't':
        f = fopen(STATE_FILE_PATH, "r");
        if (f!=NULL) {
          fgets(mode, 8, f);
        }
        if(mode != NULL && strcmp(mode,"TEMPS")){
          f = fopen(STATE_FILE_PATH, "w");
            fprintf(f, "TEMPS");
          fclose(f);
        }else{
          f = fopen(STATE_FILE_PATH, "w");
            fprintf(f, "NONE");
          fclose(f);
        }
        break;
      case 'b':
        f = fopen(STATE_FILE_PATH, "r");
        if (f!=NULL) {
          fgets(mode, 10, f);
        }
        if(mode != NULL && strcmp(mode,"BLUETOOTH")){
          f = fopen(STATE_FILE_PATH, "w");
            fprintf(f, "BLUETOOTH");
          fclose(f);
        }else{
          f = fopen(STATE_FILE_PATH, "w");
            fprintf(f, "NONE");
          fclose(f);
        }
        break;
      default:
        break;
    }
  }else if(argc==1){
    f = fopen(STATE_FILE_PATH, "r");
      if (f==NULL) {
        f = fopen(STATE_FILE_PATH, "w");
        fprintf(f, "NONE");
        strncpy(mode,"NONE",4);
      }else{
        fgets(mode, 10, f);
      }
    if(strcmp(mode,"VOLUMES")==0){
      doVolume();
    }else if(strcmp(mode,"TEMPS")==0){
      doTemps();
    }else if(strcmp(mode,"BLUETOOTH")==0){
      doBT();
    }
    else{
      printf("%s\n",MENU_STRING);
    }
    fclose(f);
  }
  return 0;
}
