#include <Arduino.h>
#include "config.h"
// #define H4P_VERBOSE 1
#include <H4Plugins.h>
H4_USE_PLUGINS(PROJ_BAUD_RATE, H4_Q_CAPACITY, false) // Serial baud rate, Q size, SerialCmd autostop

H4P_SerialLogger h4sl;
H4P_PinMachine h4gm;

#ifdef ARDUINO_ARCH_ESP8266
std::string name = "ESP8266";
#define BIG_SIZE 500
#else
std::string name = "ESP32";
#define BIG_SIZE 13000
#endif

#if H4P_USE_WIFI_AP
H4P_WiFi h4wifi(name);
#else
H4P_WiFi h4wifi(WIFI_SSID, WIFI_PASS, name);
#endif

#if USE_BLESERVER
H4P_BLEServer h4ble;
bool bleConnected;
#endif
#if USE_BLECLIENT
H4P_BLEClient h4bleclient;
#endif

#if USE_MQTT
#if H4P_USE_WIFI_AP
H4P_AsyncMQTT h4mqtt;
#else
H4P_AsyncMQTT h4mqtt(MQTT_SERVER);
#endif // H4P_USE_WIFI_AP
uint8_t big[BIG_SIZE];
H4_TIMER mqttSender;
H4_TIMER bigSender;
#endif // USE_MQTT

H4P_Heartbeat h4hb;
H4P_BinarySwitch h4onoff(4, ACTIVE_LOW, H4P_UILED_ORANGE, OFF, 10000);
H4P_UPNPServer h4upnp("H4Plugins Environment");

#if USE_HTTPREQ
H4P_AsyncHTTP h4ah;
H4_TIMER httpReqTimer;
void HTTPClient();
#endif
void publishDevice(const std::string &topic, const std::string &payload);
void publishDevice(const std::string &topic, long long payload);

void onWiFiConnect() {
	Serial.printf("Connected, IP: %s\n",WiFi.localIP().toString().c_str());
#if USE_HTTPREQ
	h4.queueFunction(HTTPClient);
	httpReqTimer = h4.every(60000, HTTPClient);
#endif
}
void onWiFiDisconnect() {
	Serial.printf("WiFi Disconnected\n");
#if USE_HTTPREQ
	h4.cancel(httpReqTimer);
#endif
}
#if USE_MQTT
void onMQTTConnect() {
	mqttSender = h4.every(2000, []()
					  {
						  publishDevice("heap", _HAL_freeHeap());
						  publishDevice("uptime",h4p.gvGetstring(upTimeTag()));
						  publishDevice("maxbloc",_HAL_maxHeapBlock());
					  });
	
	bigSender = h4.every(3000,[]{
		Serial.printf("SENDING BIG\n");
		h4mqtt.publish("big", &big[0], BIG_SIZE, 1);
	});
}
void onMQTTDisconnect() {
	Serial.printf("onMQTTDisconnect()\n");
	h4.cancel(mqttSender);
	h4.cancel(bigSender);
}
#endif
void onViewersConnect() {
	Serial.printf("onViewersConnect\n");
	h4wifi.uiAddGlobal("heap");
	h4wifi.uiAddGlobal("pool");
}
void onViewersDisconnect() {
	Serial.printf("onViewersDisconnect\n");
}

#if USE_BLESERVER
void onBLESrvConnect() {
	Serial.printf("BLE Server -> Client Connected\n");
	bleConnected = true;
}
void onBLESrvDisconnect() {
	Serial.printf("BLE Server -> Client Disconnected\n");
	bleConnected = false;
}
#endif

