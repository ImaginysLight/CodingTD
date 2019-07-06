#include"CodeScene.h"


USING_NS_CC;



Scene* CodeScene::createScene()
{
	return CodeScene::create();
}

bool CodeScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	SetupGUI();
	
	//_client = SocketIO::connect("http://127.0.0.1:3000", *this);
 	Tool::Socket_Client->_client->on("_Get_Code_C_", CC_CALLBACK_2(CodeScene::onReceiveEvent, this));

	return true;
}

void CodeScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}  

void CodeScene::onReceiveEvent(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	//if (document.HasMember("result")) {
		CCLOG("error: %d ", document["error"].GetInt());
		CCLOG("detail: %s ", document["detail"].GetString());
	//}
}
void CodeScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	Button* term;
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		term = (Button*)pSender;
		if (term->getName() == "btn_Login") {
			if (editBox_Username->getText() == "")
			{
				CCLOG("Fail");
			}
			else
			{
				std::string code = editBox_Username->getText();
				//CCLOG("code %s ", code.c_str());
				Tool::Socket_Client->_client->emit("_Get_Code_C_", "{\"code\":\"" + code + "\", \"id_question\":\"5\"}");
			}

		}
		else if (term->getName() == "btn_Register") {
			//LoginScene::onClose(_client);
			Director::getInstance()->end();
		}
	}
	default: break;
	}
}

void CodeScene::SetupGUI()
{
	auto sp_SceneName = Sprite::create("UI/LoginScene/Login.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.9));
	this->addChild(sp_SceneName);

	auto sp_Background = Sprite::create("UI/Background/Default Background 1.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	editBox_Username = ui::EditBox::create(Size(visibleSize.width*0.9f, visibleSize.height*0.9f),"", "");
	editBox_Username->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
	editBox_Username->setTextHorizontalAlignment(TextHAlignment::LEFT);
	editBox_Username->setFontSize(20);
	editBox_Username->setFontColor(Color3B(175,225,200));
	editBox_Username->setPlaceHolder("code");
	editBox_Username->setPlaceholderFontColor(Color3B::GRAY);
	//editBox_Username->setMaxLength(20);
	//editBox_Username->setText("Player001");
	this->addChild(editBox_Username);

	/*editBox_Password = ui::EditBox::create(Size(visibleSize.width / 2, 30), "", "");
	editBox_Password->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.45));
	editBox_Password->setTextHorizontalAlignment(TextHAlignment::CENTER);
	editBox_Password->setFontSize(Tool::defaultTextSize);
	editBox_Password->setFontColor(Color3B(175,225,250));
	editBox_Password->setPlaceHolder("Password");
	editBox_Password->setPlaceholderFontColor(Color3B::GRAY);
	editBox_Password->setMaxLength(20);
	editBox_Password->setText("Player001");
	this->addChild(editBox_Password);*/

	btn_Login = Button::create("UI/LoginScene/btn_Login_nomal.png","UI/LoginScene/btn_Login_select.png");
	btn_Login->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.3));
	btn_Login->setName("btn_Login");
	btn_Login->addTouchEventListener(CC_CALLBACK_2(CodeScene::btn_Click, this));
	this->addChild(btn_Login);

	btn_Register = Button::create("UI/LoginScene/btn_Register_nomal.png", "UI/LoginScene/btn_Register_select.png");
	btn_Register->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.3));
	btn_Register->setName("btn_Register");
	btn_Register->addTouchEventListener(CC_CALLBACK_2(CodeScene::btn_Click, this));
	this->addChild(btn_Register);

	lbl_Notify = Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize);
	lbl_Notify->setTextColor(Color4B::RED);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.1));
	this->addChild(lbl_Notify,1);
}



void CodeScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}
