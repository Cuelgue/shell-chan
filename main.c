#include <stdio.h>
#include <stdbool.h>
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



void cargar_buffer(input_t *input, bool vf)
{
  while (!vf && input->c != '\n'){
    input->c = getchar();
    if (input->cant < MAX_BUFFER - 1 && input->c != '\n' && input->c != T_DEL) {
      input->buffer[input->cant] = input->c;       
      input->cant++;
      input->buffer[input->cant] = '\0';
    }
    if ((input->c == T_BS || input->c == T_DEL) && input->cant > 0) {
      input->cant--;
    }      
  }
}

void procesar_buffer(input_t *input, bool *vf)
{
  if (input->c == '\n') {
    char *token[MAX_TOK];
    int cant = 0;
    separar_token(input->buffer,token,&cant);
    ejecutar_comando(token,cant,vf);
    input->cant = 0;
  }
}

int main()
{
  bool vf = false;
  input_t input = {0}; 
  while (!vf) {
    printf("chan > ");
    input.c = 0;
    
	cargar_buffer(&input,vf);
        procesar_buffer(&input,&vf);
    
      
    

  }
  return 0;
}
