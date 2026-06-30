#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>


#define MAX_BUFFER  512
#define MAX_TOK  64

typedef struct {
  char buffer[MAX_BUFFER];
  char c;
  int cant;
} input_t;



/* autor de la funcion:
 * https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
 */
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
//Este probablemente noi lo use, porque me imprime todas las teclas,
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

bool exit_shell()
{
  return true;
}

void ejecutar_comando(char **t, int n, bool *vf)
{
  //TODO: Implementar.
  (void) n;


 if (strcmp(t[0],"exit") == 0) {
  *vf = true;  
}

  }

void separar_token(char *b, char **token, int *n )
{
  char *tok;
  tok = strtok(b," " );

  int i = 0;
  while (tok  != NULL && i < MAX_TOK) {
    token[i] = tok;
    i++;
    tok = strtok(NULL," ");
  }
  *n = i;

} 


int main()
{
  bool vf = false;
  input_t input = {0}; 
  (void)vf;
    while (!vf) {
      input.c = getche();
      if (input.cant < MAX_BUFFER - 1 && input.c != '\n') {
        input.buffer[input.cant] = input.c;       
        input.cant++;
        input.buffer[input.cant] = '\0';
      } else if (input.c == '\n') {
        char *token[MAX_TOK];
        int cant = 0;
        separar_token(input.buffer,token,&cant);
        ejecutar_comando(token,cant,&vf);
        input.cant = 0;
      }
    }


 
  return 0;
}
