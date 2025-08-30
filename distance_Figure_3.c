#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// see http://primepuzzle.com/not.just.tiny.c/Figure_3.png - 8/30/25 - lrb

float distance(float x1,float y1,float x2,float y2) {
	return pow(((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)),.5);
	}

int main (void) {

float length = 0;

length += distance(6,7,-1,8);
length += distance(-1,8,7,6);
length += distance(7,6,8,3);
length += distance(8,3,0,5);
length += distance(0,5,4,2);

printf("length = %f",length);
return 0;

}
