#include"RegisterScene.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d::ui;
USING_NS_CC;


Scene* RegisterScene::createScene()
{
	return RegisterScene::create();
}


bool RegisterScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	SetupGUI();
	Tool::Socket_Client->_client->on("Register", CC_CALLBACK_2(RegisterScene::onReceiveEvent_Register, this));
	return true;
}


void RegisterScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void RegisterScene::btn_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		if (name == "btn_Exit") Director::getInstance()->replaceScene(LoginScene::createScene());
		else if (name == "btn_Register") {
			string username = editBox_Username->getText();
			string password = editBox_Password->getText();
			string retype = editBox_RetypePassword->getText();
			string securityCode = editBox_SecurityCode->getText();
			if (username.size() < 1 || password.size() < 1 || retype.size() < 1 || securityCode.size() < 1) {
				RunActionNotify("Please fill in all required fields.");
			}
			else if (password != retype) {
				RunActionNotify("Retype Password does not match!");
			}
			else if (securityCode != code) {
				RunActionNotify("Security Code does not match!");
			}
			else {
				Tool::Socket_Client->_client->emit("Register", "{\"username\":\"" + username + "\",\"password\":\"" + password + "\"}");
			}
		}
	}
}

void RegisterScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}


void RegisterScene::SetupGUI()
{
	auto sp_Background = Sprite::create("UI/Login/BG.png"); 
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	

	auto sp_Register = Sprite::create("UI/Login/head_register.png");
	sp_Register->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*.8));
	this->addChild(sp_Register);

	lbl_Notify = Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize);
	lbl_Notify->setTextColor(Color4B::RED);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.1));
	this->addChild(lbl_Notify, 1);

	auto lbl_Username = Tool::CreateLabel("Username", Tool::defaultTextSize, Color4B(175, 225, 200, 255));
	lbl_Username->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.6));
	lbl_Username->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_Username);

	editBox_Username = Tool::CreateEditBox("Username");
	editBox_Username->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.525));
	editBox_Username->setMaxLength(20);
	editBox_Username->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(editBox_Username);

	for (int i = 0; i < 4; i++) {
		RegisterScene::code += to_string(Tool::CreateRandomNumber(0, 69));
	}

	auto lbl_SecurityCode = Tool::CreateLabel("Security Code: " + code, Tool::defaultTextSize, Color4B(175, 225, 250, 255));
	lbl_SecurityCode->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.4));
	lbl_SecurityCode->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_SecurityCode);

	editBox_SecurityCode = Tool::CreateEditBox("Security Code");
	editBox_SecurityCode->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.325));
	editBox_SecurityCode->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(editBox_SecurityCode);

	auto lbl_Password = Tool::CreateLabel("Password", Tool::defaultTextSize, Color4B(175, 225, 200, 255));
	lbl_Password->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.6));
	lbl_Password->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_Password);

	editBox_Password = Tool::CreateEditBox("Password");
	editBox_Password->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.525));
	editBox_Password->setAnchorPoint(Vec2(0, 0.5));
	editBox_Password->setMaxLength(20);
	editBox_Password->setInputFlag(EditBox::InputFlag::PASSWORD);
	this->addChild(editBox_Password);

	auto lbl_RetypePassword = Tool::CreateLabel("Retype Password", Tool::defaultTextSize, Color4B(175, 225, 250, 255));
	lbl_RetypePassword->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.4));
	lbl_RetypePassword->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_RetypePassword);

	editBox_RetypePassword = Tool::CreateEditBox("Retype Password");
	editBox_RetypePassword->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.325));
	editBox_RetypePassword->setAnchorPoint(Vec2(0, 0.5));
	editBox_RetypePassword->setInputFlag(EditBox::InputFlag::PASSWORD);
	this->addChild(editBox_RetypePassword);

	auto btn_Register = Button::create("UI/Login/btn_register.png");
	btn_Register->setName("btn_Register");
	btn_Register->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.15));
	btn_Register->addTouchEventListener(CC_CALLBACK_2(RegisterScene::btn_Click, this));
	this->addChild(btn_Register);

	auto btn_Exit = Button::create("UI/Lobby/btn_exit.png");
	btn_Exit->setName("btn_Exit");
	btn_Exit->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.15));
	btn_Exit->addTouchEventListener(CC_CALLBACK_2(RegisterScene::btn_Click, this));
	this->addChild(btn_Exit);
}

void RegisterScene::onReceiveEvent_Register(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document.HasMember("Check")) {
		//CCLOG("Check: %d ", document["Check"].GetInt());
		if (document["Check"].GetInt() == 0) {
			auto node_Notify = Tool::CreateNotificationTable("Successfully Registered.", "OK");
			node_Notify->setPosition(visibleSize / 2);
			this->addChild(node_Notify, 10);
		}
		else if (document["Check"].GetInt() == -1) {
			auto node_Notify = Tool::CreateNotificationTable("This Username already in use. Please try another.", "OK");
			node_Notify->setPosition(visibleSize / 2);
			this->addChild(node_Notify, 10);
		}
	}
}