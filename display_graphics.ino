//This program is a demo of how to display picture and 
//how to use rotate function to display string.

//pin usage as follow:
//            CS  DC/RS  RESET  SDI/MOSI  SCK  SDO/MISO  LED    VCC     GND    
//ESP32-S3:   10    2      15      11      12      13     21     5V     GND          

/***********************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "ST77922.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "XRC168";
const char* password = "12345678";

#define CENTER 240


TFT_eSPI tft = TFT_eSPI();
TFT_eSprite my_lcd = TFT_eSprite(&tft);
ST77922 mylcd = ST77922(); 

//define some colour values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//clear screen
void fill_screen_test()
{
  my_lcd.fillSprite(WHITE);
  mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t *)my_lcd.getPointer()); 
  delay(500);  
  my_lcd.fillSprite(RED);
  mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t *)my_lcd.getPointer());
  delay(500); 
  my_lcd.fillSprite(GREEN);
  mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t *)my_lcd.getPointer());
  delay(500);
  my_lcd.fillSprite(BLUE);
  mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t *)my_lcd.getPointer());
  delay(500); 
  my_lcd.fillSprite(BLACK);
  mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t *)my_lcd.getPointer());
  delay(500); 
}

//display some strings
void text_test()
{
  my_lcd.fillSprite(BLACK); 
  my_lcd.setTextColor(WHITE);
  my_lcd.drawString("Hello World!", 2,2,1);
  
  my_lcd.setTextColor(YELLOW);
  my_lcd.drawFloat(1234.56, 3, 2, 10,2);

  my_lcd.setTextColor(RED);
  my_lcd.drawNumber(0xDEADBEF, 0, 24,4);

  my_lcd.setTextColor(BLUE);
  my_lcd.drawString("apmp", 2,46,6);
  my_lcd.setTextColor(GREEN);
  my_lcd.drawString("I implore thee,", 2,96,2);

  my_lcd.drawString("my foonting turlingdromes.", 2, 112,1);
  my_lcd.drawString("And hooptiously drangle me", 2, 120,1);
  my_lcd.drawString("with crinkly bindlewurdles,", 2, 128,1);
  my_lcd.drawString("Or I will rend thee", 2, 136,1);
  my_lcd.drawString("in the gobberwarts", 2, 144,1);
  my_lcd.drawString("with my blurglecruncheon,", 2, 152,1);
  my_lcd.drawString("see if I don't!", 2, 160,1);
  mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t *)my_lcd.getPointer());
}

void drawBackground()
{
    my_lcd.fillSprite(BLACK);

    // 時間區
    my_lcd.drawRect(0, 0, 480, 40, WHITE);

    // 中間分隔線
    my_lcd.drawLine(240, 40, 240, 320, WHITE);

    // 左邊區域
    my_lcd.setTextColor(CYAN);
    my_lcd.drawString("Tuen Ma Line", 30, 50, 4);

    my_lcd.setTextColor(WHITE);
    my_lcd.drawString("Yuen Long", 40, 100, 4);
    my_lcd.drawString("To Tuen Mun", 20, 140, 4);

    my_lcd.drawString("Next Train", 20, 190, 2);
    my_lcd.drawString("Following", 20, 250, 2);

    // 右邊區域
    my_lcd.setTextColor(YELLOW);
    my_lcd.drawString("Light Rail 610", 260, 50, 4);

    my_lcd.setTextColor(WHITE);
    my_lcd.drawString("Siu Hong", 290, 100, 4);
    my_lcd.drawString("Tai Hing N.", 270, 140, 4);

    my_lcd.drawString("Next Tram", 270, 190, 2);
    my_lcd.drawString("Following", 270, 250, 2);
}

void showMTR_CN(
    String west1,
    String west2,
    String lrt1,
    String lrt2,
    String nowTime
)
{
    // 西鐵加 m
if(west1 != "--")
west1 += "m";

if(west2 != "--")
west2 += "m";
    drawBackground();

    // 時間
    my_lcd.setTextColor(YELLOW);
    my_lcd.drawString(nowTime, 20, 10, 4);

    // 屯馬線 ETA
    my_lcd.setTextColor(GREEN);

    my_lcd.drawString(
        west1,
        100,
        190,
        6
    );

    my_lcd.drawString(
        west2,
        100,
        250,
        6
    );

    // 輕鐵 ETA
    my_lcd.drawString(
        lrt1,
        340,
        190,
        6
    );

    my_lcd.drawString(
        lrt2,
        340,
        250,
        6
    );

    mylcd.Fill_Colors(
        0,
        0,
        mylcd.Get_Width(),
        mylcd.Get_Height(),
        (uint16_t*)my_lcd.getPointer()
    );
}

//draw some oblique lines
void lines_test(void)
{
    int i=0;
    my_lcd.fillSprite(BLACK); 
    for(i = 0; i< my_lcd.width();i+=5)
    {
       my_lcd.drawLine(0, 0, i, my_lcd.height()-1,GREEN);
     }
     for(i = my_lcd.height()-1; i>= 0;i-=5)
     {
       my_lcd.drawLine(0, 0, my_lcd.width()-1, i,GREEN);
     }
     mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());

     my_lcd.fillSprite(BLACK); 
    for(i = my_lcd.width() -1; i>=0;i-=5)
    {
      my_lcd.drawLine(my_lcd.width()-1, 0, i, my_lcd.height()-1,RED);
     }
    for(i = my_lcd.height()-1; i>=0;i-=5)
    {
      my_lcd.drawLine(my_lcd.width()-1, 0, 0, i,RED);
     }
     mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t*)my_lcd.getPointer());

     my_lcd.fillSprite(BLACK); 
     for(i = 0; i < my_lcd.width();i+=5)
    {
      my_lcd.drawLine(0, my_lcd.height()-1, i, 0,GREEN);
     }
     for(i = 0; i < my_lcd.height();i+=5)
    {
      my_lcd.drawLine(0, my_lcd.height()-1, my_lcd.width()-1, i,GREEN);
     }
mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t*)my_lcd.getPointer());

      my_lcd.fillSprite(BLACK); 
     for(i = my_lcd.width()-1; i >=0;i-=5)
    {
      my_lcd.drawLine(my_lcd.width()-1, my_lcd.height()-1, i, 0,YELLOW);
     }
     for(i = 0; i<my_lcd.height();i+=5)
    {
      my_lcd.drawLine(my_lcd.width()-1, my_lcd.height()-1, 0, i,YELLOW);
      
     }
     mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t*)my_lcd.getPointer());
}

//draw some vertical lines and horizontal lines
void h_l_lines_test(void)
{
    int i=0;
    my_lcd.fillSprite(BLACK);
    for(i =0;i<my_lcd.height();i+=5)
    {
      my_lcd.drawFastHLine(0,i,my_lcd.width(),GREEN);
      delay(1);
    }
    mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t*)my_lcd.getPointer());
     for(i =0;i<my_lcd.width();i+=5)
    {
      my_lcd.drawFastVLine(i,0,my_lcd.height(),BLUE);
      delay(1);
    }
    mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(), (uint16_t*)my_lcd.getPointer());
}

//draw some rectangles
void rectangle_test(void)
{
  int i = 0;
   my_lcd.fillSprite(BLACK);
   for(i = 0;i<my_lcd.width()/2;i+=4)
   {
      my_lcd.drawRect(i,(my_lcd.height()-my_lcd.width())/2+i,my_lcd.width()-2*i,my_lcd.width()-2*i,GREEN); 
      delay(1);
   }
    mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
}

//draw some filled rectangles
void fill_rectangle_test(void)
{
  int i = 0;
   my_lcd.fillSprite(BLACK);
   my_lcd.fillRect(0,(my_lcd.height()-my_lcd.width())/2,my_lcd.width(),my_lcd.width(),YELLOW);
   for(i = 0;i<my_lcd.width()/2;i+=4)
   {
      my_lcd.drawRect(i,(my_lcd.height()-my_lcd.width())/2+i,my_lcd.width()-2*i,my_lcd.width()-2*i,MAGENTA);
      delay(1);
   }
   mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
   for(i = 0;i<my_lcd.width()/2;i+=4)
   {
      my_lcd.fillRect(i,(my_lcd.height()-my_lcd.width())/2+i,my_lcd.width()-2*i,my_lcd.width()-2*i,random(0xFFFF));  
      delay(1);
   }
   mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
}

//draw some filled circles
void fill_circles_test(void)
{
  int r=10,i=0,j=0;
  my_lcd.fillSprite(BLACK);
  for(i=r;i<my_lcd.width();i+=2*r)
  {
    for(j=r;j<my_lcd.height();j+=2*r)
    {
      my_lcd.fillCircle(i, j, r,MAGENTA);
    }
    mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
  }
}

//draw some circles
void circles_test(void)
{
  int r=10,i=0,j=0;
  for(i=0;i<my_lcd.width()+r;i+=2*r)
  {
    for(j=0;j<my_lcd.height()+r;j+=2*r)
    {
      my_lcd.drawCircle(i, j, r,GREEN);
      
    }
    mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
  }  
}

//draw some triangles
void triangles_test(void)
{
   int i = 0;
   my_lcd.fillSprite(BLACK);
   for(i=0;i<my_lcd.width()/2;i+=5)
   {
      my_lcd.drawTriangle(my_lcd.width()/2-1,my_lcd.height()/2-1-i,
                    my_lcd.width()/2-1-i,my_lcd.height()/2-1+i,
                    my_lcd.width()/2-1+i,my_lcd.height()/2-1+i,my_lcd.color565(0, i+64, i+64));  
                       
   }
   mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
}

//draw some filled triangles
void fill_triangles_test(void)
{
   int i = 0;
   my_lcd.fillSprite(BLACK);
    for(i=my_lcd.width()/2-1;i>0;i-=5)
   {
      my_lcd.fillTriangle(my_lcd.width()/2-1,my_lcd.height()/2-1-i,
                    my_lcd.width()/2-1-i,my_lcd.height()/2-1+i,
                    my_lcd.width()/2-1+i,my_lcd.height()/2-1+i,my_lcd.color565(0, i+64, i+64));                   
      my_lcd.fillTriangle(my_lcd.width()/2-1,my_lcd.height()/2-1-i,
                    my_lcd.width()/2-1-i,my_lcd.height()/2-1+i,
                    my_lcd.width()/2-1+i,my_lcd.height()/2-1+i,my_lcd.color565(i, 0, i));  
                       
   }
   mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
}

//draw some round rectangles
void round_rectangle(void)
{
   int i = 0;
   my_lcd.fillSprite(BLACK);
     for(i = 0;i<my_lcd.width()/2;i+=4)
   {
      my_lcd.fillRoundRect(i,(my_lcd.height()-my_lcd.width())/2+i,my_lcd.width()-2*i,my_lcd.width()-2*i,8,my_lcd.color565(255-i,0,160-i));
      delay(1);
   } 
   mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
}

//draw some filled round rectangles
void fill_round_rectangle(void)
{
   int i = 0;
   my_lcd.fillSprite(BLACK);
   for(i = 0;i<my_lcd.width()/2;i+=4)
   {
      my_lcd.fillRoundRect(i,(my_lcd.height()-my_lcd.width())/2+i,my_lcd.width()-2*i,my_lcd.width()-2*i,8,my_lcd.color565(255-i,160-i,0));
        delay(1);
   }
    mylcd.Fill_Colors(0, 0, mylcd.Get_Width(), mylcd.Get_Height(),(uint16_t*)my_lcd.getPointer());
}

void setup()
{
    Serial.begin(115200);

    mylcd.Init();
    mylcd.Set_Rotation(0);

    my_lcd.createSprite(
        mylcd.Get_Width(),
        mylcd.Get_Height()
    );

    my_lcd.setSwapBytes(1);

    Serial.println("Connecting WiFi...");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi Connected");
    Serial.println(WiFi.localIP());

    // HTTPS Test
    WiFiClientSecure client;
    client.setInsecure();

    if(client.connect("rt.data.gov.hk", 443))
    {
        Serial.println("HTTPS OK");
    }
    else
    {
        Serial.println("HTTPS FAIL");
    }
}
void loop()
{
    String eta1 = "--";
    String eta2 = "--";

    String lrtEta1 = "--";
    String lrtEta2 = "--";

    String nowTime = "--:--:--";

    WiFiClientSecure client;
    client.setInsecure();


    /*****************************************
     * 屯馬線
     * 元朗站 -> 屯門
     *****************************************/
    HTTPClient http;

    http.begin(
        client,
        "https://rt.data.gov.hk/v1/transport/mtr/getSchedule.php?line=TML&sta=YUL"
    );

    int httpCode = http.GET();

    if (httpCode == 200)
    {
        String payload = http.getString();

        Serial.println("======== TUEN MA LINE ========");

        // 取得系統時間
        int posTime =
            payload.indexOf("\"curr_time\":\"");

        if (posTime >= 0)
        {
            posTime += 13;

            int endTime =
                payload.indexOf("\"", posTime);

            if (endTime > posTime)
            {
                String fullTime =
                    payload.substring(posTime, endTime);

                if (fullTime.length() >= 19)
                {
                    nowTime =
                        fullTime.substring(11, 19);
                }
            }
        }

        // 找第一班往屯門列車
        int posDest1 =
            payload.indexOf("\"dest\":\"TUM\"");

        if (posDest1 >= 0)
        {
            int posEta1 =
                payload.indexOf(
                    "\"ttnt\":\"",
                    posDest1
                );

            if (posEta1 >= 0)
            {
                posEta1 += 8;

                int endEta1 =
                    payload.indexOf(
                        "\"",
                        posEta1
                    );

                if (endEta1 > posEta1)
                {
                    eta1 =
                        payload.substring(
                            posEta1,
                            endEta1
                        );
                }
            }

            // 從第一班目的地之後，找第二班往屯門列車
            int posDest2 =
                payload.indexOf(
                    "\"dest\":\"TUM\"",
                    posDest1 + 1
                );

            if (posDest2 >= 0)
            {
                int posEta2 =
                    payload.indexOf(
                        "\"ttnt\":\"",
                        posDest2
                    );

                if (posEta2 >= 0)
                {
                    posEta2 += 8;

                    int endEta2 =
                        payload.indexOf(
                            "\"",
                            posEta2
                        );

                    if (endEta2 > posEta2)
                    {
                        eta2 =
                            payload.substring(
                                posEta2,
                                endEta2
                            );
                    }
                }
            }
        }
        else
        {
            Serial.println(
                "No Tuen Ma Line train to TUM found"
            );
        }
    }
    else
    {
        Serial.print("TML HTTP error: ");
        Serial.println(httpCode);
    }

    http.end();


    /*****************************************
     * 輕鐵 610
     * 大興北 station_id = 212
     * 往屯門碼頭
     *****************************************/
    HTTPClient http2;

    http2.begin(
        client,
        "https://rt.data.gov.hk/v1/transport/mtr/lrt/getSchedule?station_id=212"
    );

    int httpCode2 = http2.GET();

    if (httpCode2 == 200)
    {
        String payload2 = http2.getString();

        Serial.println("======== LIGHT RAIL ========");

        int searchPos = 0;
        int found610 = 0;

        while (found610 < 2)
        {
            // 找下一個 route_no
            int routePos =
                payload2.indexOf(
                    "\"route_no\"",
                    searchPos
                );

            if (routePos < 0)
            {
                break;
            }

            // 找該班車 JSON object 的開始及結束
            int objectStart =
                payload2.lastIndexOf(
                    "{",
                    routePos
                );

            int objectEnd =
                payload2.indexOf(
                    "}",
                    routePos
                );

            if (objectStart < 0 || objectEnd < 0)
            {
                break;
            }

            String routeObject =
                payload2.substring(
                    objectStart,
                    objectEnd + 1
                );

            /*
             * 同時支援：
             * "route_no":"610"
             * "route_no": "610"
             */
            bool isRoute610 =
                routeObject.indexOf(
                    "\"route_no\":\"610\""
                ) >= 0
                ||
                routeObject.indexOf(
                    "\"route_no\": \"610\""
                ) >= 0;

            /*
             * 只選往屯門碼頭方向。
             * 同時支援有空格及沒有空格的 JSON。
             */
            bool isTuenMunFerryPier =
                routeObject.indexOf(
                    "\"dest_en\":\"Tuen Mun Ferry Pier\""
                ) >= 0
                ||
                routeObject.indexOf(
                    "\"dest_en\": \"Tuen Mun Ferry Pier\""
                ) >= 0;

            if (isRoute610 && isTuenMunFerryPier)
            {
                int timeKey =
                    routeObject.indexOf(
                        "\"time_en\""
                    );

                if (timeKey >= 0)
                {
                    int colonPos =
                        routeObject.indexOf(
                            ":",
                            timeKey
                        );

                    int firstQuote =
                        routeObject.indexOf(
                            "\"",
                            colonPos + 1
                        );

                    int secondQuote =
                        routeObject.indexOf(
                            "\"",
                            firstQuote + 1
                        );

                    if (
                        colonPos >= 0 &&
                        firstQuote >= 0 &&
                        secondQuote > firstQuote
                    )
                    {
                        String eta =
                            routeObject.substring(
                                firstQuote + 1,
                                secondQuote
                            );

                        if (found610 == 0)
                        {
                            lrtEta1 = eta;
                        }
                        else if (found610 == 1)
                        {
                            lrtEta2 = eta;
                        }

                        found610++;
                    }
                }
            }

            searchPos = objectEnd + 1;
        }

        if (found610 == 0)
        {
            Serial.println(
                "No Route 610 to Tuen Mun Ferry Pier found"
            );

            lrtEta1 = "--";
            lrtEta2 = "--";
        }
    }
    else
    {
        Serial.print("LRT HTTP error: ");
        Serial.println(httpCode2);
    }

    http2.end();


    /*****************************************
     * Serial Monitor 輸出
     *****************************************/
    Serial.println();
    Serial.println("=== TUEN MA LINE ===");

    Serial.print("Train 1: ");
    Serial.println(eta1);

    Serial.print("Train 2: ");
    Serial.println(eta2);

    Serial.println("=== LIGHT RAIL 610 ===");

    Serial.print("Train 1: ");
    Serial.println(lrtEta1);

    Serial.print("Train 2: ");
    Serial.println(lrtEta2);

    Serial.print("Time: ");
    Serial.println(nowTime);

    Serial.println("===========================");
    Serial.println();


    /*****************************************
     * 更新 LCD
     *****************************************/
    showMTR_CN(
        eta1,
        eta2,
        lrtEta1,
        lrtEta2,
        nowTime
    );
Serial.println("LOOP END");
    delay(30000);
}
