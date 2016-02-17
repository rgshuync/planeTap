//
//  UserData.h
//  com.nguyenhuy.mygame.planetap
//
//  Created by NguyenHuy on 1/27/16.
//
//

#ifndef __com_nguyenhuy_mygame_planetap__UserData__
#define __com_nguyenhuy_mygame_planetap__UserData__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class UserData{
public:
    void setScore_user(int score){
        UserDefault::getInstance()->setIntegerForKey("score",score);
    };
    void setLevel_user(int level){
        UserDefault::getInstance()->setIntegerForKey("level", level);
    }
    void setCoin_user(int coin){
        UserDefault::getInstance()->setIntegerForKey("coin", coin);
    }
    void setPlaneType_user(int type){
         UserDefault::getInstance()->setIntegerForKey("plantype", type);
    }
//Get value with key
    void getScore_user(int score){
        UserDefault::getInstance()->getIntegerForKey("score");
    };
    void getLevel_user(int level){
        UserDefault::getInstance()->getIntegerForKey("level");
    }
    void getCoin_user(int coin){
        UserDefault::getInstance()->getIntegerForKey("coin");
    }
    void getPlaneType_user(int type){
        UserDefault::getInstance()->getIntegerForKey("plantype");
    }

};
#endif /* defined(__com_nguyenhuy_mygame_planetap__UserData__) */
