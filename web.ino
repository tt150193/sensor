#include "Arduino.h"
//The setup function is called once at startup of the sketch
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "ArduinoJson.h"
#include "source_sensor/DHT.h"
#include "mqtt/PubSubClient.h"
#include "EEPROM.h"
#define EEPROM_SIZE 200
#define ADD_SERVER  10
#define ADD_PORT	60
#define ADD_MODE	70
#define ADD_SSID	80
#define ADD_PASS	110
#define ADD_NAME	140
void writeString(char add, String data) {
	Serial.println(data);
	int _size = data.length();
	int i;
	for (i = 0; i < _size; i++) {
		EEPROM.write(add + i, data[i]);
	}
	EEPROM.write(add + _size, '\0'); //Add termination null character for String Data
	EEPROM.commit();
}

String read_String(char add) {
	char data[100]; //Max 100 Bytes
	int len = 0;
	unsigned char k;
	k = EEPROM.read(add);
	while (k != '\0' && len < 500)   //Read until null character
	{
		k = EEPROM.read(add + len);
		data[len] = k;
		len++;
	}
	data[len] = '\0';
	return String(data);
}
String index_html =  "<html>"
		"	<head>"
		"        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
		"        <style>"
		"            body {"
		"                font-family: Arial, \"Helvetica Neue\", Helvetica, sans-serif;"
		"            }"
		"            a:hover {"
		"                  padding: 2px;"
		"                  color:#fff!important;background-color:#2196F3!important;"
		"            }"
		"            th, td {"
		"  border: 1px solid gray;"
		"  padding: 15px;"
		"  text-align: left;"
		"}   "
		"tr:nth-child(even) {background-color: #f2f2f2;}"
		"input, select {"
		"    padding: 10px;"
		"}"
		"        </style>"
		"		<script>"
		"            var x;"
		"            var config = {};"
		"            function getdata(str, cb) {"
		"                var xhttp = new XMLHttpRequest();"
		"                xhttp.onreadystatechange = function() {"
		"                    if (this.readyState == 4 && this.status == 200) {"
		"                        if (cb) {"
		"                            cb(this.responseText);"
		"                        }"
		"                    }"
		"                };"
		"                xhttp.open(\"GET\", str, true);"
		"                xhttp.send();"
		"            }"
		"            function getSensor() {"
		"                getdata(\"/data\", (data) => {"
		"                    var d = {};"
		"                    try {"
		"                        d = JSON.parse(data);"
		"                    } catch (e) {"
		"                        d = data;"
		"                    }"
		"                    document.getElementById(\"humi\").innerHTML = d.humidity;"
		"                    document.getElementById(\"temp\").innerHTML = d.temperature;"
		"                });"
		"            }"
		"            var e;"
		"            var cn = 10;"
		"            function scanWifi() {"
		"                e = setInterval(()=>{"
		"                    var st = document.getElementById(\"statusScan\");"
		"                    st.innerHTML = \"Waiting \" + (cn--).toString() + \" seconds\";"
		"                }, 1000);"
		"                getdata('/scan', function(data) {"
		"                    clearInterval(e);"
		"                    cn = 10;"
		"                    document.getElementById(\"statusScan\").innerHTML = \"\";"
		"                    x = document.getElementById(\"black\");"
		"                    var ab = \"\";"
		"                    try {"
		"                        ab = JSON.parse(data);"
		"                    } catch (e) {"
		"                        ab = {};"
		"                    }"
		"                    console.log(ab);"
		"                    for (c = 0; c < ab.data.length; c++) {"
		"                        var option = document.createElement(\"option\");"
		"                        option.text = ab.data[c];"
		"                        x.add(option);"
		"                    }"
		"                });"
		"            }"
		"            function setWifi() {"
		"                var x = document.getElementById(\"black\");"
		"                var ssid = x.options[x.selectedIndex].value;"
		"                var pass = document.getElementById(\"passWifi\").value;"
		"                getdata(\"/setwifi?ssid=\" + ssid + \"&pass=\" + pass, function(data) {"
		"                    console.log(data);"
		"                });"
		"            }"
		"            function display(d) {"
		"                var a = [];"
		"                a[0] = document.getElementById(\"sensor\");"
		"                a[1] = document.getElementById(\"mqtt\");"
		"                a[2] = document.getElementById(\"wifi\");"
		"                for (i = 0; i < 3; i++) {"
		"                    if (i == d - 1) {"
		"                        a[i].style.display = \"block\";"
		"                    } else {"
		"                        a[i].style.display = \"none\";"
		"                    }"
		"                }"
		"            }"
		"            var auto;"
		"            document.addEventListener('DOMContentLoaded', (event) => {"
		"                display(1);"
		"                var checkbox = document.querySelector(\"input[name=checkbox]\");"
		"                checkbox.addEventListener('change', function() {"
		"                    if (this.checked) {"
		"                        auto = setInterval(getSensor, 2000);"
		"                    } else {"
		"                        clearInterval(auto);"
		"                    }"
		"                });"
		"                getConfigure();"
		"            });"
		"            function getConfigure() {"
		"                getdata(\"/config\", (d) => {"
		"                    var ab = \"\";"
		"                    try {"
		"                        ab = JSON.parse(d);"
		"                    } catch (e) {"
		"                        ab = {};"
		"                    }"
		"                    console.log(ab);"
		"                    document.getElementById(\"server_mqtt\").value = ab.server;"
		"                    document.getElementById(\"port_mqtt\").value = ab.port;"
		"                    document.getElementById(\"name_mqtt\").value = ab.name;"
		"                });"
		"            }"
		"            function setMqtt() {"
		"                var se = document.getElementById(\"server_mqtt\").value;"
		"                var po = document.getElementById(\"port_mqtt\").value;"
		"                var na = document.getElementById(\"name_mqtt\").value;"
		"                getdata(\"/set?server=\" + se + \"&port=\" + po + \"&name=\" + na);"
		"            }"
		"		</script>"
		"	</head>"
		"	<body>"
		"        <div id=\"control\">"
		"            <a onclick=\"display(1)\">SENSOR</a> | "
		"            <a onclick=\"display(2);\">MQTT-CONFIG</a> |"
		"            <a onclick=\"display(3);\">WIFI-CONFIG</a>       "
		"        </div>"
		"        <div id=\"sensor\" style=\"display: none\">"
		"            <h1>SENSOR</h1>"
		"            <p style=\"text-align: right; font-size: 18px\"><input type=\"checkbox\" name=\"checkbox\" id=\"auto\">Auto</p>"
		"            "
		"            <div>"
		"                    <table>"
		"                            <tr>"
		"                                <td><label>TEMPERATURE: </label></td>"
		"                                <td><span id=\"temp\" style=\"font-size: 36px;\"></span></td>"
		"                            </tr>"
		"                            <tr>"
		"                                <td><label>HUMIDITY: </label></td>"
		"                                <td><span id=\"humi\" style=\"font-size: 36px;\"></span></td>"
		"                            </tr>            "
		"                    </table>                "
		"            </div>"
		"        </div>"
		"        <div id=\"mqtt\" style=\"display: none\">"
		"                <h1>SET MQTT</h1>"
		"                <div>"
		"                        <table>"
		"                                <tr>"
		"                                    <td><label>SERVER: </label></td>"
		"                                    <td>"
		"                                        <input id=\"server_mqtt\">"
		"                                    </td>"
		"                                </tr>"
		"                                <tr>"
		"                                    <td><label>PORT: </label></td>"
		"                                    <td><input id=\"port_mqtt\"></td>"
		"                                </tr>  "
		"                                <tr>"
		"                                        <td><label>NAME: </label></td>"
		"                                        <td><input id=\"name_mqtt\"></td>"
		"                                    </tr>            "
		"                            </table>"
		"                        <button style=\"padding: 5px; margin: 5px\" onclick=\"setMqtt()\">SET</button>        "
		"                </div>"
		"            </div>"
		"        <div id=\"wifi\" style=\"display: none\">"
		"            <h1>Setup WIFI</h1>"
		"            <div>"
		"                <table>"
		"                    <tr>"
		"                        <td><label>WIFI: </label></td>"
		"                        <td>"
		"                            <select id=\"black\" placeholder=\"Wifi\" style=\"width: 100%\">"
		"                                "
		"                            </select>"
		"                        </td>"
		"                    </tr>"
		"                    <tr>"
		"                        <td><label>PASS: </label></td>"
		"                        <td><input placeholder=\"Password\" style=\"width: 100%\" id=\"passWifi\"></td>"
		"                    </tr>"
		"                </table>"
		"            </div> <br>"
		"            <p id=\"statusScan\"></p>"
		"            <button onclick=\"scanWifi()\" style=\"padding: 5px; margin: 5px\">SCAN WIFI</button>"
		"            <button onclick=\"setWifi()\" style=\"padding: 5px; margin: 5px\">APPLY</button>  "
		"        </div>"
		"        <footer style=\"position:fixed;width:100%;z-index:1;bottom:0; display: none\"><h5 style=\"text-align: center\">CRETA SOLUTIONs<br>659 Lac Long Quan, P.10, Q. Tan Binh</h5></footer>"
		"	</body>"
		"</html>";

