#include "mbed.h"
#include "TCPSocket.h"
#include "MXCHIPInterface.h"

MXCHIPInterface wifi(D1,D0);
Serial pc(STDIO_UART_TX,STDIO_UART_RX,115200);
DigitalOut led1(LED1);

int main( void )
{

    printf("NetworkSocketAPI Example\r\n");

    wifi.connect("YouXX", "caiufo666");
    const char *ip = wifi.get_ip_address();
    const char *mac = wifi.get_mac_address();
    printf("IP address is: %s\r\n", ip ? ip : "No IP");
    printf("MAC address is: %s\r\n", mac ? mac : "No MAC");

    TCPSocket tcpsocket;
    printf("Sending HTTP request to www.arm.com...\r\n");
    // Open a socket on the network interface, and create a TCP connection to www.arm.com
    tcpsocket.open(&wifi);
    printf("finish open()\r\n");
    int value=tcpsocket.connect("www.arm.com", 80);
    if(!value)
    	printf("connect to ww.arm.com successfully£¡\r\n");

    // Send a simple http request
    char sbuffer[] = "GET / HTTP/1.1\r\nHost: www.arm.com\r\n\r\n";
    int scount = tcpsocket.send(sbuffer, sizeof sbuffer);
    printf("sent %d [%.*s]\r\n", scount, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);

    // Recieve a simple http response and print out the response line
    char rbuffer[64];
    int rcount = tcpsocket.recv(rbuffer, sizeof rbuffer);
    printf("recv %d [%.*s]\r\n", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);

    // Close the socket to return its memory and bring down the network interface
    tcpsocket.close();

    wifi.disconnect();

    printf("Done\r\n");

}


