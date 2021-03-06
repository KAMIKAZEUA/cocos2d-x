#ifndef _CCBX_WIDGETLOADER_H_
#define _CCBX_WIDGETLOADER_H_

#include "CCBXNodeLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL WidgetLoader : public NodeLoader {
public:
    
    static WidgetLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner, const ValueMap &customProperties, const NodeParams& params) const override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, const cocos2d::ValueMap &customProperties, const NodeParams& params) const override;
    
CC_CONSTRUCTOR_ACCESS:
    WidgetLoader();
    ~WidgetLoader();

protected:
    virtual void onHandlePropTypeClickCallback(const std::string &propertyName, bool isExtraProp, const CallbackDescription &value) override;
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value) override;
    virtual void onHandlePropTypeSoundFile(const std::string &propertyName, bool isExtraProp, const std::string &value) override;
    virtual void setCallbacks(Node* node, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *parentOwner, const NodeParams& params) const override;
    
private:
    CallbackDescription _touchDesc;
    CallbackDescription _clickDesc;
    std::string _sound;
    bool _enabled;
};

}

NS_CC_END

#endif