String ssid = "thanh lam";
String password = "thanhlam";
const char* host_name = "xtek";
String mqttServer = "iot.eclipse.org";
String mqttName = "ESP8266";
int mqttPort = 1883;
const char* mqttUser = "yourMQTTuser";
const char* mqttPassword = "yourMQTTpassword";

WiFiClient espClient;
PubSubClient client(espClient);

WebServer server(80);
StaticJsonDocument<200> doc;
StaticJsonDocument<100> dataSensor;
String scanWifi;
const int led = 13;
#define LED_STATE 2
#define LED_WIFI 14
int state = 0;
int freqLed = 500;
int counterLed = 0;
#define ERROR_WIFI 500
#define ERROR_SENSOR 100
#define NORMAL 2000
int counterMachine = 0;
int freqApp = 2000;
#define BUTTON 13
String modeEsp = "";
enum {
	STATE_IDLE, STATE_RUNNING_APP, STATE_ERROR_SENSOR, STATE_ERROR_WIFI

};

//Define DHT
float h;
float t;
float f;

#define DHTPIN 5     // what digital pin we're connected to
#define DELAY_PUSH 3000
int countButtonPush = 0;
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char) payload[i]);
	}
	Serial.println();
}

void handleRoot() {
	doc.clear();
	int n = WiFi.scanNetworks();
	JsonArray data = doc.createNestedArray("data");
	for (int i = 0; i < n; i++) {
		data.add(WiFi.SSID(i));
		delay(10);
	}
	serializeJson(doc, scanWifi);
	digitalWrite(led, 1);
	server.send(200, "text/plain", scanWifi);
	digitalWrite(led, 0);
	scanWifi = "";
}

