#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define VRX_PIN A0
#define VRY_PIN A1
#define SW_PIN 2

int playerX = SCREEN_WIDTH / 2;
int playerY = SCREEN_HEIGHT - 10;
int playerSize = 8;

int obstacleX = random(0, SCREEN_WIDTH);
int obstacleY = 0;
int obstacleSize = 10;
int obstacleSpeed = 2;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  pinMode(SW_PIN, INPUT_PULLUP);
  display.clearDisplay();
}

void loop() {
  int xValue = analogRead(VRX_PIN);
  int yValue = analogRead(VRY_PIN);
  
  playerX = map(xValue, 0, 1023, 0, SCREEN_WIDTH - playerSize);
  playerY = map(yValue, 0, 1023, 0, SCREEN_HEIGHT - playerSize);

  
  obstacleY += obstacleSpeed;
  if (obstacleY > SCREEN_HEIGHT) {
    obstacleY = 0;
    obstacleX = random(0, SCREEN_WIDTH - obstacleSize);
  }

  if (playerX < obstacleX + obstacleSize &&
      playerX + playerSize > obstacleX &&
      playerY < obstacleY + obstacleSize &&
      playerY + playerSize > obstacleY) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 20);
    display.println("Game Over");
    display.display();
    delay(2000);
    obstacleY = 0;
    obstacleX = random(0, SCREEN_WIDTH - obstacleSize);
  }


  display.clearDisplay();

  display.fillRect(playerX, playerY, playerSize, playerSize, SSD1306_WHITE);

  display.fillRect(obstacleX, obstacleY, obstacleSize, obstacleSize, SSD1306_WHITE);

  display.display();

  delay(30);
}

