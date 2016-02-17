#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MayBay.h"
#include "InfiniteParallaxNode.h"
#include "myMap.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    Size visibleSize = Director::getInstance()->getVisibleSize();
    const float PTM_RATIO=32;
    const int BACKGROUND=-1;
    const int BG_PLAYER=200;
    int kScroll=1;// number of scroll map
    int currLevel=1;
    int currMap=1;
    int currCoin=0;
    const int READY_TAG=100;
    bool stateGame=false;// start scroll background
    bool scrollMap=false;// start scroll map
    static cocos2d::Scene* createScene();
    virtual bool init();
    MayBay * maybay;
    myMap* map;
    myMap * secondMap;
    myMap * map_start;
    Label * txtLevel;
    Label * txtCoin;
    virtual bool onTouchBegin(Touch*,Event*);
    virtual void onTouchEnded(Touch*,Event*);
    virtual void onTouchMoved(Touch*,Event*);
    virtual void onTouchCancelled(Touch*,Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode KeyCode , Event *);
    bool onContactBegin(PhysicsContact & contact);
    void loadMap(int cMap);
    void loadPhysicOnMap(TMXTiledMap * map);
    void loadItemOnMap(TMXTiledMap*);
    void createInfiniteMap(float );
    void reLoadSence();
    void nextLevel();
    Point poinItem[100];
    Vector<Coin*> arrItem;
    Sprite * bg;
    Sprite * secondBg;
    InfiniteParallaxNode * bgPlayer;
private:
    PhysicsWorld * world;
    void setPhysicsWorld(PhysicsWorld * senseWorld){world=senseWorld;}
    PhysicsWorld* getPhysicsWorld(){return world;}
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
