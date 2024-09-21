import os
import socket
import struct
import time

# Функция для расчёта контрольной суммы (checksum)
def checksum(source_string):
    sum = 0
    count_to = (len(source_string) // 2) * 2
    count = 0
    while count < count_to:
        this_val = source_string[count + 1] * 256 + source_string[count]
        sum = sum + this_val
        sum = sum & 0xFFFFFFFF
        count = count + 2
    if count_to < len(source_string):
        sum = sum + source_string[len(source_string) - 1]
        sum = sum & 0xFFFFFFFF
    sum = (sum >> 16) + (sum & 0xFFFF)
    sum = sum + (sum >> 16)
    answer = ~sum
    answer = answer & 0xFFFF
    answer = answer >> 8 | (answer << 8 & 0xFF00)
    return answer

# Функция для отправки ICMP запроса
def send_ping(sock, addr, icmp_id, ttl):
    icmp_type = 8  # ICMP Echo Request
    icmp_code = 0
    checksum_val = 0
    icmp_seq = 1

    # Формирование ICMP-заголовка
    header = struct.pack('bbHHh', icmp_type, icmp_code, checksum_val, icmp_id, icmp_seq)
    data = struct.pack('d', time.time())  # Используем текущее время в качестве данных
    checksum_val = checksum(header + data)
    header = struct.pack('bbHHh', icmp_type, icmp_code, socket.htons(checksum_val), icmp_id, icmp_seq)

    # Установка TTL
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_TTL, ttl)

    # Отправляем ICMP запрос
    packet = header + data
    sock.sendto(packet, (addr, 1))

# Функция для получения ICMP ответа
def receive_ping(sock, icmp_id, expected_addr, timeout):
    sock.settimeout(timeout)
    try:
        packet, addr = sock.recvfrom(1024)
        ip_header = packet[:20]
        ip_src_addr = socket.inet_ntoa(ip_header[12:16])

        # Печатаем IP адрес отправителя и возвращаем адрес и успешный ответ
        if ip_src_addr == expected_addr or expected_addr == '*':
            icmp_header = packet[20:28]
            type, code, checksum, p_id, sequence = struct.unpack('bbHHh', icmp_header)
            return ip_src_addr, True
        return None, False
    except socket.timeout:
        return None, False

# Функция трассировки маршрута
def trace_route(host):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
        sock.settimeout(2)

        icmp_id = os.getpid() & 0xFFFF  # Используем PID процесса как ID
        max_hops = 30
        for ttl in range(1, max_hops + 1):
            send_ping(sock, host, icmp_id, ttl)
            addr, success = receive_ping(sock, icmp_id, '*', 2)

            if success:
                print(f"{ttl} {addr}")
                if addr == host:
                    break
            else:
                print(f"{ttl} *")

        sock.close()
    except PermissionError:
        print("Необходимы права суперпользователя для отправки ICMP пакетов.")
    except Exception as e:
        print(f"Ошибка при трассировке {host}: {e}")

if __name__ == "__main__":
    print("Трассировка маршрута")
    host = input("Введите адрес для трассировки маршрута: ")
    trace_route(host)