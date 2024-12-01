/*

  Módulo evaluador de usuario

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void verify_access(const char *usr, const char *pass);
void generate_html_subir(void);


#define MAX_INPUT 1024

void print_header() {
    printf("Content-Type: text/html\n\n");
}

void parse_input(char *input) {
    char *usuario = NULL;
    char *password = NULL;

    // Parsear el input
    char *token = strtok(input, "&");
    while (token != NULL) {
        if (strncmp(token, "usuario=", 8) == 0) {
            usuario = token + 8;
        } else if (strncmp(token, "password=", 9) == 0) {
            password = token + 9;
        }
        token = strtok(NULL, "&");
    }

    // Decodificar URL
    if (usuario) {
        for (char *p = usuario; *p; p++) {
            if (*p == '+') *p = ' ';
            if (*p == '%') {
                int value;
                sscanf(p + 1, "%2x", &value);
                *p = (char)value;
                memmove(p + 1, p + 3, strlen(p + 3) + 1);
            }
        }
    }
    if (password) {
        for (char *p = password; *p; p++) {
            if (*p == '+') *p = ' ';
            if (*p == '%') {
                int value;
                sscanf(p + 1, "%2x", &value);
                *p = (char)value;
                memmove(p + 1, p + 3, strlen(p + 3) + 1);
            }
        }
    }

    verify_access(usuario, password);

}

void verify_access(const char *usr, const char *pass)
{
  FILE *f = NULL;
  char line[5000] = {'\0'};
  char *usuario = NULL;
  char *password = NULL;

  f = fopen("./passwordapp.txt", "r");

  if(f == NULL)
  {
    puts("Error base de usuarios!!!");
    return;
  }

  fgets(line, sizeof(line), f);
  while(!feof(f))
  {
    line[strlen(line) - 1] = '\0';
    usuario = strtok(line, ",");
    if(usuario == NULL) return;

    password = strtok(NULL, ",");
    if(password == NULL) return;

    fgets(line, sizeof(line), f);
  }

  generate_html_subir();

  if((strcmp(usuario, usr) == 0) && (strcmp(password, pass) == 0))
  {
    printf("<script>document.location='/subir.html';</script>");
  }
  else
    printf("<script>document.location='/';</script>");
}

int main() {
    char *lenstr;
    int len;

    // Obtener la longitud del contenido
    lenstr = getenv("CONTENT_LENGTH");
    if (lenstr == NULL) {
        len = 0;
    } else {
        len = atoi(lenstr);
    }

    // Leer el input
    char input[MAX_INPUT];
    if (len > 0 && len < MAX_INPUT) {
        fread(input, 1, len, stdin);
        input[len] = '\0'; // Asegurarse de que la cadena esté terminada
    } else {
        input[0] = '\0';
    }

    // Imprimir cabecera
    print_header();

    // Procesar el input
    parse_input(input);

    return 0;
}

void generate_html_subir(void)
{
  FILE *file = NULL;
  char str[] = {" <!DOCTYPE html>\
                  <html lang=\"es\">\
                    <head>\
                      <meta charset=\"UTF-8\">\
                      <title>Subir archivo</title>\
                   </head>\
                 <body>\
                   <h1>Cargar un pdf</h1>\
                     <form action=\"/cgi-bin/upload.cgi\" method=\"post\" enctype=\"multipart/form-data\">\
                     <input type=\"file\" name=\"file\" required>\
                     <input type=\"submit\" value=\"Procesar documento\">\
                    </form>\
                </body>\
              </html>"};

  file = fopen("subir.html", "w");
  if(file == NULL) return;

  fprintf(file, "%s\n", str);
  fclose(file);
}
