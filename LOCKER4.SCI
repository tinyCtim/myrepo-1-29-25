
# A high school has a new principal. On his first day he had his students
# perform an opening day ceremony. There are 1000 lockers and 1000
# students in the school. The principal asks the first student to go to
# every locker and open it. Then he asks the second student to go to every
# second locker (even #) and close it. He has the third student go to
# every third locker and open it if it's closed and close it if it's open.
# He has the fourth student do this to every fourth locker and so on.
# After the process is completed with the 1000th student how many lockers
# are open?

# added command tail support
 
locker(n,s) int n;char *s;
{
 printf("\nUsage: locker(n,string)\n");
 printf("%clocker4.sci - 7/15/25 - lrb%c",10,10);
 # locker array, index, locker number, total
 printf("\n%s\n\n",s);
 if(!strncmp(s,"help",4))printf("\nload and run help.sci\n");
 int la[1000],i,ln,tot;
 ln=1;
 while(ln<=n){
  i=ln;
  while(i<=n){
   la[i]=1-la[i]; # toggle locker state
   i=i+ln;
   }
  ln=ln+1;
  }
 i=1;
 while(i<=n){
  if(la[i]==1){ # if open, display and tally
   printf("%d ",i);
   tot=tot+1;
   }
  i=i+1;
  }
 printf("%c%c%d",10,10,tot);
 puts(" lockers are open.");
 }

