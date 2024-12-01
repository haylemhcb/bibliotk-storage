#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char cmd[8000] = {'\0'};

  system("rm -r $HOME/out-html-pdf");
  sprintf(cmd, "./pdf_to_web ./upload/*");
  system(cmd);
  system("mkdir basedoc");

  return 0;
}
