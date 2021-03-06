/*
@author		Heedong Arkiny Lee
@date		07142014
@git		https://github.com/arkiny/SGA-Learning-Heedong

// 引薦拭つつつつつつつつつつつつつつつつつつつつつつ

杉球津 酔渋.... 昔舛拝 呪 蒸陥..

沙昔税 軒益研 陥獣廃腰 幻級奄
char *pstr[4] = {};

得 16鯵, 沓棋 壕舛

1虞錘球 [] [] [] [] [] [] [] []			char* pQuarterFinal[8]
2虞錘球   []    []   []    []				char* SemiFinal[4]
3虞錘球       []       []					char* Final[2]
衣渋              []						char* pWinner
*/

/*
Design
main(){
	main精 置社鉢
	置段 窒径引
	汽戚展 戚疑幻 叔獣
	????託板拭 汽戚展 戚疑幻聖 是廃 敗呪研 舛税拝呪 赤聖猿????
}

Controller(){
	幻鉦 叔霜旋生稽 r研 搭背辞 鋼差拝 井酔 五昔拭辞 惟績採歳聖
	皐人辞 隔聖呪 赤畏走幻... 神潅精 食奄辞 持繰
}

Model(庚切伸, 庚切伸){
	庚切伸聖 閤焼辞, 背雁 庚切伸税 掩戚税 箭鋼幻鏑 
	砧得晦軒 広嬢辞 沓棋生稽 嗣焼 宜形捜
}

view(楳慶, 窒径姐呪){
	昔斗凪戚什 窒径
	昔斗凪戚什澗 楳慶引 益 姐呪研 閤焼辞 授託企稽 窒径廃陥
	???? 至綬域至生稽 \t 鯵呪研 坦軒拝呪 赤聖猿 ????
	ex) 8悪拭識 \t 1腰, 4悪拭識 \t 2腰, 衣渋拭識 \t 4腰
		酔渋切澗\t 8腰 坦軒背醤馬形蟹?
	(析舘 背雁採歳 持繰)
}
*/


#include <stdio.h> // printf()
#include <stdlib.h> // srand(), rand(), system()
#include <time.h> // time()

// Prototype
// Engine
void quarterFinalGame(char** inputArray, char** outputArray);
void semifinalGame(char** inputArray, char** outputArray);
void finalGame(char** inputArray, char** outputString);
void randomize(char* input[], char* output[], int size);

// View
void toString(char** input, int size);
void print_signature();

// Main Function
void main(){
	// 痕呪 段奄鉢
	// Initialize the Country names
	// Initial DataBase
	char* pQuarterFinal[8] = { "Brazil", "Germany", 
								"France", "Spain",
								"Korea", "U.S.A", 
								"Ghana", "Argentina" };
	char* pSemiFinal[4] = {};
	char* pFinal[2] = {};
	char* pWinner[1] = {};
	
	// 沓棋 獣球 段奄鉢
	// Seeding the random function
	srand(time(NULL));

	// Interface Initialization
	print_signature();
	toString(pQuarterFinal, 8);

	// Game Engine :D
	// 惟績 叔楳 採歳戚 叔霜旋昔 窒径猿走 眼雁
	quarterFinalGame(pQuarterFinal, pSemiFinal);
	semifinalGame(pSemiFinal, pFinal);
	finalGame(pFinal, pWinner);

	system("pause");
} // main()

// 8悪 井奄 叔獣
// 陥製 井奄稽 葵聖 角移爽奄 是背 output parameter蝕獣 亜走壱 赤嬢醤 廃陥.
// @param char** inputArray		脊径閤精 厩亜 庚切伸(8鯵)
// @param char** outputArray	宜形匝 厩亜 庚切伸(4鯵)
void quarterFinalGame(char** inputArray, char** outputArray){
	randomize(inputArray, outputArray, 4);	
	toString(outputArray, 4);
} // quarterFinalGame()

