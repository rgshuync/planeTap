#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vec2(0,-5));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto evenTouch = EventListenerTouchOneByOne::create();
    auto evenContact = EventListenerPhysicsContact::create();
    auto evenKeyBoard = EventListenerKeyboard::create();
   // evenKeyBoard->onKeyReleased= CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    // Create touch even
    evenTouch->onTouchBegan= CC_CALLBACK_2(HelloWorld::onTouchBegin,this);
    evenTouch->onTouchMoved= CC_CALLBACK_2(HelloWorld::onTouchMoved,this);
    evenTouch->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    evenKeyBoard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    evenContact->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(evenTouch, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(evenContact, this);
    //Create may bay
    maybay = MayBay::Create();
    maybay->setAnchorPoint(Vec2(0, 0));
    //Create background game
    bg = Sprite::create("backgrounds/background.png");
    bg->setAnchorPoint(Point(0,0));
    bg->setPosition(Point(origin.x,origin.y));
    bg->setTag(5);
    bg->setScale(visibleSize.width/bg->getContentSize().width, visibleSize.height/bg->getContentSize().height);
    //Create parallax
    bgPlayer= InfiniteParallaxNode::create();
    bgPlayer->addChild(bg,BACKGROUND,Point(0,0),bg->getPosition());
    bgPlayer->addChild(maybay,BG_PLAYER,Point(0,0),Point(visibleSize.width/3,visibleSize.height/2+origin.y));
    bgPlayer->setAnchorPoint(Point(0,0));
    bgPlayer->setPosition(Point(0,0));
    this->addChild(bgPlayer);
    //Create array map for scroll
    secondBg = Sprite::create("backgrounds/background.png");
    secondBg->setPositionY(bg->getPositionY());
    secondBg->setAnchorPoint(bg->getAnchorPoint());
    secondBg->setScale(bg->getScaleX(),bg->getScaleY());
    bgPlayer->addChild(secondBg,BACKGROUND,Point(0,0),secondBg->getPosition());
    //Create sprite ready
    auto spReadyCache = SpriteFrameCache::getInstance();
    spReadyCache->addSpriteFramesWithFile("UI/UI.plist");
    auto spRedyLef = Sprite::createWithSpriteFrame(spReadyCache->getSpriteFrameByName("tapLeft.png"));
    auto spRedyRight = Sprite::createWithSpriteFrame(spReadyCache->getSpriteFrameByName("tapRight.png"));
    auto spHandUp= Sprite::createWithSpriteFrame(spReadyCache->getSpriteFrameByName("tap.png"));
    spRedyLef->setAnchorPoint(Vec2(1,0));
    spRedyLef->setPosition(Vec2(maybay->getPositionX()-maybay->getContentSize().width/2, maybay->getPositionY()));
    spRedyRight->setAnchorPoint(Vec2(0,0));
    spRedyRight->setPosition(Vec2(maybay->getPositionX()+maybay->getContentSize().width*1.5, maybay->getPositionY()));
    spHandUp->setAnchorPoint(Vec2(0,0));
    spHandUp->setPosition(maybay->getPositionX(), maybay->getPositionY()-maybay->getContentSize().height);
    Vector<SpriteFrame*> arrFrm;
    arrFrm.pushBack(spReadyCache->getSpriteFrameByName("tapTick.png"));
    arrFrm.pushBack(spHandUp->getSpriteFrame());
    auto animation =Animation::createWithSpriteFrames(arrFrm,0.5);
    auto anima = Animate::create(animation);
    spHandUp->runAction(RepeatForever::create(anima));
    Node * node = Node::create();
    node->addChild(spRedyLef);
    node->addChild(spRedyRight);
    node->addChild(spHandUp);
    node->setTag(READY_TAG);
    this->addChild(node);
    loadMap(1);
//Create information about player
    txtLevel = Label::createWithTTF("Lavel 1","fonts/Marker Felt.ttf",18);
    txtLevel->setColor(Color3B::MAGENTA);
    txtLevel->setAnchorPoint(Vec2(0.5,0));
    txtLevel->setPosition(Vec2(visibleSize.width/2-txtLevel->getContentSize().width,visibleSize.height-txtLevel->getContentSize().height-10));
    txtCoin= Label::createWithTTF("Coin 0","fonts/Marker Felt.ttf",18);
    txtCoin->setColor(txtLevel->getColor());
    txtCoin->setAnchorPoint(Vec2(0.5,0));
    txtCoin->setPosition(Vec2(txtLevel->getPositionX()+2*txtLevel->getContentSize().width,txtLevel->getPositionY()));
    this->addChild(txtLevel);
    this->addChild(txtCoin);
    setTouchEnabled(true);
    return true;
}
void HelloWorld::loadMap(int cMap){
    auto origin = Director::getInstance()->getVisibleOrigin();
    char strLevel[50];
    char str_start_level[50];
    sprintf(strLevel,"map/level%d.tmx",cMap);
    sprintf(str_start_level,"map/start_level%d.tmx",cMap);
    map_start = myMap::Create(str_start_level);
    map_start->setAnchorPoint(Vect(0,0));
    map_start->setPosition(Vect(visibleSize.width+50,origin.y));
    map_start->setScaleY(visibleSize.height/map_start->getContentSize().height);
    map_start->loadPhysicsOnMap();
    map = myMap::Create(strLevel);
    map->setAnchorPoint(map_start->getAnchorPoint());
    map->setPosition(Vec2(map_start->getPositionX()+map_start->getBoundingBox().size.width,map_start->getPositionY()));
    map->setScaleY(map_start->getScaleY());
    map->loadPhysicsOnMap();
    bgPlayer->addChild(map_start,BG_PLAYER,Point(0,0),map_start->getPosition());
    bgPlayer->addChild(map,BG_PLAYER,Point(0,0),map->getPosition());
    secondMap = myMap::Create(strLevel);
    secondMap->setPositionY(map->getPositionY());
    secondMap->setAnchorPoint(map->getAnchorPoint());
    secondMap->setPosition(Vec2(map->getPositionX()+map->getBoundingBox().size.width,map->getPositionY()));
    secondMap->setScaleY(map->getScaleY());
    secondMap->loadPhysicsOnMap();
    bgPlayer->addChild(secondMap,BG_PLAYER,Point(0,0),secondMap->getPosition());
    map->loatItemOnMap();
    secondMap->loatItemOnMap();
}
void HelloWorld::createInfiniteMap(float r){
    float step=0.7;
    float posMapX = map->getPositionX();
    float posMapY = map->getPositionY();
    float stepBg=0.4f;
    if(scrollMap){
        if(map_start!=NULL){
            if(map_start->getPositionX()+map_start->getBoundingBox().size.width<=0){
                map->setPositionX(map->getPositionX()-step);
                secondMap->setPositionX(map->getPositionX()+map->getBoundingBox().size.width);
                map_start->removeFromParent();
                map_start=NULL;
            }
            else{
                map_start->setPositionX(map_start->getPositionX()-step);
                map->setPositionX(map_start->getPositionX()+map_start->getBoundingBox().size.width);
                secondMap->setPositionX(map->getPositionX()+map->getBoundingBox().size.width);
            }
        }
        else {
            // Infinite title map
            map->setPositionX(posMapX-step);
            if(kScroll!=0){
            secondMap->setPositionX(map->getPositionX()+map->getBoundingBox().size.width);
            if(map->getPositionX()+map->getBoundingBox().size.width<=0){
                map->setPositionX(secondMap->getPositionX()+secondMap->getBoundingBox().size.width);
                map->loatItemOnMap();
                myMap * tg = map;
                map=secondMap;
                secondMap=tg;
                kScroll--;
                }
            }
            else if(map->getPositionX()+map->getBoundingBox().size.width<=0){
                scrollMap=false;
                this->runAction(CallFunc::create(CC_CALLBACK_0(HelloWorld::nextLevel, this)));
            }
        }
    }
    // Infinite background
    bg->setPositionX(bg->getPositionX()-stepBg);
    secondBg->setPositionX(bg->getPositionX()+ bg->getBoundingBox().size.width);
    if(bg->getPositionX()+bg->getBoundingBox().size.width<=0){
        bg->setPositionX(secondBg->getPositionX()+secondBg->getBoundingBox().size.width);
        Sprite * tg= bg;
        bg=secondBg;
        secondBg=tg;
    }
}
void HelloWorld::nextLevel(){
    currLevel++;
    map->removeFromParent();
    map=NULL;
    secondMap->removeFromParent();
    secondMap=NULL;
    if(currMap==4) currMap=0;
    loadMap(++currMap);
    scrollMap=true;
    kScroll=4;
    std::stringstream ss;
    ss<<currLevel;
    txtLevel->setString("Level "+ss.str());
    
}
bool HelloWorld::onTouchBegin(Touch * touch, Event* event){
    float time= maybay->getPositionY()/50;
    auto raise = MoveTo::create(0.1, Vec2(maybay->getPositionX(),maybay->getPositionY()+10));
    auto rota = RotateTo::create(0.2, -5);
    auto up = Spawn::create(raise, rota,NULL);
    auto fall = MoveTo::create(time, Vec2(maybay->getPositionX(),40));
    auto reverdRota = RotateTo::create(0.3,5);
    auto down= Spawn::create(fall, reverdRota,NULL);
    auto seq= Sequence::create(up, DelayTime::create(0.1),down,NULL);
    seq->setTag(5);
    maybay->stopActionByTag(5);
    maybay->runAction(seq);
   
}
bool HelloWorld::onContactBegin(PhysicsContact & contact){
    CCLOG("Va cham");
    auto shapeA = contact.getShapeA();
    auto shapeB = contact.getShapeB();
    if(shapeA->getBody()->getTag()==20){
        shapeA->getBody()->getNode()->removeFromParent();
        currCoin++;
        std::stringstream ss;
        ss<<currCoin;
        txtCoin->setString("Coin "+ss.str());
    }
    else if(shapeB->getBody()->getTag()==20){shapeB->getBody()->getNode()->removeFromParent();currCoin++;}
    else if(shapeA->getBody()->getTag()==30 || shapeB->getBody()->getTag()==30){
        CCLOG("gameOver");
        maybay->stopAllActions();
        this->unschedule(schedule_selector(HelloWorld::createInfiniteMap));
        maybay->getPhysicsBody()->setGravityEnable(true);
        maybay->getPhysicsBody()->setContactTestBitmask(false);
        auto spFrmCache = SpriteFrameCache::getInstance();
        auto spGameOver = Sprite::createWithSpriteFrame(spFrmCache->getSpriteFrameByName("textGameOver.png"));
        this->addChild(spGameOver);
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        spGameOver->setPosition(Vec2(visibleSize.width/2,visibleSize.height+100));
        auto mvOver1 = MoveTo::create(1, Vec2(visibleSize.width/2,visibleSize.height/2+40));
        auto mvOver2 = MoveTo::create(0.5, Vec2(visibleSize.width/2,visibleSize.height/2));
        auto seqOver = Sequence::create(mvOver1,DelayTime::create(0.1),mvOver2, NULL);
        auto reload = CallFunc::create(CC_CALLBACK_0(HelloWorld::reLoadSence, this));
        auto seq = Sequence::create(seqOver,DelayTime::create(2),reload, NULL);
        spGameOver->runAction(seq);
    }
    
}
void HelloWorld::reLoadSence(){
    auto newGame = HelloWorld::createScene();
    Director::getInstance()->replaceScene(newGame);
    
}
void HelloWorld::onTouchMoved(Touch*touch, Event* event){
    
}
void HelloWorld::onTouchEnded(Touch *touch, Event *event){
    CCLOG("ENd touch ");
    if (!stateGame) {
        schedule(schedule_selector(HelloWorld::createInfiniteMap),0.01f);
        stateGame=true;
        scrollMap=true;
        removeChildByTag(READY_TAG);
    }
}
void HelloWorld::onTouchCancelled(Touch * touch, Event * event){
    CCLOG("TOuch cancel");
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode KeyCode , Event * event){
    if (KeyCode==EventKeyboard::KeyCode::KEY_BACK) {
        Director::getInstance()->end();
    }
}

