/**********************
| INITIALIZING              |
**********************/
    int sensor1 = A0;
    int sensor2 = A1;
    int sensor3 = A2;
    char dataCharArray[12];

/**********************
| SCREEN              |
**********************/
    #include <TFT.h>  // Arduino LCD library
    #include <SPI.h>
    #define cs   10
    #define dc   9
    #define rst  8
    TFT TFTscreen = TFT(cs, dc, rst);


/**********************
| QR Code             |
**********************/
    #include "qrcode.h"
    QRCode qrcode;



void setup() {
    Serial.begin(115200);
//    powerTimer = 10;


/**********************
| SCREEN              |
**********************/
    TFTscreen.begin();
    // Rotate the screen
    TFTscreen.setRotation(2);
    
    // initialize sensors as INPUT
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(sensor3, INPUT);

}

void loop() {

    // clear the screen with a white background
    TFTscreen.background(255,255,255);
    TFTscreen.setTextSize(2);
    TFTscreen.stroke(0,0,0);
    TFTscreen.fill(0,0,0);

    // reading data from sensors
    int data1=analogRead(sensor1);
    Serial.print("Sensor1 reading= ");
    Serial.println(data1);
    delay(100);
    
    int data2=analogRead(sensor2);
    Serial.print("Sensor2 reading= ");
    Serial.println(data2);
    delay(100);
    
    int data3=analogRead(sensor3);
    Serial.print("Sensor3 reading= ");
    Serial.println(data3);
    delay(100);

    // combine all the data
    String data = String (data1)+' '+String (data2)+' '+String (data3);
    data.toCharArray(dataCharArray,12);
    
    
    // Overwriting the data on screen but dont touch the QR code
    // Remove previous value
    TFTscreen.stroke(255,255,255);
    TFTscreen.text(dataCharArray,0,0);
    
    // Set new value
    TFTscreen.stroke(0,0,0);
    TFTscreen.text(dataCharArray,0,0);

    
/**********************
| QR Code             |
**********************/
    uint8_t qrcodeData[qrcode_getBufferSize(3)];
    qrcode_initText(&qrcode, qrcodeData, 3, 0, dataCharArray); // your text in last parameter, e.g. "Hello World"
    for (uint8_t y = 0; y < qrcode.size; y++) {
      // Each horizontal module
      for (uint8_t x = 0; x < qrcode.size; x++) {
        if(qrcode_getModule(&qrcode, x, y)) {
          TFTscreen.rect(5+(x*4), 40+(y*4), 4, 4);
        }
      }
    }
    
    delay (10000);
}
