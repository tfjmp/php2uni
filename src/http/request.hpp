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

#ifndef PHP2UNI_REQUEST_HPP
#define PHP2UNI_REQUEST_HPP

#include <sstream>
#include "message.hpp"

namespace http {
  class Request: public Message{
  private:
    std::string _method;
    std::string _uri;

  public:
    Request(){}

    Request(std::string &raw){
      std::string method, uri, version;
      std::stringstream ss(raw);
      /* bellow is weird, but won't work otherwise */
      ss >> method;
      _method=method;
      ss >> uri;
      _uri = uri;
      ss >> version;
      _version = version;
    }

    std::string get_header(){
      std::stringstream ss;
      ss << _method+" "+_uri+" "+_version+"\r\n";
      return ss.str();
    }

    std::string get_method(){
      return _method;
    }

    std::string get_uri(){
      return _uri;
    }
  };
}
#endif
