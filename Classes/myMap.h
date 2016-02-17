//
//  myMap.h
//  com.nguyenhuy.mygame.planetap
//
//  Created by NguyenHuy on 1/23/16.
//
//

#ifndef __com_nguyenhuy_mygame_planetap__myMap__
#define __com_nguyenhuy_mygame_planetap__myMap__

#include <stdio.h>
#include "Coin.h"
#include <cocos2d.h>
USING_NS_CC;

class myMap: public TMXTiledMap{
public:
    myMap();
    ~myMap();
    static myMap* Create(char []);
    void loatItemOnMap();
    void loadPhysicsOnMap();
    void removeItemOnMap();
private:
    Vector<Coin*> arrItem;
};
#endif /* defined(__com_nguyenhuy_mygame_planetap__myMap__) */