// YouTube video: https://youtu.be/pbqgrv5YSf0
// Source Files: https://github.com/upiir/arduino_round_lcd_display
//
//-----------------------------------------------------
//
// Links from the video:
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Round IPS Display: https://s.click.aliexpress.com/e/_Dl834Gr
// Round IPS Display documentation: http://www.lcdwiki.com/0.96inch_IPS_ST7789_Module
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_ApbCwx
// Photopea (online graphics editor like Photoshop): https://www.photopea.com/
// Arduino UNO Small: https://s.click.aliexpress.com/e/_DBlBN0F
// Gear Shifter Keychain: https://s.click.aliexpress.com/e/_DdQpYK3
// Shifter Knob: https://s.click.aliexpress.com/e/_DnouRtl
// Pin Male Headers long: https://s.click.aliexpress.com/e/_DD7GCT9
// Color Formats: https://en.wikipedia.org/wiki/List_of_monochrome_and_RGB_color_formats
// RGB565 Color Picker: https://rgbcolorpicker.com/565
// BMW M logo: https://en.m.wikipedia.org/wiki/File:BMW_M_logo.svg
// Arduino Serial documentation: https://www.arduino.cc/reference/en/language/functions/communication/serial/read/
// RealTerm: https://sourceforge.net/projects/realterm/
// IrfanView: https://www.irfanview.com/
// Progmem documentation: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
// BMW font: https://www.dafontfree.co/bmw-font/
//
// Gear Indicator video series:
// Part 1 // getting current gear with hall sensors: https://youtu.be/QixtxaAda18
// Part 2 // exploring the Pimoroni 11x7px display: https://youtu.be/sZZFgSmYJjc
// Part 3 // custom 3D printed shifter knob: https://youtu.be/HcP48uCBzDQ
// Part 4 // Pimoroni 5x5 RGB LED display: https://youtu.be/84bn_OpuyCQ
// Part 5 // SimHub shifter knob: https://youtu.be/JbVqXZngXAY
// Part 6 // NeoPixel hexagonal displays: https://youtu.be/1NI-I1Lpdqo



//This application does not rely on any libraries and it is for ST7799H2

//This program is a demo of clearing screen to display black,white,red,green,blue.

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//             CS  A0/DC  RESET  SDA  SCL  BLK    VCC     GND
//Arduino Uno  A2   A3     A4     11   13  A0   5V/3.3V   GND

