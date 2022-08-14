#include <Arduino.h>
#include <WiFi.h>
#include <hhn_wifi_connection.h>
#include <hhn_server.h>
#include <hhn_socket.h>

void setup()
{
  HHN::WiFi_Connection::getConnection()->connect();
  
  // put your setup code here, to run once:
}

void loop()
{
  HHN::Server::getServer()->run();
  HHN::Socket::run_sockets();
}