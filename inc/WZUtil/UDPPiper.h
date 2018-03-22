#ifndef UDPPIPER_H_
#define UDPPIPER_H_

#include "frame.h"
#include "WZPiper.h"

class UDPPiper : public WZPiper {
 public:
   UDPPiper();
   ~UDPPiper();
   // initialize the server
   virtual void init_as_server();
   // set the ip and port according to the config file
   virtual void set_config_info(char file_path[256]);
   // link to the 
   virtual void init_as_client();
   // read data from the pipe
   virtual int do_read(Frame& mail);
   // write data to the pipe
   virtual void do_write(Frame mail);


 private:
   // sokect ip address
   char UDP_ip [128];
   // sokect conect port 
   int UDP_port;
   // sokect id
   int UDP_sockfd;
   // buffer size
   char buffer[1024];
};

#endif //UDPPiper
