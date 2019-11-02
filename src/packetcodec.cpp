#include <stdint.h>

const int IMU_1_ACCEL_ID[] = {1024, 1026};
const int IMU_1_GYRO_ID[] = {1025, 1027};
const int TEMP_1_ID[] = {1028, 1029, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037};
const int TEMP_2_ID[] = {1038, 1039};
const int PHOTO_2_ID[] = {1040, 1041};
const int HALL_1_ID[] = {1042, 1043, 1044, 1045, 1046, 1047};
const int PIEZO_1_ID[] = {1048, 1049};

void send_can(uint32_t packet_id, uint8_t len, uint8_t *data);

// serialize data 

void serialize_mcp6050_accelerometer(int8_t instance, int16_t x, int16_t y, int16_t z) {
    uint8_t data[6];

    // flip the indexes since it takes the last 8 bits each time 
    
    data[1] = x;
    data[0] = x >> 8;

    data[3] = y;
    data[2] = y >> 8;

    data[5] = z;
    data[4] = z >> 8;

    send_can(IMU_1_ACCEL_ID[instance], 6, data);
}

void serialize_mcp6050_gyroscope(int8_t instance, int16_t x, int16_t y, int16_t z) {
    uint8_t data[6];

    data[1] = x;
    data[0] = x >> 8;

    data[3] = y;
    data[2] = y >> 8;

    data[5] = z;
    data[4] = z >> 8;

    send_can(IMU_1_GYRO_ID[instance], 6, data);
}

void serialize_tmp411(int8_t instance, int16_t t) {
    uint8_t data[2];

    data[1] = t;
    data[0] = t >> 8;

    send_can(TEMP_1_ID[instance], 2, data);
}

void serialize_temp2(int8_t instance, int16_t t) {
    uint8_t data[2];

    data[1] = t;
    data[0] = t >> 8;

    send_can(TEMP_1_ID[instance], 2, data);
}

void serialize_photo2(int8_t instance, int32_t c) {
    uint8_t data[4];

    data[3] = c;
    data[2] = c >> 8;
    data[1] = c >> 16;
    data[0] = c >> 24;

    send_can(PHOTO_2_ID[instance], 4, data);
}

void serialize_hall1(int8_t instance, int16_t f) {
    uint8_t data[2];

    data[1] = f;
    data[0] = f >> 8;

    send_can(HALL_1_ID[instance], 2, data);
}

void serialize_piezo1(int8_t instance, int16_t v) {
    uint8_t data[2];

    data[1] = v;
    data[0] = v >> 8;

    send_can(PIEZO_1_ID[instance], 2, data);
}