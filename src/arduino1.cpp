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

void loop() {
    uint8_t len;
    uint8_t buf[8];

    if(can.checkReceive() == CAN_MSGAVAIL) {
        can.readMsgBuf(&len, buf);
        uint32_t canId = can.getCanId();

        Serial.print(canId, HEX);
        for(uint8_t i = 0; i < len; ++i) {
            Serial.print(buf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }
}