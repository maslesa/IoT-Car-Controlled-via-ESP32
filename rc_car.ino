#include <WiFi.h>
#include <WebServer.h>

#define WIFI_LED 23

// Motors
#define IN1 18
#define IN2 19
#define IN3 21
#define IN4 22

WebServer server(80);
const char* ssid = ""; // enter your ssid of network
const char* password = ""; // enter your password

void controlMotors(const String& action) {
  if (action == "forward") {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (action == "backward") {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else if (action == "left") {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (action == "right") {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Car Control</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
    h1 { margin-bottom: 20px; }
    #instructions { font-size: 20px; margin-top: 30px; }
  </style>
</head>
<body>
  <h1>ESP32 Car Control</h1>
  <p id="instructions">Use W, A, S, D keys to control the car</p>
  <script>
    let activeKey = null;

    document.addEventListener('keydown', (event) => {
      if (event.key !== activeKey) {
        activeKey = event.key;
        sendCommand(event.key);
      }
    });

    document.addEventListener('keyup', (event) => {
      if (event.key === activeKey) {
        activeKey = null;
        sendCommand('stop');
      }
    });

    function sendCommand(key) {
      let action;
      switch (key.toLowerCase()) {
        case 'w': action = 'forward'; break;
        case 's': action = 'backward'; break;
        case 'a': action = 'left'; break;
        case 'd': action = 'right'; break;
        default: action = 'stop'; break;
      }
      console.log(action);
      fetch(`/control?action=${action}`).catch(console.error);
    }
  </script>
</body>
</html>
)rawliteral");
}

void handleControl() {
  if (server.hasArg("action")) {
    String action = server.arg("action");
    controlMotors(action);
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(WIFI_LED, OUTPUT);
  digitalWrite(WIFI_LED, LOW);

  // Motor pins setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  digitalWrite(WIFI_LED, HIGH);
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up server routes
  server.on("/", handleRoot);
  server.on("/control", handleControl);

  server.begin();
}

void loop() {
  server.handleClient();
}
