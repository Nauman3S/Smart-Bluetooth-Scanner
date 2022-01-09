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
        name.trim();
        name = ss.StringSeparator(name, ':', 1);
        name.trim();

        String address = ss.StringSeparator(payload, ',', 1);
        address.trim();
        // address=ss.StringSeparator(address, ':', 1);
        address.replace("Address: ", "");
        // address.trim();

        String data = ss.StringSeparator(payload, ',', 2);
        data.trim();
        data = ss.StringSeparator(data, ':', 1);
        data.trim();

        String rssi = ss.StringSeparator(payload, ',', 3);
        rssi.trim();
        rssi = ss.StringSeparator(rssi, ':', 1);
        rssi.trim();
        rssi.replace("\nName:", "");
        rssi.replace("Name:", "");
        rssi.replace("\nName", "");
        rssi.replace("Name", "");

        // Serial.println(name);
        // Serial.println(address);
        // Serial.println(data);
        // Serial.println(rssi);

        // Serial.println(counter);
        // Serial.println("******************");

        if (counter == 48)
        {
            counter = 0;
        }
        if (counter == 0)
        {
            addresses[counter] = address;
            if (name == String(" ") || name == String(""))
            {
                name = String("Unknown");
            }
            else
            {
                names[counter] = name;
            }
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
                    if (name == String(" ") || name == String(""))
                    {
                        name = String("Unknown");
                    }
                    else
                    {
                        names[counter] = name;
                    }
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
            Serial.print("addresse: ");
            Serial.println(addresses[i]);
            Serial.print("rssi: ");
            Serial.println(rssis[i]);
            Serial.println("********");
        }
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
        sc.addAddress(data);
        sc.printAddress();
    }
}