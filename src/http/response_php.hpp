/*
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

#ifndef PHP2UNI_RESPONSE_PHP_HPP
#define PHP2UNI_RESPONSE_PHP_HPP

#include "response.hpp"

namespace http {
  class ResponsePHP: public Response{

  public:
    ResponsePHP(Request &r) : Response(r){}

    void echo(std::string str){
      _body+=str;
    }

    void echo(int v){
      _body+=std::to_string(v);
    }

    void echo(double v){
      _body+=std::to_string(v);
    }

    void showhtml(std::string str){
      _body+=str;
    }

    int http_response_code(){
      return _status;
    }

    int http_response_code(int status){
      _status=status;
      return _status;
    }
  };
}

#endif
