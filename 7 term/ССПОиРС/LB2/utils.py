import ipaddress
import netifaces
import socket
import struct

def getNetworkInfo():
    iface = netifaces.gateways()['default'][netifaces.AF_INET][1]
    addresses = netifaces.ifaddresses(iface)

    addr = addresses[netifaces.AF_INET][0]['addr']
    mask = addresses[netifaces.AF_INET][0]['netmask']

    network = ipaddress.ip_network(f"{addr}/{mask}", strict=False)
    broadcast = str(network.broadcast_address)

    return addr,network.network_address, mask, broadcast

def setGroup(sock, multicast):
    group = socket.inet_aton(multicast)
    request = struct.pack('4sL', group, socket.INADDR_ANY)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, request)

def dropGroup(sock, multicast):
    group = socket.inet_aton(multicast)
    request = struct.pack('4sL', group, socket.INADDR_ANY)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_DROP_MEMBERSHIP, request)