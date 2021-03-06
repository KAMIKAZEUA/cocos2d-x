#include "CCBXEditBoxLoader.h"
#include "ui/UIEditBox/UIEditBox.h"

NS_CC_BEGIN
namespace spritebuilder {

static const std::string PROPERTY_BLENDFUNC("blendFunc");
static const std::string PROPERTY_FONTCOLOR("fontColor");
static const std::string PROPERTY_FONTNAME("fontName");
static const std::string PROPERTY_FONTSIZE("fontSize");
static const std::string PROPERTY_STRING("string");

static const std::string PROPERTY_PLACEHOLDERFONTCOLOR("placeholderFontColor");
static const std::string PROPERTY_PLACEHOLDERFONTNAME("placeholderFontName");
static const std::string PROPERTY_PLACEHOLDERFONTSIZE("placeholderFontSize");
static const std::string PROPERTY_PLACEHOLDER("placeholder");

static const std::string PROPERTY_CONTENTSIZE("contentSize");
    
static const std::string PROPERTY_MAXLENGTH("maxLength");
    
static const std::string PROPERTY_KEYBOARDRETURNTYPE("keyboardReturnType");
static const std::string PROPERTY_INPUTMODE("inputMode");
static const std::string PROPERTY_INPUTFLAG("inputFlag");
    
static const std::string PROPERTY_BACKGROUNDSPRITEFRAME("backgroundSpriteFrame");
    
static const std::string PROPERTY_MARGIN("margin");
static const std::string PROPERTY_MARGIN_LEFT("marginLeft");
static const std::string PROPERTY_MARGIN_TOP("marginTop");
static const std::string PROPERTY_MARGIN_RIGHT("marginRight");
static const std::string PROPERTY_MARGIN_BOTTOM("marginBottom");
    
    
EditBoxLoader *EditBoxLoader::create()
{
    EditBoxLoader *ret = new EditBoxLoader();
    ret->autorelease();
    return ret;
}

Node *EditBoxLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner, const ValueMap &customProperties, const NodeParams& params) const
{
    Size editBoxSize(200,100);
    
    const SpriteFrameDescription &normalSpriteFrame = getNodeParamValue(params, PROPERTY_BACKGROUNDSPRITEFRAME, _normalSpriteFrame);
    //noramal sprite frame must be set for EditBox
    assert(normalSpriteFrame.type != SpriteFrameDescription::TextureResType::NONE);
    
    Size size = normalSpriteFrame.spriteFrame->getOriginalSize();
    const Vec4 &margins = getNodeParamValue(params, PROPERTY_MARGIN, _margins);
    ui::Scale9Sprite *normalSprite = ui::Scale9Sprite::createWithSpriteFrame(_normalSpriteFrame.spriteFrame, calcMargins(margins, size));
    
    ui::EditBox *editBox = ui::EditBox::create(editBoxSize, normalSprite);
    editBox->setAnchorPoint(Vec2(0.0f, 0.0f));
    return editBox;
}

void EditBoxLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, const cocos2d::ValueMap &customProperties, const NodeParams& params) const
{
    WidgetLoader::setSpecialProperties(node, parentSize, mainScale, additionalScale, owner, rootNode, customProperties, params);
    ui::EditBox *editBox = static_cast<ui::EditBox*>(node);
    editBox->setText(getNodeParamValue(params, PROPERTY_STRING, _label).c_str());
    editBox->setPlaceHolder(getNodeParamValue(params, PROPERTY_PLACEHOLDER, _placeholder).c_str());
    int maxLength = getNodeParamValue(params, PROPERTY_MAXLENGTH, _maxLength);
    editBox->setMaxLength(maxLength==0?INT_MAX:maxLength);
    editBox->setFont(getNodeParamValue(params, PROPERTY_FONTNAME, _font).c_str(), getAbsoluteScale(mainScale, additionalScale, getNodeParamValue(params, PROPERTY_FONTSIZE, _fontSize)));
    editBox->setFontColor(getNodeParamValue(params, PROPERTY_FONTCOLOR, _fontColor));
    editBox->setPlaceholderFont(getNodeParamValue(params, PROPERTY_PLACEHOLDERFONTNAME, _placeholderFont).c_str(), getAbsoluteScale(mainScale, additionalScale, getNodeParamValue(params, PROPERTY_PLACEHOLDERFONTSIZE, _placeholderFontSize)));
    editBox->setPlaceholderFontColor(getNodeParamValue(params, PROPERTY_PLACEHOLDERFONTCOLOR, _placeholderFontColor));
    
    editBox->setInputMode(static_cast<ui::EditBox::InputMode>(getNodeParamValue(params, PROPERTY_INPUTMODE, _inputMode)));
    editBox->setInputFlag(static_cast<ui::EditBox::InputFlag>(getNodeParamValue(params, PROPERTY_INPUTFLAG, _inputFlag)));
    editBox->setReturnType(static_cast<ui::EditBox::KeyboardReturnType>(getNodeParamValue(params, PROPERTY_KEYBOARDRETURNTYPE, _keyboardReturnType)));
}

