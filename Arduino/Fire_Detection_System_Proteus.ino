#include <Arduino.h>
#include <LiquidCrystal.h>

// Eng.Samer Alaa Abu Zaina 
// Fire Detection System with GSM Alert

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int gas_Sensor = 8;
const int flame_Sensor = 9;
const int motor_pin = 10;
const int buzzer_Pin = 11;

bool fire_Status = LOW;
bool flame_Status = LOW;
bool smsSent = false;

void SendMessage();

void setup()
{
  Serial.begin(9600);

  pinMode(buzzer_Pin, OUTPUT);
  pinMode(motor_pin, OUTPUT);
  pinMode(gas_Sensor, INPUT);
  pinMode(flame_Sensor, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Fire DETECTION");
  lcd.setCursor(0, 1);
  lcd.print("   SYSTEM");
  delay(2000);
}

void loop()
{
  fire_Status = digitalRead(gas_Sensor);
  flame_Status = digitalRead(flame_Sensor);
  delay(100);

  if (fire_Status == HIGH && flame_Status == HIGH)
  {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fire Detected!");
    lcd.setCursor(0, 1);
    lcd.print("Sending msg...");

    digitalWrite(buzzer_Pin, HIGH);
    digitalWrite(motor_pin, HIGH);

    if (!smsSent)
    {
      delay(1000);
      SendMessage();
      smsSent = true;
    }
  }
  else
  {

    smsSent = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fire Not");
    lcd.setCursor(0, 1);
    lcd.print("Detected");

    digitalWrite(buzzer_Pin, LOW);
    digitalWrite(motor_pin, LOW);
    delay(500);
  }
}

void SendMessage()
{
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+972597776840\"\r");
  delay(1000);
  Serial.println("Fire Detected inside home");
  delay(100);
  Serial.println((char)26);
  delay(1000);
}
