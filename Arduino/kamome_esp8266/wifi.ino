


void doWifi() {
  if (wifiUse == 1) {
    //もし何らかの事態でWifiが接続されていないときは、Wifi再接続する
    if (WiFi.status() == WL_NO_SSID_AVAIL ||
        WiFi.status() == WL_CONNECTION_LOST ||
        WiFi.status() == WL_DISCONNECTED) {

      Udp.stop();
      wifiStart();
    }
    bundleReceive();
  }

}

//------------------------------------------------//
//Wifiスタート処理

void wifiStart() {
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //OTA
  WiFi.mode(WIFI_STA);

  WiFi.config(myIP, myGateWay, mySubnet);
  WiFi.begin(ssid, pass);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //  Serial.println("");
  //  Serial.println("WiFi connected");

  //  printWifiStatus();

  Udp.begin(receivePort);

  wifiUse = 1;
}

//Wifiの状況をシリアルモニタで表示する（USBシリアルをつないだときのデバッグ用）
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}



//------------------------------------------------//
//OSC受信は今回は使わない予定ですが、書いておきます
//OSC受信の処理
void bundleReceive() {
  OSCMessage msgIN;
  int size;
  if ((size = Udp.parsePacket()) > 0) {
    while (size--)
      msgIN.fill(Udp.read());
    if (!msgIN.hasError()) {
      msgIN.route("/value", handleMessage);
    }
  }
}

//OSC受信したメッセージから、0番目のデータを整数で取り出す
void handleMessage(OSCMessage & msg, int addrOffset ) {

  minamoMode = msg.getFloat(3);
  fade_d = msg.getFloat(4);
  prescale_osc = 0;

  for (int i = 0; i < maxBuf; i++) {
    next_r_osc[i] = msg.getFloat(0);
    if (next_r_osc[i] > maxBright)next_r_osc[i] = maxBright;
    next_g_osc[i] = msg.getFloat(1);
    if (next_g_osc[i] > maxBright)next_g_osc[i] = maxBright;
    next_b_osc[i] = msg.getFloat(2);
    if (next_b_osc[i] > maxBright)next_b_osc[i] = maxBright;
  }


}

