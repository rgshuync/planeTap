//
//  MayBay.cpp
//  com.nguyenhuy.mygame.planetap
//
//  Created by NguyenHuy on 1/18/16.
//
//

#include "MayBay.h"

MayBay::MayBay(){}
MayBay::~MayBay(){}

MayBay * MayBay::Create(){
    MayBay * obj = new MayBay();
    auto SpFrameCache = SpriteFrameCache::getInstance();
    SpFrameCache->addSpriteFramesWithFile("plane/plane.plist");
    if(!obj->initWithSpriteFrame(SpFrameCache->getSpriteFrameByName("planeRed1.png"))){
        CCLOG("Cant not create maybay");
    }
    else{
        Vector<SpriteFrame*> vecFrm(3);
        char str[50]={0};
        for(int i=1; i<=3 ;i++){
            sprintf(str,"planeRed%d.png",i);
            auto spFrm = SpFrameCache->getSpriteFrameByName(str);
            vecFrm.pushBack(spFrm);
            
        }
        auto animation = Animation::createWithSpriteFrames(vecFrm,0.1f);
        auto ani= Animate::create(animation);
        obj->runAction(RepeatForever::create(ani));
    }
    auto physic = PhysicsBody::createBox(Size(Vec2(obj->getContentSize().width-10,obj->getContentSize().height-10)),PhysicsMaterial(1,0,1));
    physic->setCollisionBitmask(0x001);
    physic->setCategoryBitmask(0x001);
    physic->setContactTestBitmask(true);
    physic->setTag(10);
    obj->setPhysicsBody(physic);
    obj->getPhysicsBody()->setGravityEnable(false);
    obj->setFly();
    return obj;
}
void MayBay::setFly(){
    schedule(schedule_selector(MayBay::setSmoke), 0.5);
    schedule(schedule_selector(MayBay::removeSmoke), 0.5);
}
void MayBay::setSmoke(float){
    auto smoke = Sprite::create("backgrounds/puffSmall.png");
    smoke->setScale(2);
    smoke->setAnchorPoint(Vec2(0,0));
    smoke->setPosition(0, this->getContentSize().height/2-10);
    auto scale = ScaleTo::create(1, 0.1);
    auto move = MoveTo::create(1, Vec2(smoke->getPositionX()-20,smoke->getPositionY()));
    auto spawn = Spawn::create(scale,move, NULL);
    smoke->runAction(spawn);
    arrSmoke.pushBack(smoke);
    this->addChild(smoke);
}
void MayBay::removeSmoke(float){
    for(int i=0;i<arrSmoke.size()/2;i++){
        auto obj = (Sprite*)arrSmoke.at(i);
        obj->removeFromParent();
    }
}
void MayBay::setFalling(){
    
}