void responseData() {
	doc.clear();
	doc["temperature"] = String(t);
	doc["humidity"] = String(h);
	serializeJson(doc, scanWifi);
	server.send(200, "text/lain", scanWifi);
	scanWifi = "";
}

void setupConfigure() {
	String message = "";
	writeString(ADD_SERVER, server.arg("server"));
	writeString(ADD_PORT, server.arg("port"));
	writeString(ADD_NAME, server.arg("name"));
//	writeString(ADD_SERVER, server.arg(""));
	for (int i = 0; i < server.args(); i++) {
		message += server.argName(i) + ": " + server.arg(i);
		message += "\n";
//		if(server.argName(i).equals("server")){
//			writeString(ADD_SERVER, server.arg());
//		}
	}
//	Serial.println(message);
	doc.clear();
	doc["state"] = "success";
	serializeJson(doc, scanWifi);
	server.send(200, "text/plain", scanWifi);
	scanWifi = "";
	ESP.restart();
}

void setupWifi() {
	String message = "";
	writeString(ADD_SSID, server.arg("ssid"));
	writeString(ADD_PASS, server.arg("pass"));
	//	writeString(ADD_SERVER, server.arg(""));
	for (int i = 0; i < server.args(); i++) {
		message += server.argName(i) + ": " + server.arg(i);
		message += "\n";
		//		if(server.argName(i).equals("server")){
		//			writeString(ADD_SERVER, server.arg());
		//		}
	}
	Serial.println(message);
	doc.clear();
	doc["state"] = "success";
	serializeJson(doc, scanWifi);
	server.send(200, "text/plain", scanWifi);
	scanWifi = "";
	writeString(ADD_MODE, "AP-WIFI");
	ESP.restart();
}
void handleNotFound() {
	digitalWrite(led, 1);
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
	digitalWrite(led, 0);
}

