
// ESP32 Bluetooth App


#include "BluetoothSerial.h" 


#define DELAY 1000                      


BluetoothSerial ESP_BT; 


int led_pin_1 = 15;
int led_pin_2 = 2;
int led_pin_3 = 4;                      


int incoming;                           
unsigned long now;                      
unsigned long time_button1;            


void setup() {
  Serial.begin(19200);
  ESP_BT.begin("ESP32_Controle");        

  pinMode (led_pin_1, OUTPUT);          

}

void loop() {
  now = millis();                       

  
  if(digitalRead(led_pin_1) and now > time_button1 + DELAY) {     
    digitalWrite(led_pin_1, 0);                                   
    ESP_BT.write(10);                                             
    Serial.print("Button 1 timeout - value: 0");                  
  }

  
  if (ESP_BT.available())
  {
    // Aguarda chegar todos os bytes da mensagem
    delay(20);

    // Se chegou mais de um byte, considera texto (Button4)
    if (ESP_BT.available() > 1)
    {
      String texto = "";

      while (ESP_BT.available())
      {
        texto += (char)ESP_BT.read();
      }

      texto.trim();

      Serial.print("Texto recebido: ");
      Serial.println(texto);

      // Exemplos de comandos enviados pelo TextBox
      if (texto == "LED1_ON")
      {
        digitalWrite(led_pin_1, HIGH);
        time_button1 = now;
      }
      else if (texto == "LED1_OFF")
      {
        digitalWrite(led_pin_1, LOW);
      }

      // Envia confirmação para o aplicativo
      ESP_BT.print("Recebido: ");
      ESP_BT.println(texto);
    }

    else
    {
      incoming = ESP_BT.read();

      int button = incoming / 10;
      int value  = incoming % 10;

      switch (button)
      {
        case 1:
          Serial.print("Button 1: ");
          Serial.println(value);
          digitalWrite(led_pin_1, value);
          if (value == 1) time_button1 = now;
          break;
      }
    }
  }
}
