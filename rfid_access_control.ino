#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SS_PIN 10
#define RST_PIN 9
#define RELAY_PIN 3
#define LED_PIN 4

MFRC522 rfid(SS_PIN, RST_PIN);

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// Card status
bool card1Used = false;
bool card2Used = false;

// RFID UIDs
String card1 = "11 CF 9B 5D";
String card2 = "50 80 3D 61";
String resetCard = "E5 3F 78 06";

void showMessage(String msg)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println(msg);
  display.display();
}

void countdown(int seconds)
{
  // TV ON
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);

  showMessage("TV STARTS");
  delay(2000);

  for (int i = seconds; i >= 0; i--)
  {
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(15, 0);
    display.println("TV RUNNING");

    display.setTextSize(4);
    display.setCursor(40, 20);
    display.println(i);

    display.display();

    delay(1000);
  }

  // TV OFF
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  showMessage("TV OFF");
  delay(2000);

  showMessage("READY");
}

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED not found");
    while (true);
  }

  showMessage("READY");

  Serial.println("RFID Reader Ready");
}

void loop()
{
  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++)
  {
    if (rfid.uid.uidByte[i] < 0x10)
      uid += "0";

    uid += String(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1)
      uid += " ";
  }

  uid.toUpperCase();

  Serial.print("Card UID: ");
  Serial.println(uid);

  // CARD 1
  if (uid == card1)
  {
    if (!card1Used)
    {
      card1Used = true;
      countdown(20);
    }
    else
    {
      showMessage("CARD1 USED");
      delay(2000);
      showMessage("READY");
    }
  }

  // CARD 2
  else if (uid == card2)
  {
    if (!card2Used)
    {
      card2Used = true;
      countdown(40);
    }
    else
    {
      showMessage("CARD2 USED");
      delay(2000);
      showMessage("READY");
    }
  }

  // RESET CARD
  else if (uid == resetCard)
  {
    card1Used = false;
    card2Used = false;

    showMessage("RESET");
    delay(2000);

    showMessage("READY");
  }

  // UNKNOWN CARD
  else
  {
    showMessage("INVALID");
    delay(2000);

    showMessage("READY");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
