//==Version D==
//-Obnoxious declarations to reduce lines
//-LED Values determined by Rainbow State
#include <Adafruit_NeoPixel.h>
#define PIN 2

const int stripLength = 20;
int ledStripA[stripLength][3] = {},
    rainCycle = 0,
    rainState,
	stepSize=51;
	
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(stripLength, PIN, NEO_GRB + NEO_KHZ800);


void setup ()
{
    Serial.begin(9600);
    ledStrip.begin();
}
void loop()
{
    for(int i = 0; i < stripLength; i++)
    {
        rainState = rainCycle + (i*stepSize);
        while(rainState > 1530)
        {
            rainState -= 1530;
        }
		
		ledStripA[i][0] = ( ((rainState <= 255)||(rainState > 1275 )) ? 255 : ((rainState <= 510) ? (510-rainState) : ((rainState <= 1020) ? 0 : (rainState-1020))));
		ledStripA[i][1] = ( (rainState <= 255) ? rainState : ((rainState <= 765)? 255 :  ((rainState <= 1020)? (1020-rainState) : 0)));
		ledStripA[i][2] = ( (rainState <= 510) ? 0 : ((rainState <= 765) ? (rainState-510) : ((rainState <= 1275)? 255 : (1530-rainState))));
		
		
        ledStrip.setPixelColor(i, ledStrip.Color(ledStripA[i][0], ledStripA[i][1], ledStripA[i][2]));
		delay(1);
    }
	
    ledStrip.show();
    rainCycle+=stepSize;
	
    if(rainCycle >= 1530)
    {
        rainCycle=0;
    }
     Serial.println(ledToString(ledStripA[0]));
    
}

String ledToString(int ledA[])
{
    String s = "";
    s += ledA[0];
    s += ", ";
    s += ledA[1];
    s += ", ";
    s += ledA[2];
    return s;
}