void initGPIO() {
	int k = 10;
	pinMode(LED_STATE, OUTPUT);
	pinMode(LED_WIFI, OUTPUT);
	pinMode(BUTTON, INPUT_PULLUP);

	digitalWrite(LED_STATE, HIGH);
	digitalWrite(LED_WIFI, LOW);
//	delay(10000);
	for(k = 0; k < 10; k++){
		digitalWrite(LED_WIFI, !digitalRead(LED_WIFI));
		digitalWrite(LED_STATE, !digitalRead(LED_STATE));
		delay(250);
	}
	digitalWrite(LED_STATE, HIGH);
	digitalWrite(LED_WIFI, LOW);
}

void readParam() {
	mqttServer = read_String(ADD_SERVER);
	mqttPort = (read_String(ADD_PORT)).toInt();
	modeEsp = read_String(ADD_MODE);
	ssid = read_String(ADD_SSID);
	password = read_String(ADD_PASS);
	mqttName = read_String(ADD_NAME);
	Serial.print("SERVER: ");
	Serial.println(mqttServer);
	Serial.print("PORT: ");
	Serial.println(mqttPort);
	Serial.print("MODE: ");
	Serial.println(modeEsp);
	Serial.print("SSID: ");
	Serial.println(ssid);
	Serial.print("PASS: ");
	Serial.println(password);
	Serial.print("NAME: ");
	Serial.println(mqttName);
}

void getConfigure(){
	doc.clear();
	doc["ssid"] = ssid;
	doc["server"] = mqttServer;
	doc["port"] = String(mqttPort);
	doc["name"] = mqttName;
	serializeJson(doc, scanWifi);
	server.send(200, "text/lain", scanWifi);
	scanWifi = "";
}

void getDataSensor(){
	doc.clear();
	doc["temperature"] = String(t);
	doc["humidity"] = String(h);
	serializeJson(doc, scanWifi);
	doc.clear();
	doc["identifier"] = "SENSOR-123";
	doc["actionId"] = "";
	doc["status"] = "SUCCESS";
	doc["data"] = scanWifi;
	scanWifi = "";
	serializeJson(doc, scanWifi);
	server.send(200, "text/lain", scanWifi);
	scanWifi = "";
}

