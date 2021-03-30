#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif
#include <RadioHead.h>
 
RH_ASK driver;
// RH_ASK driver(2000, 4, 5, 0); // ESP8266 or ESP32: do not use pin 11 or 2
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85),
// RH_ASK driver(2000, PD14, PD13, 0); STM32F4 Discovery: see tx and rx on Orange and Red LEDS
 
void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);   // Debugging only
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
        ;
#endif
  Serial.println("init success");
}

uint8_t setupTime = 0;
 
void loop()
{
//    const char *msg = "os3: hello world!";


    // create buffer and convert from uint to string
    char buf[8];
    itoa(setupTime, buf, 10);

    // send data
    driver.send((uint8_t *)buf, strlen(buf));
    driver.waitPacketSent();

    // increment counter
    setupTime += 1;
    Serial.println(buf);
    delay(1000);
}
