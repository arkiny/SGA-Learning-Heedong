/*
	繕闇 尻至切 ( 誌牌 尻至切 )
	繕闇 ? (凧) 縦1 : (暗憎) 縦2
*/

#include <stdio.h>
int main(){
	int A = 7, B = 3;
	int nResult = 0;
	
	nResult = A < B ? A : B; // 曽曽 彰陥眺 ぞぞぞぞぞぞぞ
	printf("result = %d\n", nResult);

	/*
		scanf研 醗遂馬食
		"砧 呪研 脊径 : __ __"
		砧 呪掻 笛 呪研 達焼鎧奄
	*/

	// input variables init
	int nA = 0, nB = 0;
	// result variables
	int nResult_Max = 0;

	// Scanning part
	printf("砧 呪研 脊径 : \n");
	scanf("%d %d", &nA, &nB); // 嬢球傾什稽 閤澗杏 蹟走 源切 塊肖

	// Compute and return part
	nResult_Max = nA > nB ? nA : nB;
	printf("希 笛呪澗 =  %d\n", nResult_Max);
	return 0;
}