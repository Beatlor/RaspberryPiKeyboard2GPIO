#include <stdio.h> 
#include <string.h> 

int main()
{
  char buf[BUFSIZ];
  char *p;
  
  printf ("Please enter a line of text, max %d characters\n", sizeof(buf));
  
  if (fgets(buf, sizeof(buf), stdin) != NULL)
  {
    printf ("Thank you, you entered >%s<\n", buf);
    
    /*
     *  Now test for, and remove that newline character
     */
    if ((p = strchr(buf, '\n')) != NULL)
      *p = '\0';
      
    printf ("And now it's >%s<\n", buf);
  }
  
  return 0;
}