//Remember to set the pins to suit your display module!
/********************************************************************************
  @attention

  THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
#include <SPI.h>
#include "images.h"

// ------- UNO
#define LED   A0
#define CS    A2
#define RS    A3
#define RESET A4


void Lcd_Writ_Bus(unsigned char d)
{
  SPI.transfer(d);
}

void Lcd_Write_Com(unsigned char VH)
{
  *(portOutputRegister(digitalPinToPort(RS))) &=  ~digitalPinToBitMask(RS);//LCD_RS=0;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
  *(portOutputRegister(digitalPinToPort(RS))) |=  digitalPinToBitMask(RS); //LCD_RS=1;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com, unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
  Lcd_Write_Com(0x2a);
  Lcd_Write_Data(x1 >> 8);
  Lcd_Write_Data(x1);
  Lcd_Write_Data(x2 >> 8);
  Lcd_Write_Data(x2);
  Lcd_Write_Com(0x2b);
  Lcd_Write_Data(y1 >> 8);
  Lcd_Write_Data(y1);
  Lcd_Write_Data(y2 >> 8);
  Lcd_Write_Data(y2);
  Lcd_Write_Com(0x2c);
}

void SPI_Init(void)
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2); // 4 MHz (half speed)
  //SPI.setClockDivider(SPI_CLOCK_DIV128); // sloooooow
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
}

void Lcd_Init(void)
{
  digitalWrite(RESET, HIGH);
  delay(5);
  digitalWrite(RESET, LOW);
  delay(15);
  digitalWrite(RESET, HIGH);
  delay(15);

  //ST7789H2 Init
  digitalWrite(CS, LOW); //CS
  Lcd_Write_Com(0x36);
  Lcd_Write_Data(0x00);

  Lcd_Write_Com(0x3A);
  Lcd_Write_Data(0x05);

  Lcd_Write_Com(0xB2);
  Lcd_Write_Data(0x0C);
  Lcd_Write_Data(0x0C);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x33);
  Lcd_Write_Data(0x33);

  Lcd_Write_Com(0xB7);
  Lcd_Write_Data(0x35);

  Lcd_Write_Com(0xBB);
  Lcd_Write_Data(0x17);

  Lcd_Write_Com(0xC0);
  Lcd_Write_Data(0x2C);

  Lcd_Write_Com(0xC2);
  Lcd_Write_Data(0x01);

  Lcd_Write_Com(0xC3);
  Lcd_Write_Data(0x12);

  Lcd_Write_Com(0xC4);
  Lcd_Write_Data(0x20);

  Lcd_Write_Com(0xC6);
  Lcd_Write_Data(0x0F);

  Lcd_Write_Com(0xD0);
  Lcd_Write_Data(0xA4);
  Lcd_Write_Data(0xA1);

  Lcd_Write_Com(0xE0);
  Lcd_Write_Data(0xD0);
  Lcd_Write_Data(0x04);
  Lcd_Write_Data(0x0D);
  Lcd_Write_Data(0x11);
  Lcd_Write_Data(0x13);
  Lcd_Write_Data(0x2B);
  Lcd_Write_Data(0x3F);
  Lcd_Write_Data(0x54);
  Lcd_Write_Data(0x4C);
  Lcd_Write_Data(0x18);
  Lcd_Write_Data(0x0D);
  Lcd_Write_Data(0x0B);
  Lcd_Write_Data(0x1F);
  Lcd_Write_Data(0x23);

  Lcd_Write_Com(0xE1);
  Lcd_Write_Data(0xD0);
  Lcd_Write_Data(0x04);
  Lcd_Write_Data(0x0C);
  Lcd_Write_Data(0x11);
  Lcd_Write_Data(0x13);
  Lcd_Write_Data(0x2C);
  Lcd_Write_Data(0x3F);
  Lcd_Write_Data(0x44);
  Lcd_Write_Data(0x51);
  Lcd_Write_Data(0x2F);
  Lcd_Write_Data(0x1F);
  Lcd_Write_Data(0x1F);
  Lcd_Write_Data(0x20);
  Lcd_Write_Data(0x23);

  Lcd_Write_Com(0x21);

  Lcd_Write_Com(0x11);
  //Delay (120);

  Lcd_Write_Com(0x29);
  digitalWrite(CS, HIGH);
}

void Draw_Pixel(unsigned int x, unsigned int y, unsigned int color)
{
  digitalWrite(CS, LOW);
  Address_set(x, y, x, y);
  Lcd_Write_Data(color >> 8);
  Lcd_Write_Data(color);
  digitalWrite(CS, HIGH);
}

void Fill_Rect(unsigned int sx, unsigned int sy, unsigned int w, unsigned int h, unsigned int color)
{
  unsigned int i, m;
  unsigned int ex = w + sx - 1;
  unsigned int ey = h + sy - 1;
  digitalWrite(CS, LOW);
  Address_set(sx, sy, ex, ey);
  for (i = 0; i < w; i++)
    for (m = 0; m < h; m++)
    {
      Lcd_Write_Data(color >> 8);
      Lcd_Write_Data(color);
    }
  digitalWrite(CS, HIGH);
}

//draw a vertical line
void Draw_Fast_VLine(unsigned int x, unsigned int y, unsigned int h, unsigned int color)
{
  Fill_Rect(x, y, 1, h, color);
}

void Draw_Circle(unsigned int x, unsigned int y, unsigned int radius, unsigned int color)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x1 = 0;
  int y1 = radius;

  Draw_Pixel(x, y + radius, color);
  Draw_Pixel(x, y - radius, color);
  Draw_Pixel(x + radius, y, color);
  Draw_Pixel(x - radius, y, color);

  while (x1 < y1)
  {
    if (f >= 0)
    {
      y1--;
      ddF_y += 2;
      f += ddF_y;
    }
    x1++;
    ddF_x += 2;
    f += ddF_x;

    Draw_Pixel(x + x1, y + y1, color);
    Draw_Pixel(x - x1, y + y1, color);
    Draw_Pixel(x + x1, y - y1, color);
    Draw_Pixel(x - x1, y - y1, color);
    Draw_Pixel(x + y1, y + x1, color);
    Draw_Pixel(x - y1, y + x1, color);
    Draw_Pixel(x + y1, y - x1, color);
    Draw_Pixel(x - y1, y - x1, color);
  }
}

//fill a circle
void Fill_Circle(unsigned int x, unsigned int y, unsigned int radius, unsigned int color)
{
  Draw_Fast_VLine(x, y - radius, 2 * radius + 1, color);
  Fill_Circle_Helper(x, y, radius, 3, 0, color);
}

//fill a semi-circle
void Fill_Circle_Helper(unsigned int x0, unsigned int y0, unsigned int r, unsigned int cornername, unsigned int delta, unsigned int color)
{
  int f     = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x     = 0;
  int y     = r;

  while (x < y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if (cornername & 0x1)
    {
      Draw_Fast_VLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
      Draw_Fast_VLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
    }
    if (cornername & 0x2)
    {
      Draw_Fast_VLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
      Draw_Fast_VLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
    }
  }
}

void LCD_Clear(unsigned int j)
{
  unsigned int i, m;
  digitalWrite(CS, LOW);
  Address_set(0, 0, 239, 197);
  for (i = 0; i < 198; i++)
    for (m = 0; m < 240; m++)
    {
      Lcd_Write_Data(j >> 8);
      Lcd_Write_Data(j);
    }
  digitalWrite(CS, HIGH);
}


void LCD_Clear_random(unsigned int j)
{
  unsigned int i, m;
  digitalWrite(CS, LOW);
  Address_set(0, 0, 239, 197);
  for (i = 0; i < 198; i++)
    for (m = 0; m < 240; m++)
    {
      //Lcd_Write_Data(j>>8);
      //Lcd_Write_Data(j);
      Lcd_Write_Data(j);
      Lcd_Write_Data(i);
    }

  /*  for (m = 0; m < 100; m++) {
      for (i = 0; i < 128; i++) {
        Lcd_Write_Data(rainbow_8x8_map[i]);
      }
    }*/

  digitalWrite(CS, HIGH);
}






