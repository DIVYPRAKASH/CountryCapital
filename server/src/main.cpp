#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/client.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
using namespace Pistache;
/*

    
"capitals" : [
    {
        "country" : "string",
        "city" : "string"
    }

*/
std::unordered_map<std::string, std::string> countryCapitalsStore;

class RequestHandler : public Pistache::Http::Handler
{

public:
  HTTP_PROTOTYPE(RequestHandler)

  void onRequest(const Http::Request& request, Http::ResponseWriter response) override
  {
    if(request.resource() == "/set")
    {
        auto data = nlohmann::json::parse(request.body());

        for(const auto& capitalsJson : data.at("capitals"))
        {
            std::string country = capitalsJson.at("country");
            std::string capital = capitalsJson.at("capital");
            countryCapitalsStore.emplace(country,capital);
        }
        response.send(Http::Code::Ok,"OK");
    }
    else if(request.resource() == "/get")
    {
        auto data = nlohmann::json::parse(request.body());
        auto const country = data.at("country");
        auto capital = countryCapitalsStore.find(country);
        if(capital != countryCapitalsStore.end())
        {
            response.send(Http::Code::Ok, capital->second);
        }
        else
        {
            response.send(Http::Code::Ok, "not found");
        }

    }
  }
};


int main()
{
    Http::listenAndServe<RequestHandler>(Pistache::Address("*:9080"));
}