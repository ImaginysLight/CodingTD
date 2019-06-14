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

	//Label chữ tutorial (tạo cái sprite coi)
	{
		Label* lbl_Tutorial = Tool::CreateLabel("Tutorial", Tool::defaultTextSize * 2);
		lbl_Tutorial->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*.9));
		this->addChild(lbl_Tutorial);
	}

	auto sp_Background = Sprite::create("UI/LoginScene/background1.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	// Button ← →
	{
		btn_Back = Button::create();
		btn_Back->setTitleText(Tool::ConvertUTF16ToString(L"← Back"));
		btn_Back->setTitleFontSize(Tool::defaultTextSize * 1.5);
		btn_Back->setTitleColor(Color3B::GREEN);
		btn_Back->setPosition(Vec2(visibleSize.width*0.08, visibleSize.height / 2));
		btn_Back->addTouchEventListener(CC_CALLBACK_2(TutorialScene::onClick, this));
		btn_Back->setName("btn_Back");
		this->addChild(btn_Back);

		btn_Next = Button::create();
		btn_Next->setTitleText(Tool::ConvertUTF16ToString(L"Next →"));
		btn_Next->setTitleFontSize(Tool::defaultTextSize * 1.5);
		btn_Next->setTitleColor(Color3B::GREEN);
		btn_Next->setPosition(Vec2(visibleSize.width*0.92, visibleSize.height / 2));
		btn_Next->addTouchEventListener(CC_CALLBACK_2(TutorialScene::onClick, this));
		btn_Next->setName("btn_Next");
		this->addChild(btn_Next);

		btn_Exit = Button::create("UI/LobbyScene/btn_Exit_nomal.png", "UI/LobbyScene/btn_Exit_select.png");
		btn_Exit->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height * 0.1));
		btn_Exit->addTouchEventListener(CC_CALLBACK_2(TutorialScene::onClick, this));
		btn_Exit->setName("btn_Exit");
		this->addChild(btn_Exit);
	}

	// Thông tin hướng dẫn
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Chào mừng đến với CodingTD Online\nGame vừa thủ thành đối kháng vừa học lập trình hay nhất vũ trụ!"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Hãy chơi thử trước nào!\nBạn có thể bấm Play để tìm đối thủ ngẫu nhiên\nhoặc bấm Extend để tạo phòng."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Đầu tiên, hãy chọn 1 trong 3 Flamed Kingdom, Frozen Kingdom, Blessed Kingdom\nđại diện cho 3 hệ Fire, Ice, Nature."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Đối phương sẽ không biết bạn chọn Kingdom gì cho tới khi hết lượt\nTrận đấu sẽ bị hủy nếu có người không chọn Kingdom!"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"TIếp theo, bạn có thể cấm tối đa 2 thẻ mua lính của đối phương."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Bạn được chọn tối đa 4 thẻ mua lính.\nNhững thẻ màu xám là đã bị cấm bởi đối phương."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Ngôi nhà to nhất bạn thấy chính là Kingdom của bạn.\nBạn phải đánh sập Kingdom đối phương, nằm phía tay phải cách xa bạn 3100 pixel, để chiến thắng"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Đây là thanh mua lính, trên đó có các thẻ bạn đã chọn, và 2 thẻ đặc biệt tương ứng với Kingdom của bạn. Hãy kéo thẻ ra một trong 3 đường để mua lính."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Ngoài Buy còn có 2 chế độ là Upgrade để nâng cấp lính, và View để xem thông tin, và nút Up↑ để nâng cấp nhà chính"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Thông thường, lính chỉ có thể tấn công trên đường của mình.\nNhưng lính ở cả 3 đường đều có thể tấn công Kingdom."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Có 3 loại tài nguyên quan trọng trong trận đấu.\nGold dùng để mua lính và nâng cấp.\nKnowledge dùng để nâng cấp.\nEnergy dùng để sử dụng Skill."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Mỗi hệ có 3 skill riêng, gồm 2 chủ động và 1 bị động. Có thể chuyển sang mode View và bấm vào Skill để xem chi tiết."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Phía trên là bảng câu hỏi, lần lượt 2 người chơi sẽ được chọn độ khó cho câu hỏi tiếp theo."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Thời gian tồn tại của câu hỏi phụ thuộc vào độ khó.\nBạn sẽ nhận được Gold tùy vào kết quả trả lời, và 1 Knowledge cho câu trả lời đúng."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Phía tay phải là khung chat, bạn nhập nội dung vào ô và bấm nút Send để gửi tin nhắn đi."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Bây giờ bạn đã nắm được cách chơi cơ bản, hãy kết thúc trận đấu và xem thành quả."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Bạn sẽ nhận được kinh nghiệm dựa trên những gì bạn đã thể hiện trong trận đấu. Khi đạt đủ kinh nghiệm, bạn sẽ lên cấp và nhận được 1 Friendship Point."));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Bạn sẽ nhận được cúp dựa trên số trận thắng, số quân địch hạ gục, và số câu trả lời đúng"));
	labelContent.push_back(Tool::ConvertUTF16ToString(L"Vậy là bạn đã nắm được tổng quan về cách chơi, hãy đứng dậy hít một hơi và chúng ta đi sâu vào chi tiết."));

	for (auto content : labelContent) {
		Label* lbl = Tool::CreateLabel(content, Tool::defaultTextSize, Color4B::WHITE, CCTextAlignment::CENTER);
		vecLabel.push_back(lbl);

		Sprite* sp = Sprite::create("UI/TutorialScene/background.png");
		vecSprite.push_back(sp);
	}

	//Set thông số cho các Label và Sprite trong Tutorial
	{
		for (auto lbl : vecLabel) {
			lbl->setVisible(false);
			lbl->setWidth(500);
			lbl->setAlignment(CCTextAlignment::CENTER);
			lbl->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.2));
			lbl->setAnchorPoint(Vec2(0.5, 1));
			this->addChild(lbl);
		}
		for (auto sp : vecSprite) {
			sp->setVisible(false);
			Tool::setNodeSize(sp, 550, 300);
			sp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.5));
			this->addChild(sp);
		}
		
	}

	//Hiển thị trang 1
	{
		vecLabel[currentPage]->setVisible(true);
		vecSprite[currentPage]->setVisible(true);
	}

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

