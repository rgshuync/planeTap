//
//  myMap.cpp
//  com.nguyenhuy.mygame.planetap
//
//  Created by NguyenHuy on 1/23/16.
//
//

#include "myMap.h"
myMap::myMap(){}
myMap::~myMap(){}

myMap* myMap::Create(char mapName[]){
    myMap * obj = new myMap();
    obj->initWithTMXFile(mapName);
    return obj;
}
// Load physics body on map
void myMap::loadPhysicsOnMap(){
    for(int i=1;i<=2;i++){
        std::stringstream ss;
        ss << i;
        TMXObjectGroup * objGroup = getObjectGroup("limitted"+ss.str());
        ValueVector vecMapValue = objGroup->getObjects();
        int size = vecMapValue.size();
        Vec2  points[200];
        for(int i=0;i<size;i++){
            ValueMap obj = vecMapValue.at(i).asValueMap();
            float x = obj.at("x").asFloat();
            float y = obj.at("y").asFloat();
            points[i].setPoint(x, y);
        }
        auto body = PhysicsBody::createEdgePolygon(points, size,PhysicsMaterial(1,0,1));
        body->setContactTestBitmask(true);
        body->setCategoryBitmask(0x001);
        body->setCollisionBitmask(0x001);
        body->setTag(30);
        Node * node = Node::create();
        node->setPhysicsBody(body);
        addChild(node);
    }
}
//Load item on map
void myMap::loatItemOnMap(){
    Point poinItem[100];
    auto tmxObjGroup = getObjectGroup("coin");
    auto VecItem = tmxObjGroup->getObjects();
    //Point array is emtry
    removeItemOnMap();
    if(poinItem[0].y==0)
        for(int i=0;i<VecItem.size();i++){
            auto val = VecItem.at(i).asValueMap();
            float x= val.at("x").asFloat();
            float y= val.at("y").asFloat();
            poinItem[i].set(x, y);
            
        }
    for(int i=0;i<VecItem.size()/2;i++){
        int posArr = rand()%VecItem.size();
        float x= VecItem.at(posArr).asValueMap().at("x").asFloat();
        float y = VecItem.at(posArr).asValueMap().at("y").asFloat();
        auto coin = Coin::Create();
        coin->setPosition(Vec2(x,y));
        coin->setScale(0.7);
        addChild(coin);
        arrItem.pushBack(coin);
        
    }

}
//Remove item on map
void myMap::removeItemOnMap(){
    for(int i=0;i<arrItem.size();i++){
        arrItem.at(i)->removeFromParent();
        arrItem.at(i)->release();
        arrItem.popBack();
    }
}