/*
	@author		Heedong Arkiny Lee
	@date		07182014
	@git		https://github.com/arkiny/SGA-Learning-Heedong

	引薦 ]] Enemy研 己拭辞 戚疑馬奄
	けけけけけけけけけけけけけけ
	けけけけけけけけけけけけけけ
	けけけ政けけけけけけけけけけ
	けけけけけけけけけけけけけけ
	けけけけけけけけけけけけけけ
	けけけけけけけけけ展けけけけ
	けけけけけけけけけけけけけけ
	けけけけけけけけけけけけけけ
	けけけけけけけけ鯉けけけけけ
	けけけけけけけけけけけけけけ
	けけけけけけけけけけけけけけ
	けけけけけけけけけけけけけけ

	Enemy 姥繕端税 start 是帖拭辞 Enemy 獣拙
	Dest 是帖研 蓄亜稽 隔壱
	析舛獣娃 原陥 鯉旋走稽 戚疑馬奄
	
	戚暗 Union Find 潤辞 五戚綜 幻級壱 鯉旋是帖 達焼亜奄 背亀 吃暗 旭精汽

	_sleep(1000) 1000 = 鉦 1段
*/

//置段 巨切昔 ->
//struct point
// point澗 哀呪 赤澗 陥献 匂昔闘級聖 匂昔斗稽 亜走壱 赤製
// 
//struct cctv
//struct thief
//struct map
//function
//void mapload (random terrain loading) 
// -> int[][]稽 0精 搭引 災引, 1精 搭引 亜管
// -> load 板拭 壱舛吉  Starting Point拭辞 
//				壱舛吉  Target Point猿走 戚疑亜管廃走 溌昔馬壱 災亜管拝獣拭
//				仙稽漁
//void mapupdate(cctv, thief)
// -> map拭 cctv研 thief(starting point)研 姿形辞, 
// -> 歯 是帖亜 溌舛吃凶原陥
// -> reload 鞠惟懐 敗
//
//bool cango (union find) 
//void update - in the forloop
//bool shortwayfind (bfs b/c undirected graph)
// -
//bool move(point from, point to)


#include <stdio.h>	// printf()
#include <stdlib.h>	// rand(), srand()
#include <time.h>	// time()
#include <math.h>	// sqrt(), pow()

// map滴奄 走舛, 脊径 閤聖呪亀 赤生蟹 析舘 差説背走艦 雌呪稽 走舛
const int MAP_VERTICAL = 18;
const int MAP_HORIZONTAL = 18;

// 展析 展脊 走舛
enum type{movable, not_movable, thief, tower, start, dest, border};
// 掩達奄 AI研 是廃 号狽 走舛
enum direc{right, up, left, down};

// AI走舛
enum pathAI{noAI, turnLeft};

