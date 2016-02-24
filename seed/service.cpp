/*
*  PHP2Uni
*
* Author: Thomas Pasquier <tfjmp2@cam.ac.uk>
*
* Copyright (C) 2016 University of Cambridge
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include <os>
#include <net/inet4>
#include <math.h>
#include <iostream>
#include <sstream>
#include <net/dhcp/dh4client.hpp>
#include "request.hpp"
#include "response.hpp"
#include "response_factory.hpp"

using namespace std::chrono;

// An IP-stack object
std::unique_ptr<net::Inet4<VirtioNet> > inet;

void Service::start() {
  // Assign a driver (VirtioNet) to a network interface (eth0)
  // @note: We could determine the appropirate driver dynamically, but then we'd
  // have to include all the drivers into the image, which  we want to avoid.
  Nic<VirtioNet>& eth0 = Dev::eth<0,VirtioNet>();

  // Bring up a network stack, attached to the nic
  // @note : No parameters after 'nic' means we'll use DHCP for IP config.
  inet = std::make_unique<net::Inet4<VirtioNet> >(eth0);

  // Static IP configuration, until we (possibly) get DHCP
  // @note : Mostly to get a robust demo service that it works with and without DHCP
  inet->network_config( {{ 10,0,0,42 }},      // IP
			{{ 255,255,255,0 }},  // Netmask
			{{ 10,0,0,1 }},       // Gateway
			{{ 8,8,8,8 }} );      // DNS

  printf("Size of IP-stack: %i b \n",sizeof(inet));
  printf("Service IP address: %s \n", inet->ip_addr().str().c_str());

  // Set up a TCP server on port 80
  net::TCP::Socket& sock =  inet->tcp().bind(80);

  printf("SERVICE: %i open ports in TCP @ %p \n",
      inet->tcp().openPorts(), &(inet->tcp()));

  // TCP connection handler - here a hardcoded HTTP-service
  sock.onAccept([](net::TCP::Socket& conn){
    std::string str_request = conn.read(1024);
    printf("SERVICE got data: %s\n\n", str_request.c_str());
    // parse the request
    http::Request req(str_request);
    http::ResponseFactory rf;
    // retrieve the response
    http::Response res = rf.create(req);
    conn.write(res.get_header());
    conn.write(res.get_body());
  });

  printf("*** PHP2UNI SERVICE STARTED *** \n");
}
