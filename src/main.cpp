#include <Arduino.h>
#include <H4Plugins.h>
H4_USE_PLUGINS(115200, H4_Q_CAPACITY, false) // Serial baud rate, Q size, SerialCmd autostop
//
const char *WIFI_SSID = "XXXXXXXX";
const char *WIFI_PASS = "XXXXXXXX";
const char *MQTT_SERVER = "http://192.168.1.34:1883";
//

// const char* pload0="multi-line payload hex dumper which should split over several lines, with some left over";
// const char* pload1="PAYLOAD QOS1";
// const char* pload2="Save the Pangolin!";


// #define BIG_SIZE 5000
// #define MED_SIZE 500

// char big[BIG_SIZE];
// char med[MED_SIZE];

H4P_PinMachine h4gm;
H4P_WiFi h4wifi(WIFI_SSID, WIFI_PASS, "uiinputs");
H4P_AsyncMQTT h4mqtt(MQTT_SERVER);
H4P_Heartbeat h4hb;
H4P_UPNPServer h4upnp("UI Input Tester");

void publishDevice(const std::string &topic, const std::string &payload)
{
	Serial.printf("Publishing %s to %s\n", CSTR(payload), CSTR(topic));
	h4mqtt.publishDevice(topic, payload, 1);
}
void publishDevice(const std::string &topic, long long payload)
{
	publishDevice(topic, stringFromInt(payload, "%lu"));
}
H4_TIMER sender;
H4_TIMER reporter;

void onWiFiConnect(){
	Serial.printf("Connected, IP: %s\n",WiFi.localIP().toString().c_str());
}
void onWiFiDisconnect(){
	Serial.printf("WiFi Disconnected\n");
}
void onMQTTConnect(){

	sender = 	h4.every(200, []()
			 {
    // publishDevice("heap",_HAL_freeHeap());
		// publishDevice("uptime",h4p.gvGetInt(upTimeTag()));
		// publishDevice("hello",std::string("Hello from ") + h4p.gvGetstring(deviceTag()));
		// publishDevice("millis",millis()); 
		Serial.printf("Heap: %u\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
		// auto bigtName = std::string("h4/") + (h4p[deviceTag()] + "/big");
		// auto medtName = std::string("h4/") + (h4p[deviceTag()] + "/med");

		// auto p0Topic = std::string("h4/") + (h4p[deviceTag()] + "/0");
		// auto p1Topic = std::string("h4/") + (h4p[deviceTag()] + "/1");
		// auto p2Topic = std::string("h4/") + (h4p[deviceTag()] + "/2");

		// h4mqtt.publish(p0Topic.c_str(), pload0, strlen(pload0), 0);
		// h4mqtt.publish(p1Topic.c_str(), pload1, strlen(pload1), 1);
		// h4mqtt.publish(p2Topic.c_str(), pload2, strlen(pload2), 2);

		// h4mqtt.publish(medtName.c_str(),med, MED_SIZE, 1, false); 
		});

	// reporter = h4.every(5000, []()
	// 		 { publishDevice("heap", heap_caps_get_free_size(MALLOC_CAP_DEFAULT)); });

}
void onMQTTDisconnect(){
	h4.cancel(sender);
	h4.cancel(reporter);
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
	default:
		break;
	}

}
void h4setup()
{
	// for(auto i=0;i<BIG_SIZE;i++) big[i]=i;
	// for(auto i=0;i<MED_SIZE;i++) med[i]=i;

}
