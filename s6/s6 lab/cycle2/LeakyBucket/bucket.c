#include <stdio.h>
int main() {
  int n, bsize, in, out, store = 0;

  printf("Enter the bucket size, outgoing rate and number of inputs: ");
  
  scanf("%d %d %d", &bsize, &out, &n);

  while(n != 0) {
    
    printf("Enter the incoming packet size: ");
    scanf("%d", &in);

    if (in <= (bsize - store)) {
      store += in;
      printf("Before outgoing, bucket size %d occupied out of %d\n", store, bsize);
    } else {
      printf("Incoming packets %d discarded out of %d\n", in - (bsize - store), in);
      store = bsize;
      printf("Before outgoing, bucket size %d occupied out of %d\n", store, bsize);
    }

    if (store > out) {
      store -= out;
    } else {
      store = 0;
    }

    printf("After outgoing, bucket size %d occupied out of %d\n", store, bsize);
    n--;
  }
  return 0;
}