EditBoxLoader::EditBoxLoader()
    :_keyboardReturnType(0)
    ,_inputMode(static_cast<int>(ui::EditBox::InputMode::SINGLE_LINE))
    ,_inputFlag(static_cast<int>(ui::EditBox::InputFlag::INITIAL_CAPS_SENTENCE))
{
    
}
    
EditBoxLoader::~EditBoxLoader()
{
    
}
    
void EditBoxLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    WidgetLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
}
    
void EditBoxLoader::onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value)
{
    WidgetLoader::onHandlePropTypeColor3(propertyName, isExtraProp, value);
}
    
void EditBoxLoader::onHandlePropTypeColor4(const std::string &propertyName, bool isExtraProp, const Color4B &value)
{
    if(propertyName == PROPERTY_PLACEHOLDERFONTCOLOR) {
        _placeholderFontColor = value;
    } else if(propertyName == PROPERTY_FONTCOLOR) {
        _fontColor = value;
    } else {
        WidgetLoader::onHandlePropTypeColor4(propertyName, isExtraProp, value);
    }
}

void EditBoxLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value)
{
    if(propertyName == PROPERTY_BLENDFUNC) {
        //((LayerColor *)pNode)->setBlendFunc(pBlendFunc);
    }  else {
        WidgetLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, value);
    }
}

void EditBoxLoader::onHandlePropTypeFontTTF(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_FONTNAME) {
        _font = value;
    } else if(propertyName == PROPERTY_PLACEHOLDERFONTNAME) {
        _placeholderFont = value;
    } else {
        WidgetLoader::onHandlePropTypeFontTTF(propertyName, isExtraProp, value);
    }
}

void EditBoxLoader::onHandlePropTypeText(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_STRING) {
        _label = value;
    } else if(propertyName == PROPERTY_PLACEHOLDER) {
        _placeholder = value;
    } else {
        WidgetLoader::onHandlePropTypeText(propertyName, isExtraProp, value);
    }
}
    
void EditBoxLoader::onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value)
{
    if(propertyName == PROPERTY_MARGIN) {
        _margins = value;
    } else {
        NodeLoader::onHandlePropTypeOffsets(propertyName, isExtraProp, value);
    }
}
    
void EditBoxLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_MARGIN_LEFT) {
        _margins.x = value;
    } else if(propertyName == PROPERTY_MARGIN_TOP) {
        _margins.y = value;
    } else if(propertyName == PROPERTY_MARGIN_RIGHT) {
        _margins.z = value;
    } else if(propertyName == PROPERTY_MARGIN_BOTTOM) {
        _margins.w = value;
    } else {
        WidgetLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}


void EditBoxLoader::onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value)
{
    if(propertyName == PROPERTY_FONTSIZE) {
        _fontSize = value;
    } else if(propertyName == PROPERTY_PLACEHOLDERFONTSIZE) {
        _placeholderFontSize = value;
    } else {
        WidgetLoader::onHandlePropTypeFloatScale(propertyName, isExtraProp, value);
    }
}
    
void EditBoxLoader::onHandlePropTypeInteger(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_MAXLENGTH) {
        _maxLength = value;
    } else {
        WidgetLoader::onHandlePropTypeInteger(propertyName, isExtraProp, value);
    }
}

void EditBoxLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_KEYBOARDRETURNTYPE) {
        _keyboardReturnType = value;
    } else if(propertyName == PROPERTY_INPUTMODE) {
        _inputMode = value;
    } else if(propertyName == PROPERTY_INPUTFLAG) {
        _inputFlag = value;
    } else {
        WidgetLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}

void EditBoxLoader::onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value)
{
    WidgetLoader::onHandlePropTypeSize(propertyName, isExtraProp, value);
}

void EditBoxLoader::onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value)
{
    WidgetLoader::onHandlePropTypePosition(propertyName, isExtraProp, value);
}
    
void EditBoxLoader::onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value)
{
    if(propertyName == PROPERTY_BACKGROUNDSPRITEFRAME) {
        _normalSpriteFrame = value;
    } else {
        WidgetLoader::onHandlePropTypeSpriteFrame(propertyName, isExtraProp, value);
    }
}

}
    
NS_CC_END
