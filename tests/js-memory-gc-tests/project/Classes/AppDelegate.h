#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "platform/CCApplication.h"
/**
 @brief    The cocos2d Application.
 
 Private inheritance here hides part of interface from Director.
 */
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    
    void initGLContextAttrs() override;
    
    /**
     @brief    Implement Director and Scene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching() override;
    
    /**
     @brief  Called when the application moves to the background
     @param  the pointer of the application
     */
    virtual void applicationDidEnterBackground() override;
    
    /**
     @brief  Called when the application reenters the foreground
     @param  the pointer of the application
     */
    virtual void applicationWillEnterForeground() override;
    
    /**
     @brief  This function will be called when the application screen size is changed.
     @param new width
     @param new height
     */
    virtual void applicationScreenSizeChanged(int newWidth, int newHeight) override;
};

#endif // _APP_DELEGATE_H_

