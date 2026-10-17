#include <iostream>
#include <string>
#include "httplib.h"
#include "json.hpp"

int main(){
    httplib::Client ollama("http://localhost:11434");
    auto res1 = ollama.Get("/");
    if(!res1){
        std::cerr << "Error: ollama does not launched" << std::endl;
        return -1;
    }
    if(res1->status != 200) {
        std::cerr << "Error: " << res1->status << std::endl;
        return -1;
    }
    std::cout << res1->body << std::endl;
    
    std::cout << "Input ..." << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::string req1 = R"({
    "model": "gemma4:e2b",
    "prompt": ")";

    std::string req2 = R"(",
    "stream": false
    })";

    std::string reqresult = req1 + input + req2; // 連結でユーザーの入力をサンド

    std::cout << "" << reqresult << std::endl;
    auto res2 = ollama.Post("/api/generate", reqresult, "application/json");
    if(res2->status != 200) {
        std::cerr << "Error: " << res2->status << std::endl;
        return -1;
    }
    std::string js1 = res2->body;
    nlohmann::json j = nlohmann::json::parse(js1);
    std::cout << j["response"] << std::endl;
}