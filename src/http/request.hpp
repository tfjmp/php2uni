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
#include <string>
#include <algorithm>    // find
#include "message.hpp"
#include "uri.hpp"

namespace http {
  class Request: public Message{
  private:
    std::string _method;
    std::string _path;
    std::string _uri;

  public:
    std::map<std::string, std::string> _get;
    Request(){}

    Request(std::string &raw){
      std::string method, uri, version;
      std::stringstream ss(raw);
      /* bellow is weird, but won't work otherwise */
      ss >> method;
      _method=method;
      ss >> uri;
      _uri = uri;
      Uri u = Uri::Parse(s2ws(uri));
      _path = ws2s(u.Path);
      if(u.QueryString.size()>0){
        parse_query(u.QueryString);
      }
      ss >> version;
      _version = version;
    }

    void parse_query(const std::wstring& query){
      typedef std::wstring::const_iterator iterator_t;

      iterator_t begin = query.begin();
      begin++;
      iterator_t end = query.end();
      iterator_t param_end;
      do{
        std::wstring key, value;
        param_end = std::find(begin, end, L'&');
        iterator_t equal = std::find(begin, param_end, L'=');
        key = std::wstring(begin, equal);
        equal++;
        value = std::wstring(equal, param_end);
        _get.insert( std::pair<std::string,std::string>(ws2s(key),ws2s(value)) );
        begin = param_end;
        begin++;
      }while(param_end<end);
    }

    std::string get_header(){
      std::stringstream ss;
      ss << _method+" "+_uri+" "+_version+"\r\n";
      return ss.str();
    }

    std::string get_method(){
      return _method;
    }

    std::string get_path(){
      return _path;
    }
  };
}
#endif