// 走亀 object 竺舛
typedef struct game_map{
	// 己精 point 稲 神崎詮闘人澗 紺鯵税 姥繕戚糠稽
	// 瓜戚 point研 承 琶推澗 蒸聖牛 馬陥
	// (i % MAP_HORIZONTAL)[x疎妊] + ( i/MAP_HORIZONTAL )[y疎妊]
	// 1託据 姥繕稽 幻窮 戚政澗 託板
	// 硝壱軒葬 旋遂聖 繕榎戚蟹原 畷馬惟 馬奄是背辞...び
	int map_point[MAP_VERTICAL * MAP_HORIZONTAL];

	// Random Map 持失
	// random敗呪拭 税背 戚疑 亜管廃 展析引 戚疑 災亜管廃 展析聖 持失廃陥.
	void initmap_ob(){
		for (int i = 0; i < (MAP_VERTICAL * MAP_HORIZONTAL); i++){
			// boardering
			if (i % (MAP_HORIZONTAL) == 0 || i % MAP_HORIZONTAL == MAP_HORIZONTAL - 1
				|| i < MAP_HORIZONTAL || i > (MAP_HORIZONTAL * (MAP_VERTICAL-1))){
				map_point[i] = 1;
			}
			else if (rand() % 100 > 1){
				map_point[i] = 0; 
			}
			else{
				map_point[i] = 1;
			}
		}
	}

	// 益撹 朔己 持失
	void initmap_empty(){
		for (int i = 0; i < (MAP_VERTICAL * MAP_HORIZONTAL); i++){
				map_point[i] = 0;			
		}
	}

	// 背雁 是端 object 竺帖
	// @param int x x疎妊
	// @param int y y疎妊
	// @param int type object 展脊
	void setObject(int x, int y, int type){
		map_point[(x * MAP_HORIZONTAL) + y] = type;
	} 

	// 脊径 閤精 是帖亜 崇送析呪 赤澗 員昔走 溌昔
	// @param int x x疎妊
	// @param int y y疎妊
	bool isMovable(int x, int y){
		return map_point[(x * MAP_HORIZONTAL) + y] == movable
			|| map_point[(x * MAP_HORIZONTAL) + y] == dest
			|| map_point[(x * MAP_HORIZONTAL) + y] == start;
	}

	// 戚疑 災亜管廃 切軒拭澗 ＝聖, 戚疑 亜管廃 切軒拭澗 Λ
	// 託板拭 render己生稽 皐奄穿拭 承 社什
	// 析舘精 砺什闘........澗 節獣 貝淫拭 採禦粕辞 社什幻 害奄澗 杏稽...
	// A*研 class人 Data Structure研 照壕錘 c拭辞 姥薄馬奄拭澗 格巷蟹 哀掩戚 菰陥....
	void printMap(){
		for (int i = 0; i < (MAP_VERTICAL * MAP_HORIZONTAL); i++){
			if (i % MAP_HORIZONTAL == 0){
				printf("\n");
			}
			if (map_point[i] == movable){
				printf("%s", "Λ");
			}
			else if (map_point[i] == not_movable){
				printf("%s", "＝");
			}
			else if (map_point[i] == thief){
				printf("%s", "��");
			}
			else if (map_point[i] == tower){
				printf("%s", "−");
			}
			else if (map_point[i] == start){
				printf("%s", "窒");
			}
			else if (map_point[i] == dest){
				printf("%s", "鯉");
			}
			else{
			}
		}
		printf("\n");
	}
}GAME_MAP;

// 己照拭辞 妊薄拝 神崎詮闘
typedef struct point{
	// 疎妊
	float x, y; 
	// target引 切重引 暗軒研 姥背辞 target戚 切重税 獣醤 照拭 赤澗走
	// 溌昔 馬澗 敗呪
	// @param point *target 展為戚 吃 point 繊
	bool isinRange(point *target, int range){
		// 砧 繊娃税 暗軒亜(杷展壱虞什 舛軒 戚遂) 獣醤 暗軒左陥 拙精亜? 拙生檎 true
		// 拙走 省生檎 false;
		return  this->distanceTo(target) <= range;
	}// is in Range

	// target引 切重引税 暗軒研 姥背辞 宜形爽澗 敗呪
	// @param point *target 暗軒著舛聖 拝 target
	float distanceTo(point *target){
		float a, b;
		// x逐 暗軒 域至
		if (x == target->x){		// 丞楕 収切亜 旭聖凶 0
			a = 0;
		}
		else if (x < target->x){	// this.fX亜 拙聖獣拭 展為税 fX拭辞 this.fX研 鮫
			a = target->x - x;
		}
		else {						// 鋼企析 井酔
			a = x - target->x;
		}// if()

		// y逐 暗軒 域至
		if (y == target->y){		// 丞楕 収切亜 旭聖 凶 0
			b = 0;
		}
		else if (y < target->y){	// this.fY亜 拙聖獣拭 展為税 fY拭辞 fY研 鮫
			b = target->y - y;
		}
		else {						// 鋼企税 井酔
			b = y - target->y;
		} //if()

		// 砧 繊晦軒税 暗軒研 杷展壱虞什税 舛軒狛帳聖 戚遂馬食 域至
		// sqrt(x逐拭辞 砧繊紫戚税 暗軒^2 + y逐拭辞税 砧繊 紫戚税 暗軒^2)
		return  sqrt(pow(a, 2) + pow(b, 2));
	}

	// 脊径閤精 疎妊人 切重戚 旭精 疎妊昔走 溌昔
	// @param point *target 脊径閤精 疎妊
	// @return bool 切重引 疑析廃 疎妊昔走 溌昔
	bool equalTo(point *target){
		return (x == target->x && y == target->y);
	}
}POINT;

