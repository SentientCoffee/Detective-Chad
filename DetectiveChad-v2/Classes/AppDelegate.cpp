#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "MainMenu.h"
#include "Tutorial.h"
#include "Level_1.h"
#include "GameOver.h"
#include "WinScreen.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1600, 900);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {}
AppDelegate::~AppDelegate() {
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs() {
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
//static int register_all_packages()
//{
//    return 0; //flag for packages manager
//}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* director = Director::getInstance();
    GLView* glview = director->getOpenGLView();

    if(!glview) {
        glview = GLViewImpl::createWithRect("Detective Chad", Rect(0, 0, designResolutionSize.width, designResolutionSize.height), 1.0f, false);
		glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
        director->setOpenGLView(glview);
    }

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

#ifdef _DEBUG
	director->setDisplayStats(true);
#endif

    //// Set the design resolution
    //glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    //auto frameSize = glview->getFrameSize();
    //// if the frame's height is larger than the height of medium size.
    //if (frameSize.height > mediumResolutionSize.height)
    //{        
    //    director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    //}
    //// if the frame's height is larger than the height of small size.
    //else if (frameSize.height > smallResolutionSize.height)
    //{        
    //    director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    //}
    //// if the frame's height is smaller than the height of medium size.
    //else
    //{        
    //    director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    //}
    //register_all_packages();

    // Create and run the main menu scene
	cocos2d::Scene* mainMenuScene = MainMenu::createScene();
    director->runWithScene(mainMenuScene);
	
	//cocos2d::Scene* level1Scene = Level1::createScene();
	//director->runWithScene(level1Scene);
	
	//cocos2d::Scene* tutorialScene = Tutorial::createScene();
	//director->runWithScene(tutorialScene);

	/*cocos2d::Scene* gameOverScene = GameOver::createScene();
    director->runWithScene(gameOverScene);*/

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

//#if USE_AUDIO_ENGINE
//    AudioEngine::pauseAll();
//#elif USE_SIMPLE_AUDIO_ENGINE
//    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
//    SimpleAudioEngine::getInstance()->pauseAllEffects();
//#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

//#if USE_AUDIO_ENGINE
//    AudioEngine::resumeAll();
//#elif USE_SIMPLE_AUDIO_ENGINE
//    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
//    SimpleAudioEngine::getInstance()->resumeAllEffects();
//#endif
}


int WinScreen::mirrorScore, WinScreen::evidenceScore, WinScreen::timeScore, WinScreen::additionalScore, WinScreen::scoreScore, WinScreen::_levelID;
std::string WinScreen::ratingScore;

float Tutorial::time;
float Level1::time;

unsigned int Tutorial::levelID = 0;
unsigned int Level1::levelID = 1;