void setup(void) {
	state = STATE_IDLE;
	freqLed = NORMAL;
	Serial.begin(115200);
	initGPIO();
	while (!Serial) {

	}
	Serial.println("Console success");
	if (!EEPROM.begin(EEPROM_SIZE)) {
		Serial.println("failed to initialise EEPROM");
		delay(1000000);
	}
	readParam();
	if (modeEsp.equals("AP-MODE")) {
		WiFi.softAP("ESP-SENSOR", "12345678");
		IPAddress IP = WiFi.softAPIP();
		Serial.print("AP IP address: ");
		Serial.println(IP);
		digitalWrite(LED_WIFI, HIGH);
	} else {
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid.c_str(), password.c_str());
		// Wait for connection
		while (WiFi.status() != WL_CONNECTED) {
			delay(200);
			Serial.print(".");
			digitalWrite(LED_WIFI, !digitalRead(LED_WIFI));
			if (digitalRead(BUTTON) == 0) {
				countButtonPush = millis();
				while (digitalRead(BUTTON) == 0) {
					if(millis() - countButtonPush > DELAY_PUSH){
						digitalWrite(LED_WIFI, HIGH);
					}
				}
				if (millis() - countButtonPush > DELAY_PUSH) {
					digitalWrite(LED_WIFI, LOW);
					delay(2000);
					Serial.println("System restart to now :)");
					writeString(ADD_MODE, "AP-MODE");
					ESP.restart();
				}
			}
		}
		Serial.println("");
		Serial.print("Connected to ");
		Serial.println(ssid);
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());
		digitalWrite(LED_WIFI, LOW);
	}

	if (MDNS.begin("esp32")) {
		Serial.println("MDNS responder started");
	}

	server.on("/", []() {
		server.send(200, "text/html", index_html);
	});
	server.on("/scan", handleRoot);
	server.on("/data", responseData);
	server.on("/set", setupConfigure);
	server.on("/setwifi", setupWifi);
	server.on("/config", getConfigure);
	server.on("/sensor", getDataSensor);
	server.onNotFound(handleNotFound);
	server.begin();
	Serial.println("HTTP server started");
	//DHT begin
	dht.begin();

	//MQTT Begin
	client.setServer(mqttServer.c_str(), mqttPort);

//	while (!client.connected()) {
//		Serial.println("Connecting to MQTT...");
//
//		if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
//			client.subscribe("blackcu");
//			Serial.println("connected");
//
//		} else {
//
//			Serial.print("failed with state ");
//			Serial.print(client.state());
//			delay(2000);
//
//		}
//	}
	client.setCallback(callback);
	client.publish("esp/test", "Hello from ESP32");
}

void runLed() {
	if (millis() - counterLed > freqLed) {
		counterLed = millis();
		digitalWrite(LED_STATE, !digitalRead(LED_STATE));
	} else {

	}
}

int checkSensor() {

	return 0;
}
int checkWifi() {

	return 0;
}

void runStateMachine() {
	if ((millis() - counterMachine > freqApp) && (state == STATE_IDLE)) {
		counterMachine = millis();
		state = STATE_RUNNING_APP;
	}
	if (digitalRead(BUTTON) == 0) {
		countButtonPush = millis();
		while (digitalRead(BUTTON) == 0) {
			if(millis() - countButtonPush > DELAY_PUSH){
				digitalWrite(LED_WIFI, HIGH);
			}
		}
		if (millis() - countButtonPush > DELAY_PUSH) {
			digitalWrite(LED_WIFI, LOW);
			delay(2000);
			Serial.println("System restart to now :)");
			writeString(ADD_MODE, "AP-MODE");
			ESP.restart();
		}
	}
}

int autoSendMqtt = 1;
void runApp() {
	h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	t = dht.readTemperature();
	// Read temperature as Fahrenheit (isFahrenheit = true)
	f = dht.readTemperature(true);
	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
		state = STATE_ERROR_SENSOR;
	} else {
		freqLed = NORMAL;
		state = STATE_IDLE;
		if (autoSendMqtt) {
			doc.clear();
			doc["temperature"] = String(t);
			doc["humidity"] = String(h);
			serializeJson(doc, scanWifi);
			client.publish(("esp/sensor/"+mqttName).c_str(), scanWifi.c_str());
			scanWifi = "";
		}
	}
}

long lastReconnectAttempt = 0;
boolean reconnect() {
	if (client.connect("arduinoClient")) {
		client.subscribe("esp/config");
	}
	return client.connected();
}

void loop(void) {
	runStateMachine();
	switch (state) {
	case STATE_IDLE: {
		runLed();
	}
		break;
	case STATE_RUNNING_APP: {
		runApp();
	}
		break;
	case STATE_ERROR_SENSOR: {
		freqLed = ERROR_SENSOR;
		state = STATE_IDLE;
	}
		break;
	case STATE_ERROR_WIFI: {
		freqLed = ERROR_WIFI;
		state = STATE_IDLE;
	}
		break;
	default: {
//			Serial.println("Not found state_machine");
	}
	}
	if (!client.connected()) {
		reconnect();
	} else {
		client.loop();
	}

	server.handleClient();
}
