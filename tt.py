import binascii

# CRC16-CCITT (0x1021) 计算函数
def crc16_ccitt(data):
    crc = 0
    for byte in data:
        crc ^= byte << 8
        for _ in range(8):
            if crc & 0x8000:
                crc = (crc << 1) ^ 0x1021
            else:
                crc = crc << 1
        crc &= 0xFFFF
    return crc

# 读取文件并计算 CRC16-CCITT 校验值
def calculate_crc16_file(file_path):
    try:
        with open(file_path, 'rb') as file:
            data = file.read()
            crc_result = crc16_ccitt(data)
            print(f"CRC16-CCITT 校验结果: {crc_result:04X}")
    except FileNotFoundError:
        print(f"文件未找到: {file_path}")
    except Exception as e:
        print(f"发生错误: {e}")

# 示例用法
file_path = 'tmp.jpg'  # 替换为你的文件路径
calculate_crc16_file(file_path)