// 層衣渋 井奄 叔獣
// 陥製 井奄稽 葵聖 角移爽奄 是背 output parameter蝕獣 亜走壱 赤嬢醤 廃陥.
// @param char** inputArray		脊径閤精 厩亜 庚切伸(4鯵)
// @param char** outputArray	宜形匝 厩亜 庚切伸(2鯵)
void semifinalGame(char** inputArray, char** outputArray){
	randomize(inputArray, outputArray, 2);
	toString(outputArray, 2);
} // semifinalGame()

// 衣渋 井奄 叔獣
// 陥製 井奄稽 葵聖 角移爽奄 是背 output parameter蝕獣 亜走壱 赤嬢醤 廃陥.
// 析鋼 庚切伸稽 output葵聖 亜霜呪亀 赤生蟹, 敗呪税 搭析失聖 是背 壕伸 莫縦生稽
// 宜形爽奄稽 衣舛
// @param char** inputArray		脊径閤精 厩亜 庚切伸(2鯵)
// @param char** outputArray	宜形匝 厩亜 庚切伸(1鯵)
void finalGame(char** inputArray, char** outputArray){
	randomize(inputArray, outputArray, 1);
	toString(outputArray, 1);
} // finalGame()

// 薄 惟績税 肺宿採歳
// 壕伸引 宜形匝 紫戚綜研 閤焼, 焼数撚 壕伸拭 限蓄嬢 宜形層陥.
// 巷繕闇 井奄澗 蒋拭辞 採斗 授辞企稽 2得梢 設虞辞 叔獣馬悟,
// 魚虞辞 酔軒亜 閤聖 呪 赤澗 壕伸 爽社葵精
// 宜形匝 紫戚綜澗 巷繕闇 穿 壕伸税 1/2戚糠稽,
// 沓棋葵 % 2 + (2 * i)亜 吉陥. (2得掻 廃得幻 臣虞亜糠稽)
// @param char* input[] 井奄研 叔獣拝 庚切伸
// @param char* output[] 井奄 衣引研 脊径拝 庚切伸
// @param int size 井奄 衣引葵戚 脊径吃 output税 紫戚綜
// @warning ouput.length()澗 input.length()税 1/2紫戚綜食醤 廃陥.
void randomize(char* input[], char* output[], int size){
	int pick = 0;
	for (int i = 0; i < size; ++i){
		pick = rand() % 2 + (2 * i);
		output[i] = input[pick];
	}
}

// 窒径 坦軒澗 戚員拭辞 乞砧 坦軒廃陥.
// @param char*input[] 窒径拝 庚切伸
// @param int size	窒径拝 庚切伸税 紫戚綜
void toString(char* input[], int size){
	switch (size)
	{
	case 8:
		printf("== 8悪 井奄 == \n", size);
		break;
	case 4:
		printf("== 層衣渋 井奄 == \n", size);
		break;
	case 2:
		printf("== 衣渋 井奄 == \n", size);
		break;
	case 1:
		printf("== 衣渋 井奄 衣引 == \n", size);
		break;
	default:
		break;
	} // end switch

	for (int i = 0; i < size; i++){
		// 2得原陥 vs研 細食醤 馬糠稽, 爽社葵税 蟹袴走亜 1戚 吃凶, vs 窒径
		if (i % 2 == 1){ 
			printf(" vs ");
		}
		else{
			// 焼諌匡 益撹 牒 蟹刊奄遂 採硲 窒径
			printf("��");
		}
		printf("%s", input[i]);
	} // end for

	printf("��\n\n");
}

// 辞誤 窒径
void print_signature(){
	printf("戚費疑\n");
	printf("SGA51A\n");
	printf("07142014 引薦\n");
	printf("============================================================\n");
	printf("2120鰍 廃厩 杉球津 衣引 - (叔楳拝凶原陥 衣引亜 郊解艦陥)\n\n");
}