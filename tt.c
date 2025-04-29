#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// CRC16-CCITT (0x1021) 计算函数
uint16_t crc16_ccitt(const uint8_t* data, size_t length) {
    uint16_t crc = 0;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i] << 8;
        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc = crc << 1;
            }
        }
        crc &= 0xFFFF;
    }
    return crc;
}

// 读取文件并计算 CRC16-CCITT 校验值
void calculate_crc16_file(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("文件未找到: %s\n", file_path);
        return;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 分配内存读取文件内容
    uint8_t* buffer = (uint8_t*)malloc(file_size);
    if (buffer == NULL) {
        printf("内存分配失败\n");
        fclose(file);
        return;
    }

    // 读取文件内容
    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        printf("读取文件失败\n");
        free(buffer);
        fclose(file);
        return;
    }

    // 计算 CRC16-CCITT
    uint16_t crc_result = crc16_ccitt(buffer, file_size);
    printf("CRC16-CCITT 校验结果: %04X\n", crc_result);

    // 释放资源
    free(buffer);
    fclose(file);
}

int main() {
    const char* file_path = "tmp.jpg"; // 替换为你的文件路径
    calculate_crc16_file(file_path);
    return 0;
}