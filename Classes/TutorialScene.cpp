#include"TutorialScene.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d::ui;
USING_NS_CC;


Scene* TutorialScene::createScene()
{
	return TutorialScene::create();
}


bool TutorialScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	ScrollView_TutorialList = ui::ScrollView::create();
	ScrollView_TutorialList->setContentSize(Size(visibleSize.width, visibleSize.height*0.8));
	ScrollView_TutorialList->setInnerContainerSize(Size(1000, 2000));
	ScrollView_TutorialList->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.4f));
	ScrollView_TutorialList->setAnchorPoint(Vec2(0.5, 0.5));
	ScrollView_TutorialList->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
	ScrollView_TutorialList->setBounceEnabled(true);
	this->addChild(ScrollView_TutorialList);


	//Label chữ tutorial (tạo cái sprite coi)
	{
		Label* lbl_Tutorial = Tool::CreateLabel("Tutorial", Tool::defaultTextSize * 2);
		lbl_Tutorial->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*.9));
		this->addChild(lbl_Tutorial);
	}

	auto sp_Background = Sprite::create("UI/LoginScene/background1.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	btn_Exit = Tool::CreateButtonWithoutSprite("btn_Exit", " << Back To Lobby");
	btn_Exit->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height * 0.1));
	btn_Exit->addTouchEventListener(CC_CALLBACK_2(TutorialScene::btn_Click, this));
	btn_Exit->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(1, Vec2(25, 0)),
		MoveBy::create(1, Vec2(-25, 0)),
		nullptr)));
	this->addChild(btn_Exit,2);
	

	// Thông tin hướng dẫn
	/*labelContent.push_back(Tool::ConvertUTF16ToString(L"Chào mừng đến với CodingTD Online\nGame vừa thủ thành đối kháng vừa học lập trình hay nhất vũ trụ!"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Hãy chơi thử trước nào!\nBạn có thể bấm Play để tìm đối thủ ngẫu nhiên\nhoặc bấm Extend để tạo phòng."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Đầu tiên, hãy chọn 1 trong 3 Flamed Kingdom, Frozen Kingdom, Blessed Kingdom\nđại diện cho 3 hệ Fire, Ice, Nature."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Đối phương sẽ không biết bạn chọn Kingdom gì cho tới khi hết lượt\nTrận đấu sẽ bị hủy nếu có người không chọn Kingdom!"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"TIếp theo, bạn có thể cấm tối đa 2 thẻ mua lính của đối phương."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Bạn được chọn tối đa 4 thẻ mua lính.\nNhững thẻ màu xám là đã bị cấm bởi đối phương."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Ngôi nhà to nhất bạn thấy chính là Kingdom của bạn.\nBạn phải đánh sập Kingdom đối phương, nằm phía tay phải cách xa bạn 3100 pixel, để chiến thắng"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Có 3 loại tài nguyên quan trọng trong trận đấu.\nGold dùng để mua lính và nâng cấp.\nKnowledge dùng để nâng cấp.\nEnergy dùng để sử dụng Skill."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Ngoài ra, mỗi đơn vị sẽ tốn 1 Food, không thể mua thêm lính nếu Food đạt giới hạn."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Đây là thanh mua lính, trên đó có các thẻ bạn đã chọn, và 2 thẻ đặc biệt tương ứng với Kingdom của bạn. Hãy kéo thẻ ra một trong 3 đường để mua lính."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Chọn nút Upgrade để nâng cấp lính, Kingdom, hoặc Farm (+1 Food/level)"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Thông thường, lính chỉ có thể tấn công trên đường của mình.\nNhưng lính ở cả 3 đường đều có thể tấn công Kingdom."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Mỗi hệ có 3 skill riêng, gồm 2 chủ động và 1 bị động. Có thể chuyển sang mode View và bấm vào Skill để xem chi tiết."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Phía trên là bảng câu hỏi, lần lượt 2 người chơi sẽ được chọn độ khó cho câu hỏi tiếp theo."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Thời gian tồn tại của câu hỏi phụ thuộc vào độ khó.\nBạn sẽ nhận được Gold tùy vào kết quả trả lời, và 1 Knowledge cho câu trả lời đúng."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Phía tay phải là khung chat, bạn nhập nội dung vào ô và bấm nút Send để gửi tin nhắn đi."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Bây giờ bạn đã nắm được cách chơi cơ bản, hãy kết thúc trận đấu và xem thành quả."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Bạn sẽ nhận được kinh nghiệm dựa trên những gì bạn đã thể hiện trong trận đấu. Khi đạt đủ kinh nghiệm, bạn sẽ lên cấp và nhận được 1 Friendship Point."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Bạn sẽ nhận được cúp dựa trên số trận thắng, số quân địch hạ gục, và số câu trả lời đúng"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Vậy là bạn đã nắm được tổng quan về cách chơi, hãy đứng dậy hít một hơi và chúng ta đi sâu vào chi tiết."));*/

	labelContent.push_back(Tool::ConvertUTF16ToString(L"Welcome to Coding TD Online\nThe best learning-while-playing in this universe!"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Let's try your first game!\nYou can click Play to find your opponent randomly, or click Extend to create a room."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Firstly, you have to choose 1 of 3 Flamed Kingdom, Frozen Kingdom, Blessed Kingdom, representative of 3 elements Fire, Ice, Nature."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"This turn is secret pick, so you can't see your opponent's Kingdom until next turn. If anyone doesn't choose Kingdom, the game will be canceled"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"In the second turn, you can BAN up to 2 cards of your opponent."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"And the last turn, you can choose up to 4 cards. The gray card mean it has been banned by your opponent."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Now we enter the game. The building you're seeing is your Kingdom. You should protect it while trying to destroy your opponent one for victory."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"There are 3 important resources. Gold (+5 per sec) to buy unit and upgrade, Knowledge to upgrade, and Energy (+1 per sec) to use skills."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Pay attention to your farm. Each unit in your army will use 1 food, so you can't buy more when it cap the limit."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"This is Buy bar, with the card you choose and 2 special cards of your element. Drop and drag card to the line to buy it."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Choose Upgrade button for upgrade your cards, Kingdom (expand 25 energy cap) or Farm (+1 food / level)."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"In normal circumstance, your unit only attacks in their line, but they can attack Kingdom from any line."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Each element has 2 active and 1 passive skill. Your element's passive skill will be improved for each correct answer."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Click here to open Question Table, you and your opponent can choose difficulty for the next question sequentially."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"The lifetime of question depend on its difficulty. You will receive Gold depend on your answer, and 1 Knowledge for a Correct Answer."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"This is chat box, you can type whatever you want then press Send button. Some important infomation of the game will be showed here."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Now you knew basic gameplay, let's end this game and see your result."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"You will receive Experience depend on your result, when you collect enough Experience, you level up and receive 1 Friendship Point."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"And you receive Trophy depend on your achievement. That's all for general, now let's go to details."));

	for (int i = 0; i < labelContent.size(); i++) {
		Label* lbl = Tool::CreateLabel(labelContent[i], Tool::defaultTextSize, Color4B::WHITE, TextHAlignment::CENTER);
		vecLabel.push_back(lbl);
		lbl->setWidth(500);
		lbl->setAlignment(TextHAlignment::CENTER);
		lbl->setPosition(Vec2(visibleSize.width * (i + 0.5), visibleSize.height*0.4));
		lbl->setAnchorPoint(Vec2(0.5, 1));
		ScrollView_TutorialList->addChild(lbl);

		Sprite* sp = Sprite::create("UI/TutorialScene/background.png");
		vecSprite.push_back(sp);
		Tool::setNodeSize(sp, 550, 300);
		sp->setPosition(Vec2(visibleSize.width * (i + 0.5), visibleSize.height*0.8));
		ScrollView_TutorialList->addChild(sp);
	}

	ScrollView_TutorialList->setInnerContainerSize(Size(visibleSize.width*labelContent.size(),visibleSize.height));

	return true;
}


void TutorialScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void TutorialScene::btn_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		if (name == "btn_Exit") Director::getInstance()->replaceScene(LobbyScene::createScene());
	}
}
