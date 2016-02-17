
#include "InfiniteParallaxNode.h"
InfiniteParallaxNode* InfiniteParallaxNode::create()
{
    // Create an instance of InfiniteParallaxNode
    InfiniteParallaxNode* node = new InfiniteParallaxNode();
    if(node) {
        // Add it to autorelease pool
        node->autorelease();
    } else {
        // Otherwise delete
        delete node;
        node = 0;
    }
    return node;
}
void InfiniteParallaxNode::updatePosition()
{
    int safeOffset = -1;
        Size visibleSize = Director::getInstance()->getVisibleSize();
    // Get visible size
   // Size visibleSize = Director::getInstance()->getVisibleSize();
    // 1. For each child of an parallax node
    for(int i = 0; i < _children.size(); i++)
    {
        auto node = _children.at(i);
        // 2. We check whether it is out of the left side of the visible area
        CCLOG("vi tri node: %f",convertToNodeSpace(node->getPosition()).x+node->getContentSize().width);
        if(convertToWorldSpace(node->getPosition()).x + node->getContentSize().width < safeOffset)
            // 3. Find PointObject that corresponds to current node
            CCLOG("on to replace");
        for(int i = 0; i < _parallaxArray->num; i++)
        {
            auto po = (PointObject*)_parallaxArray->arr[i];
            // If yes increase its current offset on the value of visible width
            if(po->getChild() == node)
                po->setOffset(po->getOffset() +
                              Point(visibleSize.width + node->getContentSize().width,0));
        }
    }
}