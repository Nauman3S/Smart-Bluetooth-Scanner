

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <string>

int scanTime = 1; //In seconds
BLEScan *pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        char data[512];
        char address[18];
        strcpy(address, advertisedDevice.getAddress().toString().c_str());
        if (advertisedDevice.haveName())
        {
            sprintf(data, "%s,%s,%d;", advertisedDevice.getName().c_str(), address, advertisedDevice.getRSSI());
        }
        else
        {
            sprintf(data, "Unknown,%s,%d;", address, advertisedDevice.getRSSI());
        }
        Serial.println(data);
        Serial2.println(data);
    }
};

void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200);
    Serial.println("Scanning...");

    BLEDevice::init("myBLEScan");
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99); // less or equal setInterval value
}

void loop()
{
    // put your main code here, to run repeatedly:
    BLEDevice::init("myBLEScan");
    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
    Serial.print("Devices found: ");
    Serial.println(foundDevices.getCount());
    Serial.println("Scan done!");
    // sc.printAddress();
    pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
    BLEDevice::deinit(false);
    // sc.printAddress();
    // delay(1000);
}
