//
//  Coin.cpp
//  com.nguyenhuy.mygame.planetap
//
//  Created by NguyenHuy on 1/22/16.
//
//

#include "Coin.h"
Coin::Coin(){}
Coin::~Coin(){}
Coin * Coin::Create(){
    Coin * obj = new Coin();
    auto spFrameChe = SpriteFrameCache::getInstance();
    spFrameChe->addSpriteFramesWithFile("UI/UI.plist");
    if(!obj->initWithSpriteFrame(spFrameChe->getSpriteFrameByName("coin.png"))){
        CCLOG("Can't create coin");return NULL;
    }
    obj->setAnchorPoint(Vec2(0,0));
    auto phys = PhysicsBody::createCircle(obj->getContentSize().width/2);
    phys->setCategoryBitmask(0x001);
    phys->setCollisionBitmask(0x001);
    phys->setContactTestBitmask(true);
    phys->setDynamic(false);
    phys->setTag(20);
    obj->setPhysicsBody(phys);
    //auto rota = sk
    //->runAction(RepeatForever::create(rota));
    return obj;
}