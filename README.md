# IoT Access control system

[中文版說明](https://github.com/jason810496/Access-control-system/blob/main/README_zh.md)
## Description 

Demo of access control IoT system that allow admin user to change password instantly and control remotely

## Deployment
NodeMCU can be seen as a server  , after setting **Port forwarding** , users are allowed to connect to the system from WAN ( Wide Area Network )

## How to Connect to the System ? 

### Port Forwarding 
To remote control our device from WAN , it's essential to setup the **Port Forwading** in the AP ( Access Point , i.e. the WiFi route in my house )  , which **Forward** the request from WAN to my deviec (NodeMCU) 

### DNS Setting
I use [no-ip](https://www.noip.com/) to manage the temporary dynamic DNS record ( IP to domain name ) which is more user-friendly and convenient than manual typing IP address on the browser . 

I choise `nodemcu314.ddns.net` as my domain name , so that typing `http://nodemcu314.ddns.net/` on the browser would redirect to NodeMCU( which can also be seen as a Web server )

Note . 

It's not available right now , 
`Edit time 2022/5/13`
### After Setting 

###### tags: `IoT`
