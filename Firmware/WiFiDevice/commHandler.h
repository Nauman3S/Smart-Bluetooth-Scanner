#define DataSerial Serial2


// scanner sc;
String data = "";
void setupCommHandler()
{
    DataSerial.begin(115200); //AT commands baud rate
}

void loopCommHandler()
{

    if (DataSerial.available())
    {
        data = DataSerial.readString();
        data = ss.getMacAddress() + String(",") + data;
        // Serial.println("----");
        // Serial.println(data);
        // Serial.println("----");
        // String a=ss.StringSeparator(data,'\0',0);
        mqttPublish("BLEScanner/device/data", data);
        Serial.println(data);
        // mqttPublish("BLEScanner/device/data", ss.getMacAddress());
        // sc.addAddress(data);
        // sc.printAddress();
        // Serial.println(data);
    }
}