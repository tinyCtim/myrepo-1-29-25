#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/*

This program factors a number you enter and displays the factors.

2/4/18 1/29,30/20 6/4/23 7/27/25 - converted from factor.tc - added
elapsed time

*/

int main() {
 printf("\nfactor.c - 7/27/25 - lrb\n");
 
 clock_t start_time, end_time;
 double cpu_time_used;
 
 int f,s,p[3512],idx,j,pc,sw;char v;
 p[0]=2;p[1]=3;p[2]=5;idx=2;pc=7;
 
 while(1) {
  printf("\nEnter a number to factor (<=32767) "); 
  scanf("%d", &f);
  if (f<=32767) break;
  }

 printf("\nVerbose mode (show prime generation) (y or Y) ? : "); 
 scanf(" %c", &v); // note space before %c to consume leftover newline
 if ((v=='y')||(v=='Y')) printf("\n");

 // Record the starting clock time
 start_time = clock();

 while (idx<3511) { // load primes
  sw=0;
  j=0;
  if (pc>f) break;
  while (p[j]<p[idx]) {
   if (pc%p[j]==0) {sw=1;break;}
   j=j+1;
   }
  if(sw==0){
   idx=idx+1;
   p[idx]=pc;
   if ((v=='y')||(v=='Y')) {
    printf("%d ", pc);
    if (idx%30==0) printf("\n");
    }
   }
  pc=pc+2;
  }
  
 printf("\n\n%d = ",f);
 s=0;
 int ans;ans=1;
 int fs=f;
  
 while (1) { // factor number
  if (f%p[s]==0) {
   printf("%d ",p[s]);
   ans*=p[s];
   if (ans==fs) break;
   f/=p[s];
   }
  else {
   s=s+1;
   }
  }

  end_time=clock();
  // Calculate the elapsed CPU time
  // CLOCKS_PER_SEC is a macro that represents the number of clock ticks per second
  cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("\n\nElapsed CPU time: %f seconds\n", cpu_time_used);
  return 0;
 }

