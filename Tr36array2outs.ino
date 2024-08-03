#include <SPI.h>                                          // Подключаем библиотеку для работы с шиной SPI
#include <nRF24L01.h>                                     // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>                                         // Подключаем библиотеку для работы с nRF24L01+

#include "MIDIUSB.h" 

//#include <RF24Network.h>
//#include <Servo.h> 

RF24           radio(6, 9); 
int val; 
//Servo          myservo;  

int            data[2];                                   // Создаём массив для приёма данных
byte x = 255;
void setup(){
  Serial.begin(115200);
//  myservo.attach(4);
  
    radio.begin();                                        // Инициируем работу nRF24L01+
    radio.setChannel(5);                                  // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
    radio.setDataRate     (RF24_250KBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
    radio.setPALevel      (RF24_PA_LOW);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
    radio.openWritingPipe (0x1234567890LL);               // Открываем трубу с идентификатором 0x1234567890 для передачи данных (на одном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
}
void loop(){

   midiEventPacket_t rx;

 do {
    rx = MidiUSB.read();

 if (rx.byte2 == 36 && rx.header==9)
    {bitClear(x, 0);}
 if (rx.byte2 == 36 && rx.header==8)
     {bitSet(x, 0);}
  
 if (rx.byte2 == 37 && rx.header==9)
    {bitClear(x, 1);}
 if (rx.byte2 == 37 && rx.header==8)
    {bitSet(x, 1);}

 if (rx.byte2 == 38 && rx.header==9)
    {bitClear(x, 2);}
 if (rx.byte2 == 38 && rx.header==8)
    {bitSet(x, 2);}
 
  radio.write(&x, sizeof(x));
 } while (rx.header != 0);

}