typedef struct thief{
	POINT cur_pos; // 薄仙是帖
	POINT destination; // 鯉旋走
	int direction; // 薄仙 遭楳馬澗 号狽 : AI遂
	
	// 掩達奄 AI幻級陥亜 諺敗...
	// 焼原 Graph硝壱軒葬 戚遂背辞 A*蟹 陥�綵再�虞 掩達奄研 背醤拝暗 旭精汽..
	// 巷繕闇 Turn Right研 戚遂馬陥左艦 巷廃生稽 旭精 員聖 孤亀澗 庚薦亜 持沿
	// Graph Structure研 幻級嬢辞 紫遂馬澗 号狛亀 赤畏走幻...
	// 析舘 C澗 格巷 蓄雌鉢 舘域亜 碍焼辞 格巷 災畷馬陥...
	bool one_step_AI(game_map *map_info){
		// base case澗 戚耕 薄仙 匂走芝戚 鯉旋 匂走芝引 疑析拝凶
		if (cur_pos.x == destination.x && cur_pos.y == destination.y){
			// 亀鐸梅聖凶 楳疑聖 紬廃陥
			return true;
		}
		else if (direction == right){
			if (!map_info->isMovable(cur_pos.x, cur_pos.y + 1)){
				direction = direction++;
				this->one_step_AI(map_info);
			}
			else {
				cur_pos.y++;
				return false;
			}// end inner if
		}
		else if (direction == up){
			if (!map_info->isMovable(cur_pos.x-1, cur_pos.y)){
				direction = direction++;
				this->one_step_AI(map_info);
			}
			else {
				cur_pos.x--;
				return false;
			}// end inner if
		}
		else if (direction == left){
			if (!map_info->isMovable(cur_pos.x, cur_pos.y - 1)){
				direction = direction++;
				this->one_step_AI(map_info);
			}
			else {
				cur_pos.y--;
				return false;
			}// end inner if
		}
		else if (direction == down){
			if (!map_info->isMovable(cur_pos.x + 1, cur_pos.y)){
				direction = right;
				this->one_step_AI(map_info);
			}
			else {
				cur_pos.x++;
				return false;
			}// end inner if
		}
		else {
			printf("戚疑 拝呪 蒸柔艦陥.\n");
		}// end outer if
	}

	// 益撹 朔己析凶 100遁湿闘 疑拙馬澗 硝壱軒葬
	// 切奄 疎妊研 鯉旋走 疎妊拭 限仲 蟹娃陥.
	bool one_step_noAI(game_map *map_info){
		if (cur_pos.x == destination.x && cur_pos.y == destination.y){
			printf("亀杵 : 纏窒!\n");
			// 亀鐸梅聖凶 楳疑聖 紬廃陥
			return true;
		}
		// 曽楳疑
		else if (cur_pos.x < destination.x && map_info->isMovable(cur_pos.x + 1, cur_pos.y)){
			cur_pos.x++;
			return false;
		}
		else if (cur_pos.x > destination.x&& map_info->isMovable(cur_pos.x - 1, cur_pos.y)){
			cur_pos.x--;
			return false;
		} // 胡煽 曽楳疑 曽戟
		// 半楳疑
		else if (cur_pos.y < destination.y&& map_info->isMovable(cur_pos.x, cur_pos.y + 1)){
			cur_pos.y++;
			return false;
		}
		else if (cur_pos.y > destination.y&& map_info->isMovable(cur_pos.x, cur_pos.y - 1)){
			cur_pos.y--;
			return false;
		} // 胡煽 半楳疑 曽戟		
		else {
			printf("売... 井茸 蒋生稽 含形亜陥艦...\n");
			return true;
		}
	}
} THIEF;

