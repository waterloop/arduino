#include <stdint.h>

#define IMU_1_ACCEL_ID_1 1024
#define IMU_1_GYRO_ID_1 1025

#define IMU_1_ACCEL_ID_2 1026
#define IMU_1_GYRO_ID_2 1027

#define TEMP_1_ID_1 1028
#define TEMP_1_ID_2 1029
#define TEMP_1_ID_3 1030
#define TEMP_1_ID_4 1031
#define TEMP_1_ID_5 1032
#define TEMP_1_ID_6 1033
#define TEMP_1_ID_7 1034
#define TEMP_1_ID_8 1035
#define TEMP_1_ID_9 1036
#define TEMP_1_ID_10 1037

#define TEMP_2_ID_1 1038
#define TEMP_2_ID_2 1039

#define PHOTO_2_ID_1 1040
#define PHOTO_2_ID_2 1041

#define HALL_1_ID_1 1042
#define HALL_1_ID_2 1043
#define HALL_1_ID_3 1044
#define HALL_1_ID_4 1045
#define HALL_1_ID_5 1046
#define HALL_1_ID_6 1047

#define PIEZO_1_ID_1 1048
#define PIEZO_1_ID_2 1049

const int IMU_ACCEL_ID[] = {IMU_1_ACCEL_ID_1, IMU_1_ACCEL_ID_2};
const int IMU_GYRO_ID[] = {IMU_1_GYRO_ID_1, IMU_1_GYRO_ID_2};
const int TEMP_1_ID[] = {TEMP_1_ID_1, TEMP_1_ID_2, TEMP_1_ID_3, TEMP_1_ID_4, TEMP_1_ID_5, TEMP_1_ID_6, TEMP_1_ID_7, TEMP_1_ID_8, TEMP_1_ID_9, TEMP_1_ID_10};
const int TEMP_2_ID[] = {TEMP_2_ID_1, TEMP_2_ID_2};
const int PHOTO_2_ID[] = {PHOTO_2_ID_1, PHOTO_2_ID_2};
const int HALL_1_ID[] = {HALL_1_ID_1, HALL_1_ID_2, HALL_1_ID_3, HALL_1_ID_4, HALL_1_ID_5, HALL_1_ID_6};
const int PIEZO_1_ID[] = {PIEZO_1_ID_1, PIEZO_1_ID_2};

void send_can(uint32_t packet_id, uint8_t len, uint8_t *data);

void serialize_mcp6050_accelerometer(int16_t x, int16_t y, int16_t z) {
    uint8_t data[6];

    // flip the indexes since it takes the last 8 bits each time 
    
    data[1] = x;
    data[0] = x >> 8;

    data[3] = y;
    data[2] = y >> 8;

    data[5] = z;
    data[4] = z >> 8;

    send_can(IMU_1_ACCEL_ID_1, 6, data);
}

void serialize_tmp411(int16_t t) {
    uint8_t data[2];

    data[1] = t;
    data[0] = t >> 8;

    send_can(TEMP_1_ID_1, 2, data);
}

void serialize_temp2(int16_t t) {
    uint8_t data[2];

    data[1] = t;
    data[0] = t >> 8;

    send_can(TEMP_1_ID_1, 2, data);
}

void serialize_photo2(int32_t c) {
    uint8_t data[4];

    data[3] = c;
    data[2] = c >> 8;
    data[1] = c >> 16;
    data[0] = c >> 24;

    send_can(PHOTO_2_ID_1, 4, data);
}

void serialize_hall1(int16_t f) {
    uint8_t data[2];

    data[1] = f;
    data[0] = f >> 8;

    send_can(HALL_1_ID_1, 2, data);
}

void serialize_piezo1(int16_t v) {
    uint8_t data[2];

    data[1] = v;
    data[0] = v >> 8;

    send_can(PIEZO_1_ID_1, 2, data);
}