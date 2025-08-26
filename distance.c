
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float distance(float x1,float y1,float x2,float y2) {
	return pow(((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)),.5);
	}

int main (void) {

float length = 0;

length += distance(12,10,258,141);
length += distance(258,141,205,261);
length += distance(205,261,132,147);
length += distance(132,147,19,275);

length /= 72;
printf("length = %f",length);
return 0;
}
