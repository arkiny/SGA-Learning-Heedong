/*
	2託 壕伸 庚切伸 匂昔斗
*/

#include <stdio.h> // printf()
int main()
{
	char *pstr[4] = {};
	
	char Brazil[] = "Brazil";
	char Holland[] = "Holland";
	char Germany[] = "Germany";
	char Argentina[] = "Argentina";

	pstr[0] = Brazil;
	pstr[1] = Holland;
	pstr[2] = Germany;
	pstr[3] = Argentina;

	printf("%s\n", pstr[1]);

	char USA[] = "USA";

	pstr[1] = USA;

	printf("%s\n", pstr[1]);

	return 0;
}


// 引薦拭つつつつつつつつつつつつつつつつつつつつつつ
/*
	杉球津 酔渋.... 昔舛拝 呪 蒸陥..

	沙昔税 軒益研 陥獣廃腰 幻級奄
	char *pstr[4] = {};

	得 16鯵, 沓棋 壕舛

	1虞錘球 [] [] [] [] [] [] [] []		char* pQuarterFinal[4]
	2虞錘球   []    []   []    []			char* SemiFinal[2]
	3虞錘球       []       []				char* Final[2]
	衣渋              []					char* pWinner
*/