void draw_image(int x, int y, int width, int height, byte image_array[]) {
  // draw an image
  digitalWrite(CS, LOW);
  Address_set(x, y, x + width - 1, y + height - 1);
  for (int i = 0; i < (width * height * 2); i++) {
    //Lcd_Write_Data(gImage_shifter_digit_R_24x28px[i]);  // not PROGMEM
    Lcd_Write_Data(pgm_read_byte_near(image_array + i)); // PROGMEM

  }
  digitalWrite(CS, HIGH);
  // end draw an image
}


void draw_image_tinted(int x, int y, int width, int height, byte image_array[], unsigned int tint) {
  // draw an image
  digitalWrite(CS, LOW);
  Address_set(x, y, x + width - 1, y + height - 1);
  for (int i = 0; i < (width * height); i++) {
    //Lcd_Write_Data(gImage_shifter_digit_R_24x28px[i]);  // not PROGMEM

    Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2) & highByte(tint)); // PROGMEM
    Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2 + 1) & lowByte(tint)); // PROGMEM

    //Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2) & (B11111000)); // PROGMEM
    //Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2 + 1) & (B00000000)); // PROGMEM

  }
  digitalWrite(CS, HIGH);
  // end draw an image
}

void draw_image_byteshift(int x, int y, int width, int height, byte image_array[], byte shift_low, byte shift_high) {
  // draw an image
  digitalWrite(CS, LOW);
  Address_set(x, y, x + width - 1, y + height - 1);
  for (int i = 0; i < (width * height); i++) {
    //Lcd_Write_Data(gImage_shifter_digit_R_24x28px[i]);  // not PROGMEM
    Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2) >> shift_low); // PROGMEM
    Lcd_Write_Data(pgm_read_byte_near(image_array + i * 2 + 1) >> shift_high); // PROGMEM

  }
  digitalWrite(CS, HIGH);
  // end draw an image
}



