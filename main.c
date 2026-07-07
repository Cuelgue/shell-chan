#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_BUFFER  512
#define MAX_TOK  64
#define T_DEL  127
#define T_BS  8

typedef struct {
  char buffer[MAX_BUFFER];
  char c;
  int cant;
} input_t;


typedef struct {
  char *tok[MAX_TOK];
  int cant;
} token_t;


bool exit_shell()
{
  return true;
}

bool ejecutar_comando(char **t, int n, bool *vf)
{
  //TODO: Implementar.
  (void) n;
  bool ejecuto = false;

  if (strcmp(t[0],"exit") == 0) {
    *vf = true;
    ejecuto = true;
  }
  return ejecuto;
}

void imp_token(token_t t)
{
  for (int i = 0; i < t.cant; i++) {
    printf("%s ",t.tok[i]);
}
}

void ejecutar_programa(token_t t)
{
  pid_t p = fork();
  // Encontramos el problema, todo tenemos el path del usuario local.
  printf("%s\n",getenv("PATH"));
  if (p < 0) {
    fprintf(stderr,"FORK ERROR: No se pudo crear el proceso\n");
    exit(0);
  } else if (p == 0) {
    // El proceso hijo ejecuta si existe el programa.
    //    int n = execvp(t.tok[0],t.tok);
    char *l[] = {"ls",NULL};
    int n = execvp("ls",l);
    if (n == -1) {
    printf("execl returned! errno is [%d]\n",errno);
    perror("The error message is :");
    }
    printf("%s: Orden no encontrada %d\n",t.tok[0],n);
    exit(errno);
  } else waitpid(p,NULL,0); //El proceso padre espera a que el proceso hijo termine.
}


void separar_token(char *b, char **token, const char *delim, int *n )
{
  char *tok;
  tok = strtok(b,delim );

  int i = 0;
  while (tok  != NULL && i < MAX_TOK) {
    token[i] = tok;
    i++;
    tok = strtok(NULL,delim);
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

void init_array_tokens(token_t *t, char *b, const char *delim)
{
  t->cant = 0;
  separar_token(b,t->tok,delim,&t->cant);
  t->tok[t->cant] = NULL;
  t->cant += 1;
}

void procesar_buffer(input_t *input, bool *vf)
{
  if (input->c == '\n') {
    token_t t = {0};
    init_array_tokens(&t,input->buffer," ");
    if (!ejecutar_comando(t.tok,t.cant,vf)) ejecutar_programa(t);
    input->cant = 0;
  }
}


void loop(input_t *input, token_t p)
{
  bool vf = false;
  (void)p;

  while (!vf) {
    printf("[>_<]: ");
    input->c = 0;
    cargar_buffer(input,vf);
    procesar_buffer(input,&vf);
    }
}


int main()
{
  char *path = getenv("PATH");
  token_t paths = {0};
  init_array_tokens(&paths,path,":");
  input_t input = {0};
  loop(&input,paths);
  return 0;
}