void h4pGlobalEventHandler(const std::string& svc,H4PE_TYPE t,const std::string& msg)
{
	switch (t)
	{
		H4P_DEFAULT_SYSTEM_HANDLER;
#if USE_BLESERVER
	case H4PE_BLESINIT:
		h4ble.elemAddBoolean("mybool");
		h4.every(1000, []{
			static bool val = false;
			val = !val;
			if (bleConnected) {
				h4ble.elemSetValue("mybool", val);
			}
		});
		break;
#endif
	case H4PE_SERVICE:
		H4P_SERVICE_ADAPTER(WiFi);
#if USE_MQTT
		H4P_SERVICE_ADAPTER(MQTT);
#endif
#if USE_BLESERVER
		H4P_SERVICE_ADAPTER(BLESrv);
#endif
		break;
	case H4PE_VIEWERS:
		H4P_SERVICE_ADAPTER(Viewers);
		break;
	default:
		break;
	}
}
#if USE_BLECLIENT
namespace H4BLEClient {
bool bleClientConnected = false;
BLERemoteCharacteristic* cmdCharacteristic = nullptr;
BLERemoteCharacteristic* replyCharacteristic = nullptr;
H4_TIMER requestor;
void onNotify(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify) {
	Serial.printf("onNotify(%s, %s, is=%d)\n", pBLERemoteCharacteristic->getUUID().toString().c_str(), std::string(reinterpret_cast<char*>(pData), length).c_str(), isNotify);
}
void onConnect() {
	Serial.printf("H4BLEClient::onConnect()\n");
	bleClientConnected = true;
	H4BLEClient::cmdCharacteristic = h4bleclient.getRemoteCharacteristic(BLEUUID("9652c3ca-1231-4607-9d40-6afd67609443"), BLEUUID("3c1eb836-4223-4f3e-9c9d-10c5dae1d9b1"));
	H4BLEClient::replyCharacteristic = h4bleclient.getRemoteCharacteristic(BLEUUID("9652c3ca-1231-4607-9d40-6afd67609443"), BLEUUID("5f1c2e8d-f531-488e-8198-0132ec230a6f"));
	Serial.printf("cmdChar %p {%s} replyChar %p {%s}\n", 
								H4BLEClient::cmdCharacteristic, 
								H4BLEClient::cmdCharacteristic ? H4BLEClient::cmdCharacteristic->getUUID().toString().c_str() : "", 
								H4BLEClient::replyCharacteristic,
								H4BLEClient::replyCharacteristic ? H4BLEClient::replyCharacteristic->getUUID().toString().c_str() : ""
								);

	requestor = h4.every(5000, []{
		Serial.printf("Commanding/Requesting the H4 Server...\n");
		if(cmdCharacteristic->canWrite()){
			Serial.printf("Writing to command characteristic\n");
			cmdCharacteristic->writeValue("h4/toggle");
			cmdCharacteristic->writeValue("h4/dump/glob");
			cmdCharacteristic->writeValue("help");
			// h4.queueFunction([]{
			// 	Serial.printf("Reading reply..\n");
			// 	if (bleClientConnected){
			// 		auto s = replyCharacteristic->readValue();
			// 		Serial.printf("Reply: %s\n", s.c_str());
			// 	}
			// });
		} else {
			Serial.printf("Can not write! %d\n", cmdCharacteristic->canWrite());
		}
	});
	Serial.printf("requestor %p\n", requestor);
}
void onDisconnect() {
	Serial.printf("H4BLEClient::onDisconnect()\n");
	bleClientConnected = false;

	h4.cancel(requestor);
	requestor = nullptr;
}
}
#endif
void h4setup()
{
#ifdef MBEDTLS_DEBUG_C
	mbedtls_debug_set_threshold(1);
#endif

#if USE_BLECLIENT
	h4bleclient.add({BLEUUID("9652c3ca-1231-4607-9d40-6afd67609443"), true},	  // H4_SERVICE_UUID 	, mandatory=true
					 {
						 {BLEUUID("3c1eb836-4223-4f3e-9c9d-10c5dae1d9b1"), true}, // CMD_CHAR_UUID 		, mandatory=true
						 {BLEUUID("5f1c2e8d-f531-488e-8198-0132ec230a6f"), true}, // REPLY_CHAR_UUID 	, mandatory=true
						 {BLEUUID("d684fb38-8fdc-484f-a3a5-15233de0dd9d"), true}, // ELEMENTS_CHAR_UUID , mandatory=true
						 {BLEUUID("53922702-8a3a-41c2-9e5e-d8c90609855e"), true}, // H4UIDATA_CHAR_UUID , mandatory=true
					 },
					 H4BLEClient::onNotify);
	h4bleclient.setCallbacks(H4BLEClient::onConnect, H4BLEClient::onDisconnect);
	h4.queueFunction([]{h4bleclient.start();});
	
	Serial.printf("Invoking cmd h4/dump/glob\n");
	auto res= h4p.invokeCmd("h4/dump/glob");
	Serial.printf("result=%d", res);
#endif

#if USE_MQTT
	h4p[brokerTag()]=MQTT_SERVER;
	for (int i=0;i<BIG_SIZE;i++) {
		big[i]=i;
	}
#endif

#if H4P_SECURE
#if USE_HTTPREQ && SECURE_HTTPREQ
	auto testRootCA = reinterpret_cast<const uint8_t*>(const_cast<char*>(test_root_ca.c_str()));
	h4ah.secureTLS(testRootCA, test_root_ca.length() + 1);
	Serial.printf("HTTP CERT Validation: %s\n", H4AsyncClient::isCertValid(testRootCA, test_root_ca.length() + 1) ? "SUCCEEDED" : "FAILED");
#endif // SECURE_HTTPREQ

#if USE_MQTT && SECURE_MQTT
	auto mqCert = reinterpret_cast<const uint8_t*>(const_cast<char*>(MQTT_CERT.c_str()));
	Serial.printf("MQTT CERT Validation: %s\n", H4AsyncClient::isCertValid(mqCert,MQTT_CERT.length()+1) ? "SUCCEEDED" : "FAILED");
	h4mqtt.secureTLS(mqCert, MQTT_CERT.length()+1);
#endif // USE_MQTT

#if SECURE_WEBSERVER
	Serial.printf("WEBSERVER CERT Validation: %s\n", H4AsyncClient::isCertValid((const uint8_t*)WEBSERVER_CERT.c_str(), WEBSERVER_CERT.length() + 1) ? "SUCCEEDED" : "FAILED");
	Serial.printf("WEBSERVER KEY Validation: %s\n", H4AsyncClient::isPrivKeyValid((const uint8_t*)WEBSERVER_PRIV_KEY.c_str(), WEBSERVER_PRIV_KEY.length() + 1) ? "SUCCEEDED" : "FAILED");
	h4wifi.hookWebserver([](){
		h4wifi.secureTLS((const uint8_t*)WEBSERVER_PRIV_KEY.c_str(), WEBSERVER_PRIV_KEY.length() + 1, 
							NULL, 0,
						(const uint8_t*)WEBSERVER_CERT.c_str(), WEBSERVER_CERT.length() + 1);
		h4wifi.useSecurePort();
	});
#endif // SECURE_WEBSERVER

	h4wifi.authenticate("admin","admin");

#endif // H4P_SECURE

#if USE_MQTT
	h4.every(300, []()
			 {
#if defined(ARDUINO_ARCH_ESP32)
				Serial.printf("H=%u M=%u m=%u S=%u\n", _HAL_freeHeap(MALLOC_CAP_INTERNAL), _HAL_maxHeapBlock(MALLOC_CAP_INTERNAL), _HAL_minHeapBlock(MALLOC_CAP_INTERNAL), uxTaskGetStackHighWaterMark(NULL));
#else
				Serial.printf("H=%u M=%u m=%u\n", _HAL_freeHeap(), _HAL_maxHeapBlock(), _HAL_minHeapBlock());
#endif
				h4p["heap"] = _HAL_freeHeap();
				h4p["pool"] = mbx::pool.size();
				});
#endif
}


void publishDevice(const std::string &topic, const std::string &payload)
{
	Serial.printf("Publishing %s to %s\n", CSTR(payload), CSTR(topic));
#if USE_MQTT
	h4mqtt.publishDevice(topic, payload, 1);
#endif
}

void publishDevice(const std::string &topic, long long payload)
{
	publishDevice(topic, stringFromInt(payload, "%lu"));
}

#if USE_HTTPREQ
void HTTPClient() {
#if SECURE_HTTPREQ
	h4ah.GET("https://www.howsmyssl.com/a/check", [](ARMA_HTTP_REPLY reply){
#else
	h4ah.GET("http://jsonplaceholder.typicode.com/todos/1", [](ARMA_HTTP_REPLY reply){
#endif
		auto rCode = reply.httpResponseCode;
		auto response = reply.asJsonstring();
		auto headers = reply.responseHeaders;
		Serial.printf("code %d response %s\n", rCode, response.c_str());

		for (auto &h:headers) {
			Serial.printf("%s : %s\n", h.first.c_str(), h.second.c_str());
		}
		headers.clear();
		publishDevice("response", response);
	});
}
#endif

