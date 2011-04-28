#include <stdio.h>
#include <stdlib.h>
#include "linuxcmd.h"

int ld()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandld");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int lda(int assertion)
{
  int c;
  FILE *fd;

  switch (assertion)
    {
     case 1:
       fd = fopen("/tmp/lda1.txt", "r");
       break;
     case 2:
       fd = fopen("/tmp/lda2.txt", "r");
       break;
     case 3:
       fd = fopen("/tmp/lda3.txt", "r");
       break;
     case 4:
       fd = fopen("/tmp/lda4.txt", "r");
       break;
     case 5:
       fd = fopen("/tmp/lda5.txt", "r");
       break;
     case 6:
       fd = fopen("/tmp/lda6.txt", "r");
       break;
     case 7:
       fd = fopen("/tmp/lda7.txt", "r");
       break;
    default:
      ;
   }

  if (fd == NULL){
    printf("FOPEN FAILED\n");
    return -1;
  }else{
    c = fgetc(fd);
    c = c - '0';
  }

  return c;
}


int ar()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandar");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int cp()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandcp");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int cpio()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandcpio");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int cron()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandcron");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int file()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandfile");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int gzip()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandgzip");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int ldd()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandldd");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int ln()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandln");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int mail()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandmail");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int mkdir()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandmkdir");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int mv()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandmv");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int nm()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandnm");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int objdump()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandobjdump");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int size()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandsize");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int tar()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandtar");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int unzip()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/commandunzip");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}

int logrotate()
{
  int ret;
  ret = system("sudo /opt/ltp/runltp -f /opt/ltp/runtest/logrotate");
  /*getting the returned value*/
  ret = ret>>8;
  return ret;
}
