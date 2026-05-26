#include <WiFi.h>
#include <Preferences.h>
#include <WebServer.h>

// ================= LED =================
#define LED_BUILTIN_PIN 2

// ================= ACCESS POINT =================
const char* AP_NAME = "ESP32-SETUP";
const char* AP_PASS = "12345678";

// ================= WEB SERVER =================
WebServer server(80);

// ================= STORAGE =================
Preferences prefs;

// ================= WIFI DATA =================
String savedSSID = "";
String savedPASS = "";

// =====================================================
// ==================== LED CONTROL ====================
// =====================================================

void ledON() {
  digitalWrite(LED_BUILTIN_PIN, HIGH);
}

void ledOFF() {
  digitalWrite(LED_BUILTIN_PIN, LOW);
}

// =====================================================
// ==================== LOAD WIFI ======================
// =====================================================

void loadWiFi() {

  prefs.begin("wifi", true);

  savedSSID = prefs.getString("ssid", "");
  savedPASS = prefs.getString("pass", "");

  prefs.end();
}

// =====================================================
// ==================== SAVE WIFI ======================
// =====================================================

void saveWiFi(String ssid, String pass) {

  prefs.begin("wifi", false);

  prefs.putString("ssid", ssid);
  prefs.putString("pass", pass);

  prefs.end();
}

// =====================================================
// ==================== WEB PAGE =======================
// =====================================================

String webPage() {

  String page = "";

  page += "<!DOCTYPE html>";
  page += "<html>";
  page += "<head>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<title>ESP32 WiFi Setup</title>";
  page += "</head>";

  page += "<body style='font-family:Arial;text-align:center;margin-top:50px;'>";

  page += "<h2>ESP32 WiFi Setup</h2>";

  page += "<form action='/save'>";

  page += "SSID:<br><br>";
  page += "<input name='ssid'><br><br>";

  page += "Password:<br><br>";
  page += "<input name='pass' type='password'><br><br>";

  page += "<input type='submit' value='Connect'>";

  page += "</form>";
  page += "</body>";
  page += "</html>";

  return page;
}

// =====================================================
// ==================== HOTSPOT MODE ===================
// =====================================================

void startHotspotMode() {

  Serial.println("HOTSPOT MODE");

  WiFi.mode(WIFI_AP);

  WiFi.softAP(AP_NAME, AP_PASS);

  IPAddress IP = WiFi.softAPIP();

  Serial.print("AP IP: ");
  Serial.println(IP);

  server.on("/", []() {

    server.send(200, "text/html", webPage());
  });

  server.on("/save", []() {

    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    Serial.println("WiFi Saved");

    saveWiFi(ssid, pass);

    server.send(200, "text/html",
                "<h2>WiFi Saved</h2><p>ESP32 Connecting...</p>");

    delay(2000);

    ESP.restart();
  });

  server.begin();

  // LED berkedip cepat
  while (true) {

    server.handleClient();

    ledON();
    delay(100);

    ledOFF();
    delay(100);
  }
}

// =====================================================
// ==================== CONNECT WIFI ===================
// =====================================================

bool connectWiFi() {

  if (savedSSID == "") {

    Serial.println("No Saved WiFi");

    return false;
  }

  Serial.print("Connecting to: ");
  Serial.println(savedSSID);

  WiFi.mode(WIFI_STA);

  WiFi.begin(savedSSID.c_str(), savedPASS.c_str());

  unsigned long startAttempt = millis();

  // coba konek selama 20 detik
  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttempt < 20000) {

    // LED kedip 1 detik
    ledON();
    delay(500);

    ledOFF();
    delay(500);

    Serial.print(".");
  }

  // berhasil connect
  if (WiFi.status() == WL_CONNECTED) {

    Serial.println();
    Serial.println("WiFi Connected");

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    ledON();

    return true;
  }

  // gagal connect
  Serial.println();
  Serial.println("WiFi Failed");

  return false;
}

// =====================================================
// ======================= SETUP =======================
// =====================================================

void setup() {

  Serial.begin(115200);

  pinMode(LED_BUILTIN_PIN, OUTPUT);

  ledOFF();

  loadWiFi();

  bool connected = connectWiFi();

  if (!connected) {

    startHotspotMode();
  }
}

// =====================================================
// ======================== LOOP =======================
// =====================================================

void loop() {
    // ko
}