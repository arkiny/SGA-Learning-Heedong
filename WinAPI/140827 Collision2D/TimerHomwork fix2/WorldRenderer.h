/*
	@author		Heedong Arkiny Lee
	@git		https://github.com/arkiny/SGA-Learning-Heedong
*/

#pragma once;
#include <Windows.h>
#include "World.h"

class WorldRenderer{
public:	
	WorldRenderer(World* world){		
		_world = world;
	}
	
	void render(HDC hdc){
		if (!_world->EllipseCollider()){
			::Ellipse(hdc,
				_world->getObstacle().getPos().x - _world->getObstacle().getSize(),
				_world->getObstacle().getPos().y - _world->getObstacle().getSize(),
				_world->getObstacle().getPos().x + _world->getObstacle().getSize(),
				_world->getObstacle().getPos().y + _world->getObstacle().getSize());
		}
				
		HBRUSH myBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);		
		/*::Rectangle(hdc,
			_world->getPlayer().getPos().x - _world->getPlayer().getSize(),
			_world->getPlayer().getPos().y - _world->getPlayer().getSize(),
			_world->getPlayer().getPos().x + _world->getPlayer().getSize(),
			_world->getPlayer().getPos().y + _world->getPlayer().getSize());*/
		::Ellipse(hdc,
			_world->getPlayer().getPos().x - _world->getPlayer().getSize(),
			_world->getPlayer().getPos().y - _world->getPlayer().getSize(),
			_world->getPlayer().getPos().x + _world->getPlayer().getSize(),
			_world->getPlayer().getPos().y + _world->getPlayer().getSize());
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
	}

private:
	World* _world;
};