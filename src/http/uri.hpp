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
* Based on:   http://stackoverflow.com/questions/2616011/easy-way-to-parse-a-url-in-c-cross-platform
* And:        http://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
*/

#ifndef PHP2UNI_URI_HPP
#define PHP2UNI_URI_HPP

#include <string>
#include <algorithm>    // find
#include <codecvt>

namespace http {
  std::wstring s2ws(const std::string& str)
  {
      typedef std::codecvt_utf8<wchar_t> convert_typeX;
      std::wstring_convert<convert_typeX, wchar_t> converterX;

      return converterX.from_bytes(str);
  }

  std::string ws2s(const std::wstring& wstr)
  {
      typedef std::codecvt_utf8<wchar_t> convert_typeX;
      std::wstring_convert<convert_typeX, wchar_t> converterX;

      return converterX.to_bytes(wstr);
  }

  struct Uri
  {
    public:
    std::wstring QueryString, Path, Protocol, Host, Port;

    static Uri Parse(const std::wstring &uri)
    {
        Uri result;

        typedef std::wstring::const_iterator iterator_t;

        if (uri.length() == 0)
            return result;

        iterator_t uriEnd = uri.end();

        // get query start
        iterator_t queryStart = std::find(uri.begin(), uriEnd, L'?');

        // protocol
        iterator_t protocolStart = uri.begin();
        iterator_t protocolEnd = std::find(protocolStart, uriEnd, L':');            //"://");

        if (protocolEnd != uriEnd)
        {
            std::wstring prot = &*(protocolEnd);
            if ((prot.length() > 3) && (prot.substr(0, 3) == L"://"))
            {
                result.Protocol = std::wstring(protocolStart, protocolEnd);
                protocolEnd += 3;   //      ://
            }
            else
                protocolEnd = uri.begin();  // no protocol
        }
        else
            protocolEnd = uri.begin();  // no protocol

        // host
        iterator_t hostStart = protocolEnd;
        iterator_t pathStart = std::find(hostStart, uriEnd, L'/');  // get pathStart

        iterator_t hostEnd = std::find(protocolEnd,
            (pathStart != uriEnd) ? pathStart : queryStart,
            L':');  // check for port

        result.Host = std::wstring(hostStart, hostEnd);

        // port
        if ((hostEnd != uriEnd) && ((&*(hostEnd))[0] == L':'))  // we have a port
        {
            hostEnd++;
            iterator_t portEnd = (pathStart != uriEnd) ? pathStart : queryStart;
            result.Port = std::wstring(hostEnd, portEnd);
        }

        // path
        if (pathStart != uriEnd)
            result.Path = std::wstring(pathStart, queryStart);

        // query
        if (queryStart != uriEnd)
            result.QueryString = std::wstring(queryStart, uri.end());

        return result;
    }
  };
}
#endif