// 叔精 益撹 cctv亜 焼艦虞 亀杵聖 降胃馬檎 魚虞亜澗 稽鎖 ...
typedef struct cctv{
	POINT cur_pos;		// 薄仙是帖
	POINT target_pos;	// 鯉妊 是帖
	int vision;			// 獣醤骨是

	// 展為是帖 穣汽戚闘
	// @param point target 展為税 是帖
	void update_Target_pos(POINT *target){
		target_pos.x = target->x;
		target_pos.y = target->y;
	}

	// 益撹 朔己析凶 100遁湿闘 疑拙馬澗 硝壱軒葬
	// 切奄 疎妊研 鯉旋走 疎妊拭 限仲 蟹娃陥.
	// 添発精 舌蕉弘拭 姥背閤走 省壱, 舌蕉弘聖 採呪檎辞 崇送昔陥.
	// 亀杵引澗 陥牽惟 企唖識 崇送績亀 亜管
	bool persuit(POINT *target){
		// 展為 是帖 呪舛, 薄仙 展為税 是帖研 閤焼辞 切重戚 亜走壱 赤澗 展為税 是帖研 呪舛廃陥.
		this->update_Target_pos(target);
		// BaseCase 誤掻梅聖凶税 崇送績
		if (cur_pos.x == target_pos.x && cur_pos.y == target_pos.y){
			// 誤掻梅聖凶 楳疑聖 紬廃陥
			return true;
		}
		// 企唖楳疑
		else if (cur_pos.x < target_pos.x && cur_pos.y < target_pos.y){
			cur_pos.x++;
			cur_pos.y++;
			return false;
		}
		else if (cur_pos.x > target_pos.x && cur_pos.y > target_pos.y){
			cur_pos.x--;
			cur_pos.y--;
			return false;
		} // 企唖 楳疑 曽戟
		// 戚耕 是拭辞 陥献 井酔澗 陥晒生糠稽 y蟹 x亜 旭聖獣澗 辛芝拭 照隔嬢操亀吃究
		// 曽楳疑
		else if (cur_pos.x < target_pos.x){
			cur_pos.x++;
			return false;
		}
		else if (cur_pos.x > target_pos.x){
			cur_pos.x--;
			return false;
		} // 胡煽 曽楳疑 曽戟
		// 半楳疑
		else if (cur_pos.y < target_pos.y){
			cur_pos.y++;
			return false;
		}
		else if (cur_pos.y > target_pos.y){
			cur_pos.y--;
			return false;
		} // 胡煽 半楳疑 曽戟		
		else {
			printf("戚疑 拝呪 蒸柔艦陥.\n");
			return true;
		}
	}
} CCTV;

// prototype
bool mapUpdate(GAME_MAP *new_map, THIEF *player, CCTV *watcher, int *type);
void mapLoading(GAME_MAP *new_map, THIEF *player, CCTV *watcher, int *type);
void objectLoading(THIEF *player, CCTV *watcher, int *type);
void printUI();
void gameload(GAME_MAP *new_map, THIEF *player, CCTV *watcher, int *type);
int mainMenu();
void print_signature();

// global variable
// 据掘澗 戚係惟 馬檎 照鞠澗汽, 析舘 舘析引薦 畷税失聖 是背 鉱生稽 鮫


void main(){
	// seeding
	srand(time(NULL));

	// main menu遂
	int type = -1;

	// 惟績 曽戟 flag
	bool arrived = false;

	// Game map
	GAME_MAP new_map;

	// Game object
	THIEF player;
	CCTV watcher;

	// 板拭 沓棋坦軒 敗呪
	
	// main_menu loading
	type = mainMenu();

	// main menu拭辞 識澱廃 惟績稽球	///////////////////////////
	// 託板 UserInterface稽 薪移亀 吃究
	switch (type)
	{
	case 1:
	case 2:
	case 3:
		gameload(&new_map, &player, &watcher, &type);
		break;
	case 4:
		printf("曽戟杯艦陥.\n");
		return;
		break;
	default:
		break;
	}
	//////////////////////////////////////////////////////////.

	system("cls");
	new_map.printMap();
	printf("己 持失 貢, object 持失刃戟. \n 獣拙杯艦陥.\n");
	system("pause");
	system("cls");

	while (arrived!=true){
		arrived = mapUpdate(&new_map, &player, &watcher, &type);		// update
		printUI();														// UI 窒径
		new_map.printMap();												// render map
		_sleep(500);													
		if (arrived){
			printf("惟績戚 刃戟鞠醸柔艦陥.\n");
			system("pause");
		}
		system("cls");
	}
}

