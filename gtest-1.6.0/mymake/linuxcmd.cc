#include <stdio.h>
#include <stdlib.h>
#include "linuxcmd.h"

int uname()
{
  int i;

  if (system(NULL)) 
    puts ("Ok");
  else 
    return i;

  printf ("Executing command uname -r...\n");

  i = system ("uname -r");

  printf ("Value returned: %d\n",i);
  return i;

}
