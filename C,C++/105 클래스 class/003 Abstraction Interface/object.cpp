// 엔간해선 헤더 참조는 다 cpp파일로 내려보내도록 한다.
// 꺽쇠 모양 헤더를 맨위로 보내고
#include <iostream>
#include <cmath>

// custom header를 나중에 넣을수있도록 한다.
#include "object.h"

// 왜 using namespace std를 안쓰고 일부분만 가져오느냐
// 매번 로딩때마다 다 로딩하게 되면 무거워진다...
using std::cout;
using std::endl;

void Object::show(){
	cout << ">>> Object Class <<<" << endl;
	cout << "posX = " << pos.fx << ", posY = " << pos.fy << endl;
}

Object::Object(){
	cout << ">>> Object Constructed <<<" << endl;
	// 초기화 방법은 여러가지가 있으니...
	/*pos.fx = 0.0f;
	pos.fy = 0.0f;*/
	//혹은
	//pos = POINT(); // 구조체도 일종의 class이므로 숨겨진 생성자, 소멸자가 있다.
}

Object::Object(float x, float y){
	pos.fx = x;
	pos.fy = y;
}

Object::~Object(){
	cout << ">>> Object Destructed <<<" << endl;
}

void Object::setPos(float inputX, float inputY){
	pos.fx = inputX;
	pos.fy = inputY;
}

void Object::movePos(float moveX, float moveY){
	pos.fx += moveX;
	pos.fy += moveY;
}

float Object::calcDistance(POINT &target){
	// sqrt((세로 거리)^2 + (가로거리)^2)
	return sqrt(pow((target.fx - pos.fx), 2) + pow((target.fy - pos.fy), 2));
}

void Object::showDistance(POINT &target){
	cout << "Distance to Target= " << this->calcDistance(target) << endl;
}

float Object::calcAngle(POINT &target){
	// tan^-1 (x/y) * (180 / PI)
	return atan2((target.fy - pos.fy), (target.fx - pos.fx)) * (180 / 3.141592);
}

void Object::showAngle(POINT &target){
	cout << "Angle to Target= " << this->calcAngle(target) << " degree"<< endl;
}

POINT Object::getPos(){
	return pos;
}