// object級税 置段 痕呪研 閤焼辞 object研 獣拙馬澗 敗呪
// 沓棋生稽 神崎詮闘級税 是帖研 繕舛廃陥.
// 暁廃 五敢 辛芝拭 魚虞 井茸税 獣醤 蝕獣 繕舛廃陥.
// @param THIEF *player 亀杵
// @param CCTV *watcher 井茸
// @param int *option 五昔五敢拭辞 識澱廃 辛芝
void objectLoading(THIEF *player, CCTV *watcher, int *option){
	player->cur_pos = { rand() % MAP_VERTICAL, rand() % MAP_HORIZONTAL };
	player->destination = { rand() % MAP_VERTICAL, rand() % MAP_HORIZONTAL };
	player->direction = right;
	watcher->cur_pos = { rand() % MAP_VERTICAL, rand() % MAP_HORIZONTAL };
	if (*option == 1 || *option == 3){
		watcher->vision = 5;
	}
	else {
		watcher->vision = 10;
	}
}

// 段奄鉢吉 神崎詮闘級聖 置段 稽漁馬澗 敗呪
// 辛芝拭 魚虞 己戚 含虞遭陥.
// 1, 2腰 辛芝精 朔己, 3腰 辛芝精 舌蕉弘戚 鹿昔 己聖 稽漁廃陥.
// @param GAME_MAP *new_map 己舛左研 煽舌拝 痕呪 爽社
// @param THIEF *player 亀杵
// @param CCTV *watcher 井茸
// @param int *option 五昔五敢拭辞 識澱廃 辛芝
void mapLoading(GAME_MAP *new_map, THIEF *player, CCTV *watcher, int *option){
	// 辛芝拭 魚献 己 段奄鉢
	if (*option == 1 || *option == 2){
		new_map->initmap_empty();
	}
	else if (*option == 3){
		new_map->initmap_ob();
	}
	// 己拭 神崎詮闘 舛左 脊径
	new_map->setObject(player->cur_pos.x, player->cur_pos.y, thief);
	new_map->setObject(player->destination.x, player->destination.y, dest);
	new_map->setObject(watcher->cur_pos.x, watcher->cur_pos.y, tower);	
}

