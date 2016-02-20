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

#define _s__GET _req._get
#define _s__SERVER _server

#include <ctime>
#include "date_constants.hpp"
#include "response.hpp"

namespace http {

  typedef char* cstr_t;

  class ResponsePHP: public Response{
  protected:
    std::map<std::string, std::string> _server;

  public:
    ResponsePHP(Request &r) : Response(r){
      _server["SERVER_SOFTWARE"]=_header_attributes["Server"];
      _server["SERVER_PROTOCOL"]=r.get_method();
      _server["REQUEST_METHOD"]=r.get_version();
      _server["REQUEST_TIME"]=std::to_string(time());
      _server["DOCUMENT_ROOT"]="/";
      _server["QUERY_STRING"]=r.get_query();
      _server["REQUEST_URI"]=r.get_uri();
      _server["PATH_INFO"]=r.get_path();
      std::map<std::string, std::string> req_header = r.get_header_map();
      _server["HTTP_ACCEPT"]=req_header["Accept"];
      _server["HTTP_ACCEPT_LANGUAGE"]=req_header["Accept-Language"];
      _server["HTTP_CONNECTION"]=req_header["Connection"];
      _server["HTTP_HOST"]=req_header["Host"];
      _server["HTTP_USER_AGENT"]=req_header["User-Agent"];
    }

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

    std::string date(std::string format, int date=-1){
      /* TODO deal with the formatting */
      std::stringstream ss;
      std::time_t now;
      if(date!=-1){
        now = (std::time_t)date;
      }else{
        now = std::time(0);
      }

      std::tm *ltm = localtime(&now);
      if(format==W3C){
        ss << 1900 + ltm->tm_year << "-" <<  1 + ltm->tm_mon << "-" << ltm->tm_mday;
        ss << " " << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec;
        ss << "+00:00";
      }else{ // default to W3C
        ss << 1900 + ltm->tm_year << "-" <<  1 + ltm->tm_mon << "-" << ltm->tm_mday;
        ss << " " << (1 + ltm->tm_hour)%24 << ":" << (1 + ltm->tm_min)%60 << ":" << (1 + ltm->tm_sec)%60;
        ss << "+00:00";
      }
      return ss.str();
    }


    int mktime(int hour=0, int min=0, int second=0, int month=0, int day=0, int year=0){
      std::time_t rawtime;
      std::tm *timeinfo;

      std::time(&rawtime);
      timeinfo = localtime ( &rawtime );
      timeinfo->tm_year = year - 1900;
      timeinfo->tm_mon = month - 1;
      timeinfo->tm_mday = day;
      timeinfo->tm_hour = hour-1;
      timeinfo->tm_min = min-1;
      timeinfo->tm_sec = second-1;
      rawtime = std::mktime(timeinfo);

      return (int)rawtime;
    }

    int time(){
      std::time_t rawtime;
      std::time(&rawtime);
      return (int)rawtime;
    }
  };
}

#endif
