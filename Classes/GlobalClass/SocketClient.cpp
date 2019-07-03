#include "SocketClient.h"
#include "json\document.h"
#include "json\rapidjson.h"
#include <network/SocketIO.h>
#include"Player.h"
USING_NS_CC;

//SIOClient* SocketClient::_client = SocketIO::connect("http://127.0.0.1:3000", this);

void SocketClient::onConnect(SIOClient* client) {
	// SocketIO::connect success
	//CCLOG("connect success");
}
void SocketClient::onMessage(SIOClient* client, const std::string& data) {
	 //SocketIO::send receive
	//CCLOG("receive %s " , data);
}
void SocketClient::onClose(SIOClient* client) {
	// SocketIO::disconnect success
	///CCLOG("disconnect success");
}
void SocketClient::onError(SIOClient* client, const std::string& data) {
	// SocketIO::failed
	//CCLOG("onError");
}


