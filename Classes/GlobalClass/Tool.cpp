#include"Tool.h"
using namespace std;

int Tool::defaultTextSize = 20;
float Tool::currentIngameTime = 0;

SocketClient* Tool::Socket_Client = new SocketClient();

void Tool::setNodeSize(Node* node, int width, int height){
	node->setScaleX(width/ node->getBoundingBox().size.width);
	node->setScaleY(height / node->getBoundingBox().size.height);
}

void Tool::updateScale(Vector<Node*> node, int scaleX, int scaleY){
	for (auto x : node){
		x->setScaleX(x->getScaleX()*scaleX);
		x->setScaleY(x->getScaleY()*scaleY);
	}
}


string Tool::ConvertUTF16ToString(wstring utf16) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	std::string result = convert.to_bytes(utf16);
	return result;
}


void Tool::CutString(string* str, vector <string*> &vec, string cutPoint) {
	int root = 0;
	size_t pos = str->find(cutPoint);
	while (pos != std::string::npos) {
		string* temp = new string;
		*temp = str->substr(root, pos - root);
		vec.push_back(temp);
		root = pos + cutPoint.size();
		pos = str->find(cutPoint, pos + 1);
	}
	string* temp = new string;
	*temp = str->substr(root, str->size() - root);
	vec.push_back(temp);
}

int Tool::ConvertStringToInt(string a) {
	int result = 0;
	for (int i = 0; i < a.size(); i++) {
		result += ((int)a[a.size() - i - 1] - 48) * pow(10.0, i);
	}
	return result;
}

Label * Tool::CreateLabel(string content, int size, Color4B color, TextHAlignment align)
{
	auto lbl_Result = Label::create(content, "fonts/arial.ttf", size);
	lbl_Result->setTextColor(color);
	lbl_Result->setAlignment(align);
	return lbl_Result;
}

Button * Tool::CreateButtonWithoutSprite(string name, string titleText, int size, Color3B color)
{
	Button* btn_Result = Button::create();
	btn_Result->setName(name);
	btn_Result->setTitleText(titleText);
	btn_Result->setTitleFontSize(size);
	btn_Result->setTitleColor(color);
	return btn_Result;
}

Button * Tool::CreateButtonWithSpirte(string name, string spritePath)
{
	Button* btn_Result;
	try {
		btn_Result = Button::create(spritePath);
	}
	catch (string error) {
		btn_Result = Button::create();
	}
	btn_Result->setName(name);
	return btn_Result;
}

Node * Tool::CreateBar(string content, Color4B textColor, Size size, Color3B frontColor, Color4F backColor)
{
	Node* result = Node::create();
	auto frontBar = ProgressTimer::create(Sprite::create("Sprites/Health Bar.png"));
	frontBar->setType(ProgressTimer::Type::BAR);
	frontBar->setBarChangeRate(Vec2(1, 0));
	frontBar->setMidpoint(Vec2(0, 0));
	frontBar->setPercentage(100);
	frontBar->setAnchorPoint(Vec2(0, 0));
	frontBar->setColor(frontColor);
	Tool::setNodeSize(frontBar, size.width, size.height);
	frontBar->setName("Front Bar");
	frontBar->setAnchorPoint(Vec2(0.5, 0.5));
	result->addChild(frontBar);

	auto background = DrawNode::create();
	background->clear();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(0, 0);
	rectangle[1] = Vec2(0, frontBar->getBoundingBox().size.height);
	rectangle[2] = Vec2(frontBar->getBoundingBox().size.width, frontBar->getBoundingBox().size.height);
	rectangle[3] = Vec2(frontBar->getBoundingBox().size.width, 0);
	background->drawPolygon(rectangle, 4, backColor, 1, backColor);
	background->setName("Background");
	background->setPosition(-Vec2(frontBar->getBoundingBox().size.width / 2, frontBar->getBoundingBox().size.height / 2));
	result->addChild(background, -1);

	auto lbl_Content = Label::create(content, "fonts/custom_font.ttf", Tool::defaultTextSize,Size::ZERO,cocos2d::TextHAlignment::CENTER);
	lbl_Content->setTextColor(Color4B::WHITE);
	lbl_Content->setName("Content");
	lbl_Content->setTextColor(textColor);
	result->addChild(lbl_Content, 1);
	return result;
}

void Tool::Button_ChangeState(Button *& btn, bool isShow, float fadeTime)
{
	if (isShow) {
		btn->setVisible(true);
		btn->setEnabled(true);
		btn->runAction(FadeIn::create(fadeTime));
	}
	else {
		btn->setEnabled(false);
		btn->runAction(FadeOut::create(fadeTime));
	}
}

int Tool::CreateRandomNumber(int begin, int end)
{
	/*
	//Hóa ra trước giờ mình bị lừa @@
	srand(time(NULL));
	return rand() % (end - begin + 1) + begin;
	*/
	random_device rd;	// only used once to initialize (seed) engine
	mt19937 rng(rd());	// random-number engine used (Mersenne-Twister in this case)

	uniform_int_distribution<int> uni(begin, end);
	auto random_integer = uni(rng);
	return random_integer;
}


Node * Tool::CreateNotificationTable(string lblContent, string btnRightContent, string btnLeftContent, Size tableSize)
{
	Node* result = Node::create();
	Sprite* sp_Background = Sprite::create("UI/NotifyBackground.png");
	Tool::setNodeSize(sp_Background, tableSize.width, tableSize.height);
	result->addChild(sp_Background,-1);

	Label* lbl_Content = Tool::CreateLabel(lblContent,Tool::defaultTextSize,Color4B::WHITE, TextHAlignment::CENTER);
	lbl_Content->setName("lbl_Content");
	lbl_Content->setAnchorPoint(Vec2(0.5, 0));
	lbl_Content->setMaxLineWidth(tableSize.width - 10);
	result->addChild(lbl_Content);

	Button* btn_Right = Tool::CreateButtonWithoutSprite("btn_Right", btnRightContent);
	btn_Right->addTouchEventListener([&](Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
		((Node*)pSender)->getParent()->runAction(RemoveSelf::create());
	});
	btn_Right->setTitleColor(Color3B::RED);
	result->addChild(btn_Right);

	if (btnLeftContent == "") {
		btn_Right->setPositionY(-tableSize.height/4);
	}
	else {
		btn_Right->setPosition(Vec2(tableSize.width / 4, -tableSize.height / 4));
		Button* btn_Left = Tool::CreateButtonWithoutSprite("btn_Left", btnLeftContent);
		btn_Left->setPosition(Vec2(-tableSize.width / 4, -tableSize.height / 4));
		btn_Left->setTitleColor(Color3B::GREEN);
		result->addChild(btn_Left);
	}

	return result;
}

EditBox * Tool::CreateEditBox(string placeholder, Size size)
{
	EditBox* result;
	result = ui::EditBox::create(size, "", "");
	result->setTextHorizontalAlignment(TextHAlignment::CENTER);
	result->setInputMode(EditBox::InputMode::ANY);
	result->setFontSize(Tool::defaultTextSize);
	result->setPlaceHolder(placeholder.c_str());
	result->setMaxLength(100);

	auto sp_EditBox = Sprite::create("UI/Login/editbox.png");
	sp_EditBox->setAnchorPoint(Vec2(0, 0));
	Tool::setNodeSize(sp_EditBox, result->getBoundingBox().size.width, result->getBoundingBox().size.height);
	result->addChild(sp_EditBox, -1);
	return result;
}
