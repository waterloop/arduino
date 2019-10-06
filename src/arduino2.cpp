#include <Arduino.h>
#include <mcp_can.h>

// CS is on pin 10
MCP_CAN can(10);

void setup() {
    Serial.begin(115200);

    while(can.begin(CAN_500KBPS) != CAN_OK) {
        Serial.println("CAN bus init failed");
        delay(100);
    }
    Serial.println("CAN bus init success");
}

uint8_t buf[8];

void loop() {
    can.sendMsgBuf(0, 0, 8, buf);

    for(int i = 7; i >= 0 && !++buf[i]; --i);

    delay(100);
}