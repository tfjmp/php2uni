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

#ifndef PHP2UNI_RESPONSE_HPP
#define PHP2UNI_RESPONSE_HPP

#include <sstream>
#include "message.hpp"
#include "request.hpp"

namespace http {
  class Response: public Message{
  protected:
    Request _req;
    int _status;

    std::map<int, std::string> status_codes {
      //< 1xx: Informational - Request received, continuing process
      {100, "Continue"},
      {101, "Switching Protocols"},
      {102, "Processing"},

      //< 2xx: Success - The action was successfully received, understood, and accepted
      {200, "OK"},
      {201, "Created"},
      {202, "Accepted"},
      {203, "Non-Authoritative Information"},
      {204, "No Content"},
      {205, "Reset Content"},
      {206, "Partial Content"},
      {207, "Multi-Status"},
      {208, "Already Reported"},
      {226, "IM Used"},

      //< 3xx: Redirection - Further action must be taken in order to complete the request
      {300, "Multiple Choices"},
      {301, "Moved Permanently"},
      {302, "Found"},
      {303, "See Other"},
      {304, "Not Modified"},
      {305, "Use Proxy"},
      {307, "Temporary Redirect"},
      {308, "Permanent Redirect"},

      //< 4xx: Client Error - The request contains bad syntax or cannot be fulfilled
      {400, "Bad Request"},
      {401, "Unauthorized"},
      {402, "Payment Required"},
      {403, "Forbidden"},
      {404, "Not Found"},
      {405, "Method Not Allowed"},
      {406, "Not Acceptable"},
      {407, "Proxy Authentication Required"},
      {408, "Request Timeout"},
      {409, "Conflict"},
      {410, "Gone"},
      {411, "Length Required"},
      {412, "Precondition Failed"},
      {413, "Payload Too Large"},
      {414, "URI Too Long"},
      {415, "Unsupported Media Type"},
      {416, "Range Not Satisfiable"},
      {417, "Expectation Failed"},
      {421, "Misdirected Request"},
      {422, "Unprocessable Entity"},
      {423, "Locked"},
      {424, "Failed Dependency"},
      {426, "Upgrade Required"},
      {428, "Precondition Required"},
      {429, "Too Many Requests"},
      {431, "Request Header Fields Too Large"},

      //< 5xx: Server Error - The server failed to fulfill an apparently valid request
      {500, "Internal Server Error"},
      {501, "Not Implemented"},
      {502, "Bad Gateway"},
      {503, "Service Unavailable"},
      {504, "Gateway Timeout"},
      {505, "HTTP Version Not Supported"},
      {506, "Variant Also Negotiates"},
      {507, "Insufficient Storage"},
      {508, "Loop Detected"},
      {510, "Not Extended"},
      {511, "Network Authentication Required"}
    }; //< status_codes

  public:
    Response(){}

    Response(Request &r){
      _req=r;
      _version=r.get_version();
      _status=200;
      _header_attributes["Server"]="PHP2Uni prototype 0.1";
      _header_attributes["Content-Type"]="text/html; charset=UTF-8";
      _header_attributes["Accept-Ranges"]="none";
      _header_attributes["Connection"]="close";
    }

    std::string get_header(){
      std::stringstream ss;
      ss << _version+" "+std::to_string(_status)+" "+status_codes[_status]+"\r\n";
      for (const auto& kv : _header_attributes) {
        ss << kv.first + ": " + kv.second + "\n\r";
      }
      ss << "Content-Length: " + std::to_string(_body.size()) +"\r\n";
      ss << "\n\r";
      return ss.str();
    }

    void compute(){
      _body+="<h1>Page not found</h1>";
      _status=404;
    }
  };
}

#endif