int gear_previous = 0;
int gear_current = 1;

unsigned int color_dark_gray = 0x8410; //    Red    ⏐    Green    ⏐   Blue - 1 0 0 0 0 ⏐ 1 0 0 0 0 0 ⏐ 1 0 0 0 0
unsigned int color_light_gray = 0xc618; //    Red    ⏐    Green    ⏐   Blue - 1 1 0 0 0 ⏐ 1 1 0 0 0 0 ⏐ 1 1 0 0 0
unsigned int color_red = 0xf800; // 1 1 1 1 1 ⏐ 0 0 0 0 0 0 ⏐ 0 0 0 0 0
unsigned int color_light_blue = 0x841f; // 1 0 0 0 0 ⏐ 1 0 0 0 0 0 ⏐ 1 1 1 1 1
unsigned int color_blue_gray = 0x8418; //
unsigned int color_dark_blue = 0x01f0; //


// those two colors are used to draw everything
unsigned int color_active;
unsigned int color_inactive;

byte color_theme = 0;


void setup()
{
  SPI_Init();
  pinMode(A0, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A2, OUTPUT);

  digitalWrite(A0, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A2, HIGH);

  Lcd_Init();
  Serial.begin(115200);
  //Serial.begin(230400);
  //Serial.begin(921600);

  LCD_Clear(0x0000); // fill fullscreen with BLACK

  color_active = color_red;
  color_inactive = color_dark_gray;



  // first screen redraw
  // images logo on the back - M symbol
  draw_image( 55,  99, 123, 47, gImage_shifter_logo_M_123x47px);

  // connecting lines + DIGITS

  // R
  Fill_Rect( 40, 85, 4, 37, color_inactive);
  Fill_Rect( 44, 118, 25, 4, color_inactive);   // going over the image
  draw_image_tinted( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px, color_inactive);

  // 1
  Fill_Rect( 92, 85, 4, 14, color_inactive);
  draw_image_tinted( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px, color_inactive);

  // 2
  Fill_Rect( 92, 146, 4, 9, color_inactive);
  draw_image_tinted( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px, color_inactive);

  // 3
  Fill_Rect( 144, 85, 4, 14, color_inactive);
  draw_image_tinted(134,  52, 24, 28, gImage_shifter_digit_3_24x28px, color_inactive);

  // 4
  Fill_Rect( 144, 146, 4, 9, color_inactive);
  draw_image_tinted(134, 160, 24, 28, gImage_shifter_digit_4_24x28px, color_inactive);

  // 5
  Fill_Rect( 196, 85, 4, 37, color_inactive);
  Fill_Rect( 178, 118, 18, 4, color_inactive);
  draw_image_tinted(186,  52, 24, 28, gImage_shifter_digit_5_24x28px, color_inactive);

  // 6
  Fill_Rect( 196, 118, 4, 37, color_inactive);
  Fill_Rect( 178, 118, 18, 4, color_inactive);
  draw_image_tinted(186, 160, 24, 28, gImage_shifter_digit_6_24x28px, color_inactive);




}


