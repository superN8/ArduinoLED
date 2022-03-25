//==Version A==
//-Reduced setup
//-Redeclares values redundantly on every iteration of main loop

#include <Adafruit_NeoPixel.h>
#define PIN 2

const int stripLength = 10;
int ledStripA[stripLength][3] = {},
    rainCycle = 0,
    rainState,
	stepSize=17;
	
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
		
		if(rainState <= 255) //r -> y
		{
			ledStripA[i][0]=255;
			ledStripA[i][1]=rainState;
			ledStripA[i][2]=0;
		}
		else if(rainState <= 510) //y -> g
		{
			ledStripA[i][0]=510-rainState;
			ledStripA[i][1]=255;
			ledStripA[i][2]=0;
		}
		else if(rainState <= 765) //g -> c
		{
			ledStripA[i][0]=0;
			ledStripA[i][1]=255;
			ledStripA[i][2]=rainState-510;
		}
		else if(rainState <= 1020) //c -> b
		{
			ledStripA[i][0]=0;
			ledStripA[i][1]=1020-rainState;
			ledStripA[i][2]=255;
		}
		else if(rainState <= 1275) //b -> m
		{
			ledStripA[i][0]=rainState-1020;
			ledStripA[i][1]=0;
			ledStripA[i][2]=255;
		}
		else //m -> r
		{
			ledStripA[i][0]=255;
			ledStripA[i][1]=0;
			ledStripA[i][2]=1530-rainState;
		}
		
        ledStrip.setPixelColor(i, ledStrip.Color(ledStripA[i][0], ledStripA[i][1], ledStripA[i][2]));
		//delay(1);
    }
	
    ledStrip.show();
    rainCycle+=stepSize;
	
    if(rainCycle >= 1530)
    {
        rainCycle=0;
    }
	
    //Serial.println(ledToString(ledStripA[0]));
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