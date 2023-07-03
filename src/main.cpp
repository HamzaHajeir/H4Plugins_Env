#include <Arduino.h>
#include "config.h"
#include <H4Plugins.h>
H4_USE_PLUGINS(PROJ_BAUD_RATE, H4_Q_CAPACITY, false) // Serial baud rate, Q size, SerialCmd autostop
//


H4P_SerialLogger h4sl;
H4P_PinMachine h4gm;

#ifdef ARDUINO_ARCH_ESP8266
std::string name = "ESP8266";
#else
std::string name = "ESP32";
#endif

H4P_WiFi h4wifi(WIFI_SSID, WIFI_PASS, name);
#if USE_MQTT
H4P_AsyncMQTT h4mqtt(MQTT_SERVER);
#endif
H4P_Heartbeat h4hb;
H4P_BinarySwitch h4onoff(4, ACTIVE_LOW, H4P_UILED_ORANGE, OFF, 10000);
H4P_UPNPServer h4upnp("UI Input Tester");

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
H4_TIMER sender;

void onWiFiConnect() {
	Serial.printf("Connected, IP: %s\n",WiFi.localIP().toString().c_str());
}
void onWiFiDisconnect() {
	Serial.printf("WiFi Disconnected\n");
#if USE_MQTT
	h4mqtt.informNetworkState(H4AMC_NETWORK_DISCONNECTED); // [ ] Move to H4Plugins.
#endif
}
void onMQTTConnect() {
	sender = h4.every(2000, []()
					  {
						  publishDevice("heap", _HAL_freeHeap());
						  publishDevice("uptime",h4p.gvGetInt(upTimeTag()));
					  });

}
void onMQTTDisconnect() {
	h4.cancel(sender);
}
void onViewersConnect() {
	h4wifi.uiAddGlobal("heap");
	// h4wifi.uiAddGlobal("pool");
}
void onViewersDisconnect() {
}

void h4pGlobalEventHandler(const std::string& svc,H4PE_TYPE t,const std::string& msg)
{
	switch (t)
	{
		H4P_DEFAULT_SYSTEM_HANDLER;
	case H4PE_SERVICE:
		H4P_SERVICE_ADAPTER(MQTT);
		H4P_SERVICE_ADAPTER(WiFi);
		break;
	case H4PE_VIEWERS:
		H4P_SERVICE_ADAPTER(Viewers);
		break;
	default:
		break;
	}

}
void h4setup()
{
#ifdef MBEDTLS_DEBUG_C
	mbedtls_debug_set_threshold(1);
#endif

#if H4P_SECURE
	auto mqCert = reinterpret_cast<const uint8_t*>(const_cast<char*>(MQTT_CERT.c_str()));
	Serial.printf("MQTT CERT Validation: %s\n", H4AsyncClient::isCertValid(mqCert,MQTT_CERT.length()+1) ? "SUCCEEDED" : "FAILED");
	Serial.printf("WEBSERVER CERT Validation: %s\n", H4AsyncClient::isCertValid((const uint8_t*)WEBSERVER_CERT.c_str(), WEBSERVER_CERT.length() + 1) ? "SUCCEEDED" : "FAILED");
	Serial.printf("WEBSERVER KEY Validation: %s\n", H4AsyncClient::isPrivKeyValid((const uint8_t*)WEBSERVER_PRIV_KEY.c_str(), WEBSERVER_PRIV_KEY.length() + 1) ? "SUCCEEDED" : "FAILED");

#if USE_MQTT
	h4mqtt.secureTLS(mqCert, MQTT_CERT.length()+1);
#endif
#if SECURE_WEBSERVER
	h4wifi.hookWebserver([](){
		h4wifi.secureTLS((const uint8_t*)WEBSERVER_PRIV_KEY.c_str(), WEBSERVER_PRIV_KEY.length() + 1, 
							NULL, 0,
						(const uint8_t*)WEBSERVER_CERT.c_str(), WEBSERVER_CERT.length() + 1);
		h4wifi.useSecurePort();
	});
#endif // SECURE_WEBSERVER
#endif // H4P_SECURE

	h4.every(300, []()
			 {
				Serial.printf("H=%u M=%u m=%u S=%u\n", _HAL_freeHeap(MALLOC_CAP_INTERNAL), _HAL_maxHeapBlock(MALLOC_CAP_INTERNAL), _HAL_minHeapBlock(MALLOC_CAP_INTERNAL), uxTaskGetStackHighWaterMark(NULL));
				h4p["heap"] = _HAL_freeHeap();
				// h4p["pool"] = mbx::pool.size();
				});
}
