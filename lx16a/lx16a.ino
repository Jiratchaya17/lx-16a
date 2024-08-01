#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  delay(1000);  // รอให้เซอร์โวมอเตอร์พร้อมทำงาน
}

void loop() {
  // ตั้งตำแหน่งเซอร์โวมอเตอร์ 10 ตัวในเวลาเดียวกัน
  setServoPosition(1, 500);  // เซอร์โวมอเตอร์ ID 1
  setServoPosition(2, 600);  // เซอร์โวมอเตอร์ ID 2
  setServoPosition(3, 700);  // เซอร์โวมอเตอร์ ID 3
  setServoPosition(4, 800);  // เซอร์โวมอเตอร์ ID 4
  setServoPosition(5, 900);  // เซอร์โวมอเตอร์ ID 5
  setServoPosition(6, 1000); // เซอร์โวมอเตอร์ ID 6
  setServoPosition(7, 1100); // เซอร์โวมอเตอร์ ID 7
  setServoPosition(8, 1200); // เซอร์โวมอเตอร์ ID 8
  setServoPosition(9, 1300); // เซอร์โวมอเตอร์ ID 9
  setServoPosition(10, 1400);// เซอร์โวมอเตอร์ ID 10
  delay(1000);

  setServoPosition(1, 1400); // เซอร์โวมอเตอร์ ID 1
  setServoPosition(2, 1300); // เซอร์โวมอเตอร์ ID 2
  setServoPosition(3, 1200); // เซอร์โวมอเตอร์ ID 3
  setServoPosition(4, 1100); // เซอร์โวมอเตอร์ ID 4
  setServoPosition(5, 1000); // เซอร์โวมอเตอร์ ID 5
  setServoPosition(6, 900);  // เซอร์โวมอเตอร์ ID 6
  setServoPosition(7, 800);  // เซอร์โวมอเตอร์ ID 7
  setServoPosition(8, 700);  // เซอร์โวมอเตอร์ ID 8
  setServoPosition(9, 600);  // เซอร์โวมอเตอร์ ID 9
  setServoPosition(10, 500); // เซอร์โวมอเตอร์ ID 10
  delay(1000);
}

void setServoPosition(int id, int position) {
  byte buf[10];
  buf[0] = 0x55;  // Header 1
  buf[1] = 0x55;  // Header 2
  buf[2] = 0x07;  // Length
  buf[3] = id;1,2,3,4,5,6,7,8,9,10    // Servo ID
  buf[4] = 0x01;  // Command
  buf[5] = 0x2A;  // Parameter - Write position
  buf[6] = position & 0xFF;        // Position low byte
  buf[7] = (position >> 8) & 0xFF; // Position high byte
  buf[8] = 0x00;  // Time low byte (0 for default)
  buf[9] = 0x00;  // Time high byte (0 for default)
  
 // คำนวณ checksum
  byte checksum = 0;
  for(int i = 2; i < 10; i++) {
    checksum += buf[i];
  }
  checksum = ~checksum;
  
  // ส่งข้อมูลไปยังเซอร์โวมอเตอร์
  for(int i = 0; i < 10; i++) {
    mySerial.write(buf[i]);
  }
  mySerial.write(checksum);  // ส่ง checksum
}