void loop()
{


  if (gear_current != gear_previous) { // show a different gear

    // FADE THE PREVIOUS DIGIT

    if (gear_previous == -1) { // reverse
      Fill_Rect( 40, 85, 4, 37, color_inactive);
      Fill_Rect( 44, 118, 25, 4, color_inactive);   // going over the image
      draw_image_tinted( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px, color_inactive);
    }
    else if (gear_previous == 0) { // neutral
      // add this
    }
    else if (gear_previous == 1) { // 1
      Fill_Rect( 92, 85, 4, 14, color_inactive);
      draw_image_tinted( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px, color_inactive);
    }
    else if (gear_previous == 2) { // 2
      Fill_Rect( 92, 146, 4, 9, color_inactive);
      draw_image_tinted( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px, color_inactive);
    }
    else if (gear_previous == 3) { // 3
      Fill_Rect( 144, 85, 4, 14, color_inactive);
      draw_image_tinted(134,  52, 24, 28, gImage_shifter_digit_3_24x28px, color_inactive);
    }
    else if (gear_previous == 4) { // 4
      Fill_Rect( 144, 146, 4, 9, color_inactive);
      draw_image_tinted(134, 160, 24, 28, gImage_shifter_digit_4_24x28px, color_inactive);
    }
    else if (gear_previous == 5) { // 5
      Fill_Rect( 196, 85, 4, 37, color_inactive);
      Fill_Rect( 178, 118, 18, 4, color_inactive);
      draw_image_tinted(186,  52, 24, 28, gImage_shifter_digit_5_24x28px, color_inactive);
    }
    else if (gear_previous == 6) { // 6
      Fill_Rect( 196, 118, 4, 37, color_inactive);
      Fill_Rect( 178, 118, 18, 4, color_inactive);
      draw_image_tinted(186, 160, 24, 28, gImage_shifter_digit_6_24x28px, color_inactive);
    }
    else if (gear_previous == 7) { // 7 - ALL
      // R
      Fill_Rect( 40, 85, 4, 37, color_inactive);
      Fill_Rect( 44, 118, 25, 4, color_inactive);   // going over the image
      draw_image_tinted( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px, color_inactive);

      // 1
      Fill_Rect( 92, 85, 4, 14, color_inactive);
      draw_image_tinted( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px, color_inactive);

      // 2
      Fill_Rect( 92, 146, 4, 9, color_inactive);
      draw_image_tinted( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px, color_inactive);

      // 3
      Fill_Rect( 144, 85, 4, 14, color_inactive);
      draw_image_tinted(134,  52, 24, 28, gImage_shifter_digit_3_24x28px, color_inactive);

      // 4
      Fill_Rect( 144, 146, 4, 9, color_inactive);
      draw_image_tinted(134, 160, 24, 28, gImage_shifter_digit_4_24x28px, color_inactive);

      // 5
      Fill_Rect( 196, 85, 4, 37, color_inactive);
      Fill_Rect( 178, 118, 18, 4, color_inactive);
      draw_image_tinted(186,  52, 24, 28, gImage_shifter_digit_5_24x28px, color_inactive);

      // 6
      Fill_Rect( 196, 118, 4, 37, color_inactive);
      Fill_Rect( 178, 118, 18, 4, color_inactive);
      draw_image_tinted(186, 160, 24, 28, gImage_shifter_digit_6_24x28px, color_inactive);
    }


    // new gear
    if (gear_current == -1) { // reverse
      Fill_Rect( 40, 85, 4, 37, color_active);
      Fill_Rect( 44, 118, 25, 4, color_active);   // going over the image
      //draw_image( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px);
      draw_image_tinted( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px, color_active);
    }
    else if (gear_current == 0) { // reverse

    }
    else if (gear_current == 1) { // reverse
      Fill_Rect( 92, 85, 4, 14, color_active);
      //draw_image( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px);
      draw_image_tinted( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px, color_active);
    }
    else if (gear_current == 2) { // reverse
      Fill_Rect( 92, 146, 4, 9, color_active);
      //draw_image( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px);
      draw_image_tinted( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px, color_active);
    }
    else if (gear_current == 3) { // reverse
      Fill_Rect( 144, 85, 4, 14, color_active);
      //draw_image(134,  52, 24, 28, gImage_shifter_digit_3_24x28px);
      draw_image_tinted(134,  52, 24, 28, gImage_shifter_digit_3_24x28px, color_active);
    }
    else if (gear_current == 4) { // reverse
      Fill_Rect( 144, 146, 4, 9, color_active);
      //draw_image(134, 160, 24, 28, gImage_shifter_digit_4_24x28px);
      draw_image_tinted(134, 160, 24, 28, gImage_shifter_digit_4_24x28px, color_active);
    }
    else if (gear_current == 5) { // reverse
      Fill_Rect( 196, 85, 4, 37, color_active);
      Fill_Rect( 178, 118, 18, 4, color_active);
      //draw_image(186,  52, 24, 28, gImage_shifter_digit_5_24x28px);
      draw_image_tinted(186,  52, 24, 28, gImage_shifter_digit_5_24x28px, color_active);
    }
    else if (gear_current == 6) { // reverse
      Fill_Rect( 196, 118, 4, 37, color_active);
      Fill_Rect( 178, 118, 18, 4, color_active);
      //draw_image(186, 160, 24, 28, gImage_shifter_digit_6_24x28px);
      draw_image_tinted(186, 160, 24, 28, gImage_shifter_digit_6_24x28px, color_active);
    }
    else if (gear_current == 7) { // ALL
      // R
      Fill_Rect( 40, 85, 4, 37, 0xFFFF);
      Fill_Rect( 44, 118, 25, 4, 0xFFFF);   // going over the image
      draw_image( 30,  52, 24, 28, gImage_shifter_digit_R_24x28px);

      // 1
      Fill_Rect( 92, 85, 4, 14, 0xFFFF);
      draw_image( 82,  52, 24, 28, gImage_shifter_digit_1_24x28px);

      // 2
      Fill_Rect( 92, 146, 4, 9, 0xFFFF);
      draw_image( 82, 160, 24, 28, gImage_shifter_digit_2_24x28px);

      // 3
      Fill_Rect( 144, 85, 4, 14, 0xFFFF);
      draw_image(134,  52, 24, 28, gImage_shifter_digit_3_24x28px);

      // 4
      Fill_Rect( 144, 146, 4, 9, 0xFFFF);
      draw_image(134, 160, 24, 28, gImage_shifter_digit_4_24x28px);

      // 5
      Fill_Rect( 196, 85, 4, 37, 0xFFFF);
      Fill_Rect( 178, 118, 18, 4, 0xFFFF);
      draw_image(186,  52, 24, 28, gImage_shifter_digit_5_24x28px);

      // 6
      Fill_Rect( 196, 118, 4, 37, 0xFFFF);
      Fill_Rect( 178, 118, 18, 4, 0xFFFF);
      draw_image(186, 160, 24, 28, gImage_shifter_digit_6_24x28px);
    }

    gear_previous = gear_current;


  }


  gear_current++;
  if (gear_current > 7) {
    gear_current = -1;
    delay(500);
    color_theme = (color_theme + 1) % 6;
  }



  if (color_theme == 0) { // red on gray
    color_active = color_red;
    color_inactive = color_dark_gray;
  } else if (color_theme == 1) { // white on blue
    color_active = 0xFFFF;
    color_inactive = color_dark_blue; // red on blue
  } else if (color_theme == 2) {
    color_active = color_red;
    color_inactive = color_dark_blue;
  } else if (color_theme == 3) { // white on gray
    color_active = 0xFFFF;
    color_inactive = color_dark_gray;
  } else if (color_theme == 4) { // red on blue
    color_active = color_red;
    color_inactive = color_dark_blue;
  } else if (color_theme == 5) { // red on blue
    color_active = color_red;
    color_inactive = color_light_gray;
  }


  delay(150);

 }
