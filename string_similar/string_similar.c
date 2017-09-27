#include <stdio.h>
#define A_LEN 10
#define B_LEN 10
int result_save[A_LEN][B_LEN];

int similar_distance(char *str_a, int a_begin, int a_end, char *str_b, int b_begin, int b_end);

void init()
{
	int i=0, j=0;
	for (i=0; i<A_LEN; i++)
	{
		for (j=0; j<B_LEN; j++)
		{
			result_save[i][j] = -1;
		}
	}	
}
int similar_distance(char *str_a, int a_begin, int a_end, char *str_b, int b_begin, int b_end)
{
	printf("a_begin[%d], b_begin[%d]\n", a_begin, b_begin);
	if ( a_begin > a_end )     // A已经遍历完了
	{
		if (b_begin > b_end )  // B 也完了, 则返回0
			return 0;
		else                   // B 未完, 则返回B剩余的
			return b_end - b_begin + 1;
	}
	
	if ( b_begin > b_end )    // B已经完了
	{
		if (a_begin > a_end)
			return 0;
		else
			return a_end - a_begin +1;
	}
	
	int result = result_save[a_begin][b_begin];
	if ( result != -1)
	{
		printf("get result_save[%d][%d]=%d\n", a_begin, b_begin, result);
		return result;
	}
	char ch_a = *( str_a + a_begin);
	char ch_b = *( str_b + b_begin );
	if (  ch_a ==  ch_b )
	{
		 printf("char equal:%c\n", ch_a);
		 int result = similar_distance(str_a, a_begin+1, a_end, str_b, b_begin+1, b_end);
		 printf("result[%d][%d]=%d\n", a_begin, b_begin, result);
		 result_save[a_begin][b_begin] = result;
		 return result;
	}
	else
	{
		int r1 = similar_distance(str_a, a_begin, a_end, str_b, b_begin+1, b_end);
		int r2 = similar_distance(str_a, a_begin+1, a_end, str_b, b_begin, b_end);
		int r3 = similar_distance(str_a, a_begin+1, a_end, str_b, b_begin+1, b_end);
		int min = r1 < r2? r1:r2;
		int min2 = min < r3? min: r3;
		printf("r1[%d],r2[%d],r3[%d], min[%d]\n", r1, r2, r3, min2);
		result_save[a_begin][b_begin] = min2;
	}
	
}

int main(int argc, char *argv[])
{	
	char a[A_LEN]="qwertyuio";
	char b[B_LEN]="qwaetyujk";
	init();
	int result = similar_distance(a, 0, A_LEN, b, 0, B_LEN);
	printf("finaly result:%d\n", result);
	return 0;
}