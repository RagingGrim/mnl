#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../build/mnl.h"

void vvector_test(){
     p_vvector vect = vvector_init();
     int a = 0;
     int b = 1;
     int c = 2;
     vvector_push(vect, &a);
     vvector_push(vect, &b);
     vvector_push(vect, &c);
     for(size_t i = 0 ; i < vect->elements ; i++)
          assert(i == *(int *)vvector_at(vect, i));
     vvector_pop(vect);
     for(size_t i = 0 ; i < vect->elements ; i++)
          assert(i == *(int *)vvector_at(vect, i));
     vvector_delete(vect, 0);
     assert(1 == *(int *)vvector_at(vect, 0));
     vvector_free(vect);
}

int main(){
     vvector_test();

     return 0;
}