void TutorialScene::onClick(Ref * sender, Widget::TouchEventType type)
{
	string name = ((Node*)sender)->getName();
	if (type == Widget::TouchEventType::ENDED) {
		// Back
		if (name == "btn_Back") {
			if (currentPage > 0) {
				//Khóa button trong lúc chuyển trang
				btn_Back->setEnabled(false);
				btn_Next->setEnabled(false);
				vecLabel[currentPage]->runAction(Sequence::create(DelayTime::create(1),
					CallFunc::create([&]() {	btn_Back->setEnabled(true);
												btn_Next->setEnabled(true);
												currentPage--;
					}),
				nullptr));

				// Hiệu ứng chuyển trang cũ
				vecLabel[currentPage]->runAction(Sequence::create(MoveBy::create(0.4, Vec2(1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage]->setVisible(false);
												vecSprite[currentPage]->setVisible(false);
					}),
					MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height*0.2)),
				nullptr));

				vecSprite[currentPage]->runAction(Sequence::create(MoveBy::create(0.4, Vec2(1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage]->setVisible(false);
												vecSprite[currentPage]->setVisible(false);
					}),
					MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height*0.5)),
				nullptr));

				// Hiệu ứng đổi trang mới

				vecLabel[currentPage - 1]->runAction(Sequence::create(MoveBy::create(0.4, Vec2(-1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage - 1]->setVisible(true);
												vecSprite[currentPage - 1]->setVisible(true);
					}),
					MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height*0.2)),
				nullptr));

				vecSprite[currentPage - 1]->runAction(Sequence::create(MoveBy::create(0.4, Vec2(-1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage - 1]->setVisible(true);
												vecSprite[currentPage - 1]->setVisible(true);
					}),
					MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height*0.5)),
				nullptr));
			}
		}
		// Next
		else if (name == "btn_Next") {
			if (currentPage < vecLabel.size()-1) {
				//Khóa button trong lúc chuyển trang
				btn_Back->setEnabled(false);
				btn_Next->setEnabled(false);
				vecLabel[currentPage]->runAction(Sequence::create(DelayTime::create(1),
					CallFunc::create([&]() {	btn_Back->setEnabled(true);
												btn_Next->setEnabled(true);
												currentPage++;
					}), 
				nullptr));

				// Hiệu ứng chuyển trang cũ
				vecLabel[currentPage]->runAction(Sequence::create(MoveBy::create(0.4, Vec2(-1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage]->setVisible(false); 
												vecSprite[currentPage]->setVisible(false);
					}),
					MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height*0.2)),
				nullptr));

				vecSprite[currentPage]->runAction(Sequence::create(MoveBy::create(0.4, Vec2(-1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage]->setVisible(false);
												vecSprite[currentPage]->setVisible(false);
					}),
					MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height*0.5)),
				nullptr));
				
				// Hiệu ứng đổi trang mới

				vecLabel[currentPage+1]->runAction(Sequence::create(MoveBy::create(0.4, Vec2(1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage+1]->setVisible(true);
												vecSprite[currentPage+1]->setVisible(true);
					}),
					MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height*0.2)),
				nullptr));

				vecSprite[currentPage+1]->runAction(Sequence::create(MoveBy::create(0.4, Vec2(1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage+1]->setVisible(true);
												vecSprite[currentPage+1]->setVisible(true);
					}),
					MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height*0.5)),
				nullptr));
			}
		}
		else if (name == "btn_Exit")
		{
			Director::getInstance()->replaceScene(LobbyScene::createScene());
		}
	}

}

