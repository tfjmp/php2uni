#include <iostream>
#include "request.hpp"
#include "response.hpp"
#include "response_factory.hpp"

using namespace std;
using namespace http;

int main(){
  cout << "Test starting..." << endl;
  Request req("GET /hello.htm HTTP/1.1");
  cout << req.get_header() << endl;
  ResponseFactory rf;
  Response res = rf.create(req);
  cout << res.get_header() << endl;
  cout << res.get_body() << endl;
  return 0;
}
