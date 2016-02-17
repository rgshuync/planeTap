//
//  MayBay.h
//  com.nguyenhuy.mygame.planetap
//
//  Created by NguyenHuy on 1/18/16.
//
//

#ifndef __com_nguyenhuy_mygame_planetap__MayBay__
#define __com_nguyenhuy_mygame_planetap__MayBay__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class MayBay:public Sprite{
public:
    MayBay();
    ~MayBay();
    static MayBay * Create();
    void setFly();
    void setFalling();
    void setSmoke(float);
    Vector<Sprite*> arrSmoke;
private:
    void removeSmoke(float);
};
#endif /* defined(__com_nguyenhuy_mygame_planetap__MayBay__) */
