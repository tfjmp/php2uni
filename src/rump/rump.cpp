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

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include <iostream>
#include <string>
#include "request.hpp"
#include "response.hpp"
#include "response_factory.hpp"

#define PORT "80"

void handle_request(int conn){
	int status;
	char buf[1025];
	memset(buf, 0, 1024);
	status = recv(conn, buf, 1024, 0);
	std::string str_request(buf);
	http::Request req(str_request);
	http::ResponseFactory rf;
	http::Response res = rf.create(req);
	std::string header = res.get_header();
	std::string body = res.get_body();
	send(conn, header.c_str(), header.length(), 0);
	send(conn, body.c_str(), body.length(), 0);
	close(conn);
}

int main(int argc, char * argv[])
{
	int status;
	struct addrinfo hints, * res;
	int listner;

	memset(& hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // We don't care V4 AF_INET or 6 AF_INET6
	hints.ai_socktype = SOCK_STREAM; // TCP Socket SOCK_DGRAM
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo(NULL, PORT, &hints, &res);
	if(status != 0)
	{
		fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(status));
	}

	listner = socket(res->ai_family,res->ai_socktype, res->ai_protocol);
	if(listner < 0 )
	{
		fprintf(stderr,"socket error: %s\n",gai_strerror(status));
	}

	status = bind(listner, res->ai_addr, res->ai_addrlen);
	if(status < 0)
	{
		fprintf(stderr,"bind: %s\n",gai_strerror(status));
	}

	status = listen(listner, 10);
	if(status < 0)
	{
		fprintf(stderr,"listen: %s\n",gai_strerror(status));
	}

	freeaddrinfo(res);

	struct sockaddr_storage client_addr;
	socklen_t addr_size;
	addr_size = sizeof client_addr;

	printf("Listening on port %s ...\n",  PORT);
	while(1){
		printf("Accepting connections ...\n");
		int conn = accept(listner, (struct sockaddr *) & client_addr, &addr_size);
		printf("Connection received\n");
		if(conn < 0)
		{
			fprintf(stderr,"accept: %s\n",gai_strerror(conn));
			continue;
		}
		handle_request(conn);
	}

	return 0;
}
