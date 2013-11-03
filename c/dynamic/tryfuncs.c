#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h> 

int main(int argc, char** argv)
{
   int rc = 0;
   void* handle; 
   int (*f) (int);
   double (*g) (double);

   handle = dlopen("./libfuncs.so", RTLD_LAZY);
   if (!handle) {
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
      goto exit;
   }
   dlerror();    /* Clear any existing error */
   f = dlsym(handle, "f");
   g = dlsym(handle, "g");

   int j = 17;
   double x = 3.0;
   printf("f(%d) = %d\n", j, f(j));
   printf("g(%f) = %f\n", x, g(x));

exit:
   return rc;
}
