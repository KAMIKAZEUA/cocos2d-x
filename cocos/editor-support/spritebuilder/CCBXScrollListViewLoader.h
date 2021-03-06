#ifndef _CCBX_CCSCROLLLISTVIEWLOADER_H_
#define _CCBX_CCSCROLLLISTVIEWLOADER_H_

#include "base/CCRef.h"

#include "CCBXWidgetLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL ScrollListViewLoader : public WidgetLoader {
public:
    
    static ScrollListViewLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner, const ValueMap &customProperties, const NodeParams& params) const override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, const cocos2d::ValueMap &customProperties, const NodeParams& params) const override;
    
CC_CONSTRUCTOR_ACCESS:
    ScrollListViewLoader();
    ~ScrollListViewLoader();

protected:
    virtual void onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value) override;
    virtual void onHandlePropTypeCCBFile(const std::string &propertyName, bool isExtraProp, const NodeLoaderDescription &value) override;
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value) override;
    virtual void onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value) override;
    virtual void onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value) override;
    virtual void onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value) override;
    virtual void onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value) override;
    virtual void onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value) override;
    
private:
    bool _horizontal;
    bool _clipping;
    bool _inertial;
    bool _scrollBar;
    bool _bounce;
    int _gravity;
    int _magnetic;
    NodeLoaderDescription _loader;
    FloatScaleDescription _scrollBarWidth;
    bool _scrollBarAutoHideEnabled;
    bool _scrollHideIfSizeFit;
    PositionDescription _scrollBarPositionFromCorner;
    Color3B _scrollBarColor;
    GLubyte _scrollBarOpacity;
};

}

NS_CC_END

#endif
