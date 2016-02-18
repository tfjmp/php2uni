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

#ifndef PHP2UNI_MESSAGE_HPP
#define PHP2UNI_MESSAGE_HPP

#include <map>

namespace http {
  class Message {
  protected:
    std::map<std::string, std::string> _header_attributes;
    std::string _version;
    std::string _body;

  public:
    Message(){
    }

    std::string get_header();

    std::string get_body(){
      return _body;
    }

    std::string get_version(){
      return _version;
    }
  };
}

#endif
