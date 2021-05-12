
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <cpr/cpr.h>


#include <boost/program_options.hpp>

namespace po = boost::program_options;


/*

    
"capitals" : [
    {
        "country" : "string",
        "city" : "string"
    }

*/



int main(int argc, char* argv[])
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Produce help message")
        ("node,n",po::value<std::string>(), "Specify source interface address.")
        ("method,m",po::value<std::string>()->default_value("GET"), "Specify method GET or SET")
        ("country,cou",po::value<std::string>()->default_value(""),"Specify a country name")
        ("capital,cap",po::value<std::string>()->default_value(""),"Specify the capital of country");
    
    boost::program_options::variables_map vm;
    boost::program_options::store(
    boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help"))
    {
      std::cout << desc << "\n";
      return 0;
    }

    std::string addr;
    std::string method;
    std::string country;
    std::string capital;
    if (!vm.count("node"))
    {
      std::cout << "the option '--node' is required but missing"
                << "\n";
      return 0;
    }
    else
    {
        addr = vm["node"].as<std::string>();
    }

    if (vm.count("method"))
    {
        method  = vm["method"].as<std::string>();
    }

    if (vm.count("country"))
    {
        country  = vm["country"].as<std::string>();
    }

    if (vm.count("capital"))
    {
        capital  = vm["capital"].as<std::string>();
    }


    if( method == "GET")
    {
        nlohmann::json countryJson;
        countryJson["country"] = country;
        auto const response = cpr::Get(cpr::Url{"http://" + addr + "/get"},cpr::Body{countryJson.dump()});
        std::cout << "\n STATUS_CODE : " << response.status_code << std::endl;
        std::cout << "\n CAPITAL: " << response.text << std::endl; 
        return 0;
    }
    else if (method == "SET")
    {
        nlohmann::json countryAndCapitalsJson = nlohmann::json::array();
        nlohmann::json j;
        j["country"] = country;
        j["capital"] = capital;
        countryAndCapitalsJson.push_back(j);

        nlohmann::json capitalsJson;
        capitalsJson["capitals"] = countryAndCapitalsJson;
        auto const response = cpr::Put(cpr::Url{"http://" + addr + "/set"},cpr::Body{capitalsJson.dump()});
        std::cout << "\n STATUS_CODE : " << response.status_code << " STATUS_TEXT : " << response.text << std::endl;
        return 0;
    }
    std::cout << "Operation not supported" << std::endl;
    return -1;
}