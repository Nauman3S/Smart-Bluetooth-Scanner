#define DataSerial Serial2
class scanner
{

private:
    String addresses[50];
    String names[50];
    String rssis[50];
    int counter = 0;

public:
    void addAddress(String payload)
    {
        // Serial.println("******************");
        String name = ss.StringSeparator(payload, ',', 0);
        String address = ss.StringSeparator(payload, ',', 1);
        String rssi = ss.StringSeparator(payload, ',', 2);

        if (counter == 48)
        {
            counter = 0;
        }
        if (counter == 0)
        {
            addresses[counter] = address;
            names[counter] = name;
            rssis[counter] = rssi;
            counter++;
        }
        else
        {
            for (int i = 0; i < counter; i++)
            {
                if (addresses[i].indexOf(address) >= 0)
                {
                    addresses[i] = address;
                    names[i] = name;
                    rssis[i] = rssi;
                    break;
                }
                else
                {
                    addresses[counter] = address;
                    names[counter] = name;
                    rssis[counter] = rssi;
                    counter++;
                    break;
                }
            }
        }
    }

    void printAddress()
    {
        for (int i = 0; i < counter; i++)
        {
            Serial.println("********");
            Serial.print("Name: ");
            Serial.println(names[i]);
            Serial.print("address: ");
            Serial.println(addresses[i]);
            Serial.print("rssi: ");
            Serial.println(rssis[i]);
            Serial.print("counter: ");
            Serial.println(counter);
            Serial.println("********");
        }
        Serial.println("--END SCAN--");
    }
};

scanner sc;
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
        // mqttPublish("BLEScanner/device/data", ss.getMacAddress());
        // sc.addAddress(data);
        // sc.printAddress();
        // Serial.println(data);
    }
}