// 覗傾績, 箸精 崇送績原陥 己舛左研 穣汽戚闘背爽澗 敗呪
// 辛芝拭 魚虞 崇送績戚 含虞遭陥.
// 1, 3腰 辛芝精 井茸戚 亀杵聖 降胃馬檎 惟績神獄
// 2腰 辛芝精 井茸戚 亀杵拭惟 陥亜亜辞 端匂馬檎 惟績神獄
// @param GAME_MAP *new_map 己舛左研 煽舌拝 痕呪 爽社
// @param THIEF *player 亀杵
// @param CCTV *watcher 井茸
// @param int *option 五昔五敢拭辞 識澱廃 辛芝
bool mapUpdate(GAME_MAP *new_map, THIEF *player, CCTV *watcher, int *option){
	// 惟績戚 魁概澗走 軒渡拝 痕呪
	bool static ret = false;

	// 薄仙 亀杵税 是帖澗 陥獣 崇送析呪 赤澗 展析稽 郊蚊層陥.
	new_map->setObject(player->cur_pos.x, player->cur_pos.y, movable);

	// 幻鉦 1,2腰(掩達奄 AI亜 蒸澗 辛芝)昔 井酔 背雁 敗呪研 硲窒背 亀杵聖 戚疑
	if (*option == 1 || *option == 2){
		if (ret == false){
			ret = player->one_step_noAI(new_map);
		}
		else{
			//
		}
	}
	// 幻鉦 3腰(掩達奄 AI)昔 井酔 背雁 敗呪研 硲窒背 亀杵聖 戚疑
	else if (*option == 3){
		if (ret == false){
			ret = player->one_step_AI(new_map);
		}
		else {
			//
		}
	}
	// 己舛左拭辞 亀杵税 是帖研 呪舛背層陥.
	new_map->setObject(player->cur_pos.x, player->cur_pos.y, thief);


	// 戚板 井茸税 崇送績 穣汽戚闘
	// 井茸 亀杵聖 降胃梅聖凶 鎧左鎧澗 五室走 (1, 3腰 辛芝)
	if (*option == 1 || *option == 3){
		if (watcher->cur_pos.isinRange(&player->cur_pos, watcher->vision)){
			printf("\a Alert triggered, Game over\n");
			ret = true;
		}
	}
	// 2腰 辛芝, 井茸戚 亀杵聖 蓄旋拝獣
	else if (*option == 2){
		// cctv亜 亀杵聖 降胃梅聖凶 鎧左鎧澗 五室走
		if (watcher->cur_pos.isinRange(&player->cur_pos, watcher->vision) && ret != true){
			printf("\a遂税切 溌昔, 蓄旋掻 \n");
			// 井茸税 薄仙是帖澗 崇送析呪 赤澗 展析稽 呪舛背層陥.(Prodecessor亜 災亜管馬糠稽 析舘 戚係惟.._
			// 戚君廃 崇送績税 庚薦澗 movable須税 陥献 展析(ex 鯉旋走)研 高壱 走蟹穐聖獣
			// 差姥亜 災亜管馬陥澗 舘繊戚 赤陥.
			new_map->setObject(watcher->cur_pos.x, watcher->cur_pos.y, movable);
			// 井茸税 蓄旋敗呪研 搭背 井茸税 薄仙是帖研 呪舛
			watcher->persuit(&player->cur_pos);
			// 走亀舛左拭 穣汽戚闘
			new_map->setObject(watcher->cur_pos.x, watcher->cur_pos.y, tower);	
			
			// 井茸引 亀杵戚 幻概澗走 溌昔
			ret = player->cur_pos.equalTo(&(watcher->cur_pos));
			
			// 幻概聖井酔
			if (ret){
				printf("雁重聖 端匂杯艦陥. 旦槌旦槌\n");
				// 軒渡戚 if 姥庚照拭 赤聖井酔 return戚 紬鞠醸聖 井酔 敗呪澗 巷繕闇 曽戟吉陥.
				return ret;
			}
			return ret;
		}
	}
	return ret;
}

// 奄沙 UI窒径
void printUI(){
	printf("亀杵戚 切疑生稽 鯉旋走研 達焼亜澗 覗稽益轡\n");
	printf("亀杵 : ��, 井茸 : −, 鯉旋走 : 鯉\n");
}

// Main menu 兄希 貢 窒径
int mainMenu(){
	int ret = -1;
	while (true){
		print_signature();
		printf("1. 朔 己, no掩達奄 AI, 井茸 獣醤暗軒鎧 亀杵 降胃獣 惟績over\n");
		printf("2. 朔 己, no掩達奄, 井茸戚 亀杵蓄旋, 端匂獣 惟績 over\n");
		printf("3. 舌蕉弘 己, 掩達奄 AI(砺什闘掻), no 添発, 獣醤暗軒鎧 惟績 over\n");
		printf("0. 曽戟\n");
		printf("脊径 : ");
		scanf("%d", &ret);
		if (ret != 1 && ret != 2 && ret != 3 && ret !=0){
			printf("辛芝掻拭 陥獣 茨虞爽室推.\n");
		}
		return ret;
	}
}

// 惟績聖 辛芝拭 魚虞辞 稽漁馬澗 敗呪
// 雌伐拭 魚虞 稽漁鉢檎聖 戚楕拭 増嬢隔嬢 兄希 獣迭呪 赤陥.
// 幻鉦 搾疑奄縦生稽 兄希亜 亜管拝 井酔, 稽漁鉢檎 兄希人 稽漁聖 疑獣拭 遭楳亜管
void gameload(GAME_MAP *new_map, THIEF *player, CCTV *watcher, int *type){	
	system("cls");
	printf("稽漁掻...\n");
	_sleep(2000);
	objectLoading(player, watcher, type);				// loading object
	mapLoading(new_map, player, watcher, type);		// loading map
}

// 辞誤
void print_signature(){
	printf("戚費疑\n");
	printf("SGA51A\n");
	printf("07182014 引薦\n");
	printf("============================================================\n");
	printf("亀杵引 井茸\n\n");
}