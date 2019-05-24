//
//  LobbyScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/22.
//

#include "LobbyScene.hpp"
#include "SettingScene.hpp"
#include "RankScene.hpp"
#include "FriendScene.hpp"
#include "AssisstanceFunc.hpp"
#include <sstream>

#include <thread>
#include <nlohmann/json.hpp>

#include "User.hpp"
#include "NetworkCom.hpp"

USING_NS_CC;

// The images for the buttons.
static const std::string kNormalButtonImage = "lobby-btn-fullwidth.png";
static const std::string kSelectedButtonImage = "lobby-btn-fullwidth2.png";
static const std::string kDisabledButtonImage = "lobby-btn-fullwidth.png";

/// Padding for the UI elements.
static const float kUIElementPadding = -20;

/// The title text size for the Firebase buttons.
static const float kButtonTitleFontSize = 45.0;

/// The content size for the Firebase buttons.
static const cocos2d::Size kButtonContentSize = cocos2d::Size(400, 100);





// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

Scene *LobbyScene::createScene(){
    return LobbyScene::create();
}

// on "init" you need to initialize your instance
bool LobbyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //add backbround
    auto backGroundColor = CCLayerColor::create(ccc4(236, 207, 177, 255)); //RGBA
    this->addChild(backGroundColor, 0);
    
    //==============================================================================================================
    //Button X pos
    const float  ButtonXPosition = origin.x + visibleSize.width - 100;
    
    //Rank button
    auto RankButton = createButton(true, "Rank", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    nextYPosition = origin.y + visibleSize.height * 2 / 3;
    RankButton->setPosition(Vec2(ButtonXPosition, nextYPosition));
    RankButton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::RankCallback, this));
    
    this->addChild(RankButton);
    //Store button
    auto StoreButton = createButton(true, "Store", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    this->addChild(StoreButton);
    
    //Friend button
    auto FriendButton = createButton(true, "Friend", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    FriendButton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::FriendCallback, this));
    this->addChild(FriendButton);
    
    //Setting button
    auto SettingButton = createButton(true, "Setting", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    SettingButton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::SettingCallback, this));
    this->addChild(SettingButton);
    //==============================================================================================================
    
    //======================================
    //get User information
    
    std::thread mythread([](){
        auto client = Client::getInstance();
        
        /*
        if(re["Nick Name"] == ""){
            Client::getInstance()->userChangenickname("test Name");
        }
        auto user = User::getInstance();
        user->setNickName(re["Nick Name"]);
        user->setWin(re["User Win"]);
        user->setLoss(re["User Loss"]);
        user->setMoney(re["User Money"]);
        */
        
    });
    
    mythread.join();
    
    
    //======================================
    
    //Username Label
    const std::string Username = User::getInstance()->getNickName();
    
    auto UsernameLabel = Label::createWithTTF(Username, "fonts/arial.ttf", 40);
    UsernameLabel->setAnchorPoint(Vec2(0,1)); //以左上角為緢點
    UsernameLabel->setColor(Color3B::BLACK);
    UsernameLabel->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - 20));
    
    this->addChild(UsernameLabel);
    

    //Hash uid Label
    unsigned int IntUID = User::getInstance()->getUID();
    std::stringstream sUID;
    sUID << IntUID; // int to string
    auto IntUIDLabel = Label::createWithTTF(sUID.str(), "fonts/arial.ttf", 30);
    IntUIDLabel->setAnchorPoint(Vec2(0,1)); //以左上角為緢點
    IntUIDLabel->setColor(Color3B::BLACK);
    IntUIDLabel->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - 105));
    
    CCUserDefault::sharedUserDefault()->setStringForKey("UID", sUID.str());
    
    this->addChild(IntUIDLabel);

    //User W/L information
    int win = User::getInstance()->getWin(), lose = User::getInstance()->getLoss();
    //win = CCUserDefault::sharedUserDefault()->getIntegerForKey("win");
    //lose = CCUserDefault::sharedUserDefault()->getIntegerForKey("lose");
    
    auto MyScore = Label::createWithTTF("My Score:", "fonts/arial_Bold.ttf", 100);
    MyScore->setPosition(Vec2(origin.x + visibleSize.width/4, origin.y+visibleSize.height*2/3));
    MyScore->setColor(Color3B::BLACK);
    std::string WinAndLoss = std::to_string(win) + "W" + " " +std::to_string(lose) + "L";
    
    auto Score = Label::createWithTTF(WinAndLoss, "fonts/arial_Bold.ttf", 100);
    Score->setPosition(Vec2(origin.x + visibleSize.width/4, origin.y+visibleSize.height*2/3 - MyScore->getContentSize().height ));
    Score->setColor(Color3B::BLACK);
    this->addChild(MyScore);
    this->addChild(Score);
    
    
    //start Game button
    const std::string gameButtonPath = "startgame-btn.png"; ////3245 × 591
    const std::string gameButtonSelectedPath = "startgame-btn-click.png"; ////3245 × 591
    auto gameButton = createButton(true, "Game", Color3B::BLACK, gameButtonPath, gameButtonSelectedPath, gameButtonPath);
    gameButton->setContentSize(Size(3245/4, 591/4));
    gameButton->setTitleFontSize(85);
    gameButton->setAnchorPoint(Vec2(0, 0.5));
    gameButton->setPosition(Vec2(origin.x + 100, origin.y + visibleSize.height/4));
    gameButton->setTitleOffset(0, 0);
    this->addChild(gameButton);
    
    
    
    return true;
    
    
    
    
}


cocos2d::ui::Button* LobbyScene::createButton(
                                                 bool buttonEnabled, const std::string& buttonTitleText,
                                                 const cocos2d::Color3B& buttonColor, const std::string& ImagePath1, const std::string& ImagePath2, const std::string& ImagePath3) {
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    cocos2d::ui::Button* button = cocos2d::ui::Button::create(
                                                              ImagePath1, ImagePath2, ImagePath3);
    
    const float  ButtonXPosition = origin.x + visibleSize.width - 100;
    
    button->setEnabled(buttonEnabled);
    button->setTitleColor(buttonColor);
    button->setTitleText(buttonTitleText);
    button->setTitleFontSize(kButtonTitleFontSize);
    button->ignoreContentAdaptWithSize(false);
    button->setContentSize(kButtonContentSize);
    nextYPosition -= button->getContentSize().height + kUIElementPadding;
    button->setPosition(cocos2d::Vec2(ButtonXPosition, nextYPosition));
    button->setTitleOffset(-80, 0);
    
    return button;
}
//Select Setting button call back
void LobbyScene::SettingCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            auto scene = SettingScene::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);
            break;
        }
        
        default:
            break;
       
    }
}
//Select Rank button call back
void LobbyScene::RankCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            auto scene = RankScene::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);
            break;
        }
            
        default:
            break;
            
    }
}
//Select Friend button call back
void LobbyScene::FriendCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            auto scene = FriendScene::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);
            break;
        }
            
        default:
            break;
            
    }
}





