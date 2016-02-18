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

#ifndef PHP2UNI_RESPONSE_FACTORY_HPP
#define PHP2UNI_RESPONSE_FACTORY_HPP

#include "message.hpp"
#include "request.hpp"
/* routes:include */

namespace http {
  class ResponseFactory{
  public:
    Response create(Request& r){
      Response rtn(r);
/* routes:switch */
      rtn.compute();
      return rtn;
    }
  };
}
#endif
