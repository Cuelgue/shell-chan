#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>


#define MAX_BUFFER  512

typedef struct {
  char buff[MAX_BUFFER];
  char c;
  int pos;
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



int main()
{
  bool vf = true;
  input_t input = {0}: 

  while (vf) {
     input.c = getche();
    (void)c;
  }


 
  return 0;
}
