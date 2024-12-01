#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long int cont = 1;
void cont_files(void);

int main(int argc, char *argv[])
{
  FILE *f = NULL;
  FILE *fout = NULL;
  char line[5000] = {'\0'};
  char fmt[5000] = {'\0'};
  unsigned long int i = 0;


  f = popen("ls ./basedoc", "r");
  if( f == NULL) return 1;

  fout = fopen("catalog.html", "w");
  if(fout == NULL) return 1;

  fgets(line, sizeof(line), f);
  fprintf(fout, "<style>\n");
  fprintf(fout, ".content {width: 95%;}\n");
  fprintf(fout, "  img {width: 20%; height: 20%; padding: 1%; border-radius: 10px;}\n");
  fprintf(fout, "  p {background: #000; color: #fff; opacity: 60%; font-size: 80%; border-radius: 8px;}\n");
  fprintf(fout, "  body {height: 100vh; background: url('img/back.jpg'); background-repeat: no-repeat; background-size: cover;}\n");
  fprintf(fout, "</style>\n");
  fprintf(fout, "<html lang=\"es\">\n");
  fprintf(fout, "<body>\n");
  fprintf(fout, "<div class=\"content\"><table border=0>\n");
  fprintf(fout, "<tr>\n");
    while(!feof(f))
    {
      line[strlen(line) - 1] = '\0';

      fprintf(fout, "<td>\n");
      fprintf(fout, "<div><center><a href=\"basedoc/%s/index.html\"><img src=\"basedoc/%s/portada.jpg\"></img></a></center></div>\n", line, line);
      sprintf(fmt, "./gen-portada.sh basedoc/%s", line);
      system(fmt);
      sprintf(fmt, "cp -fv /tmp/portada.jpg basedoc/%s/portada.jpg", line);
      system(fmt);
      fprintf(fout, "<center><p>%s</p></center>\n", line);
      fprintf(fout, "</td>\n");

      if((cont % 4) == 0)
      {
        fprintf(fout, "</tr>\n");
        fprintf(fout, "<tr>\n");
      }

      fgets(line, sizeof(line), f);
      cont++;
    }
    fprintf(fout, "</table>\n");
    fprintf(fout, "</div>\n");
    fprintf(fout, "</body>\n");
    fprintf(fout, "</html>\n");

    pclose(f);
    pclose(fout);
  return 0;
}

void cont_files(void)
{
  FILE *f = NULL;
  char line[5000] = {'\0'};


  f = popen("ls ./basedoc", "r");
  if( f == NULL) return;

  fgets(line, sizeof(line), f);
  while(!feof(f))
  {
    line[strlen(line) - 1] = '\0';
    cont++;
    fgets(line, sizeof(line), f);
  }
  pclose(f);
}
