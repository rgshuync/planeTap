//
//  Coin.h
//  com.nguyenhuy.mygame.planetap
//
//  Created by NguyenHuy on 1/22/16.
//
//

#ifndef __com_nguyenhuy_mygame_planetap__Coin__
#define __com_nguyenhuy_mygame_planetap__Coin__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Coin: public Sprite{
public:
    Coin();
    ~Coin();
    static Coin* Create();
};
#endif /* defined(__com_nguyenhuy_mygame_planetap__Coin__) */
