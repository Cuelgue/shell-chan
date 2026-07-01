#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>


#define MAX_BUFFER  512
#define MAX_TOK  64
#define T_DEL  127
#define T_BS  8

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

/* Cuando apreto la tecla back space
*me la tima como la tecla de borrado.
*esta funcion imprime la tecla bs, un espacio
*y de nuevo la tecla bs. dando la senciacion de borrado
*como en cualquier otra shell */
void print_bs()
{
  printf("%c",T_BS);
  printf(" ");
  printf("%c",T_BS);
}

void cargar_buffer(input_t *input)
{
  input->c = getch();
  if (input->cant < MAX_BUFFER - 1 && input->c != '\n' && input->c != T_DEL) {
    input->buffer[input->cant] = input->c;       
    input->cant++;
    input->buffer[input->cant] = '\0';
  }
}

int main()
{
  bool vf = false;
  input_t input = {0}; 
  while (!vf) {
    printf("chan > ");
    input.c = 0;
    while (!vf && input.c != '\n'){      
      cargar_buffer(&input);
        if (input.c == '\n') {
          char *token[MAX_TOK];
          int cant = 0;
          separar_token(input.buffer,token,&cant);
          ejecutar_comando(token,cant,&vf);
          input.cant = 0;
        }
      if ((input.c == T_BS || input.c == T_DEL)) {
        if (input.cant > 0) {
          input.cant--;
          print_bs();
        }
      }
      printf("%c",input.c);    
    }

  }
  return 0;
}
