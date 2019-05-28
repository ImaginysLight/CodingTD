#ifndef __SOCKETCLIENT_SCENE_H__
#define __SOCKETCLIENT_SCENE_H__

#include "cocos2d.h"
#include "ui/cocosGUI.h"

#include <network/SocketIO.h>

using namespace cocos2d::network;
using namespace cocos2d::ui;

static class SocketClient : public SocketIO::SIODelegate
{
public:
	// socket.io even\vent listener
	//std::string onReceiveEvent(SIOClient* client, const std::string& data);
	// SIODelegate
	virtual void onConnect(SIOClient* client);
	virtual void onMessage(SIOClient* client, const std::string& data);
	virtual void onClose(SIOClient* client);
	virtual void onError(SIOClient* client, const std::string& data);
	
	//void Check_Login();
	SIOClient* _client = SocketIO::connect("http://127.0.0.1:3000", *this);
};

#endif // __SOCKETCLIENT_SCENE_H__