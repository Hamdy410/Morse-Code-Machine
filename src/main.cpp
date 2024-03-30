#include <Arduino.h>

#define BUZZER 2
#define GREEN 4
#define RED 3
#define BUTTON 5
#define potentiometer A5
#define LDR A4

String input;
int currentState = 0;
String morse_input;

void setup()
{
  pinMode(BUZZER, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop()
{
  double sensorValue = analogRead(potentiometer);
  if (511.5 <= sensorValue && sensorValue <= 1023)
  {
    currentState = 0;
    Serial.println("Morse Encoder");
  }
  else
  {
    currentState = 1;
    Serial.println("Morse Decoder");
  }

  if (currentState == 0)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    if (Serial.available() > 0)
    {
      input = Serial.readString();
      Serial.println(input);

      for (unsigned int i = 0; i < input.length(); i++)
      {
        delay(100); // Period between elements of same letter
        if (input[i] == '.' || input[i] == '-')
        {
          digitalWrite(BUZZER, HIGH);
          delay(input[i] == '.' ? 100 : 300);
          digitalWrite(BUZZER, LOW);
        }
        else if (input[i] == '/')
        {
          delay(700);
        }
        else
        {
          delay(300);
        }
      }

      digitalWrite(BUZZER, LOW);
      delay(700);
    }
  }
  else
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    int lastState = HIGH; // Initial state of LDR (assuming bright = HIGH)
    int currentReading = analogRead(LDR);
    int threshold = 42; // Adjust threshold based on your LDR sensitivity
    unsigned long startTime = millis();

    while (Serial.available() == 0)
    { // Wait for serial data or Morse code to finish
      int newReading = analogRead(LDR);

      if ((lastState == LOW && newReading > threshold) || (lastState == HIGH && newReading < threshold))
      {
        int pulseLength = millis() - startTime;
        startTime = millis();
        if (currentReading > newReading)
        {
          if (0 < pulseLength && pulseLength <= 350)
          {
            morse_input += ".";
          }
          else
          {
            morse_input += "-";
          }
        }
        else
        {
          if (pulseLength >= 900)
          {
            morse_input += "/";
          }
          else
          {
            morse_input += "";
          }
        }
        lastState = newReading > threshold ? HIGH : LOW;
        currentReading = newReading;
      }

      if (digitalRead(BUTTON) == HIGH)
      {
        Serial.println("Clicked");
        Serial.println(morse_input);
        morse_input.remove(0, morse_input.length());
        delay(500);
        break;
      }
    }
    Serial.println("Got Out!");
  }
}
