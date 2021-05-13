#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/client.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

#include <csignal>
using namespace Pistache;
/*
"capitals" : [
    {
        "country" : "string",
        "city" : "string"
    }

*/
std::unordered_map<std::string, std::string> countryCapitalsStore;
static bool quit{false};
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

static void interruptHandler(int nSig)
{
    quit = true;
}

int main()
{
    signal(SIGINT, interruptHandler);
    signal(SIGTERM, interruptHandler);
    signal(SIGUSR2, interruptHandler);
    signal(SIGKILL, interruptHandler);
    std::cout<< "\n Starting REST interface. Listening on port 9080 \n";

    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    Pistache::Http::Endpoint server(addr);
    auto opts = Http::Endpoint::options().threads(1).flags(Pistache::Tcp::Options::ReuseAddr);
    server.init(opts);
    server.setHandler(Http::make_handler<RequestHandler>());
    server.serveThreaded();
    while(!quit);

    std::cout<< "Shutdown";
    server.shutdown();
    return 0;
}