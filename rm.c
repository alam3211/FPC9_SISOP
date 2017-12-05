#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;

  printf(2,"argc : %d argv: %s %s \n", argc, argv[0], argv[1]);

  if(argc < 2){
    printf(2, "Usage: rm files...!\n");
    exit();
  }

  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){
      printf(2, "rm: %s failed to delete\n", argv[i]);
      break;
    }
  }
  exit();
}

/*
int main()
{
   int status;
   char file_name[25];
 
   printf(1,"Enter the name of file you wish to delete\n");
   gets(file_name,1);
 
   status = remove(file_name);
 
   if( status == 0 )
      printf(1,"%s file deleted successfully.\n",file_name);
   else
   {
      printf(1,"Unable to delete the file\n");
      //perror("Error");
   }
 
   return 0;
}
*/