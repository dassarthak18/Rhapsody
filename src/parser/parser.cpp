// parser.cpp
#include "parser.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

std::unordered_map<std::string, json> parse_json_file(const std::string& filename) {
    std::unordered_map<std::string, json> result;

    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Failed to open " << filename << "\n";
        return result;
    }

    json data = json::parse(in);

    // Populate known fields
    if (data.contains("environment")) result["environment"] = data["environment"];
    if (data.contains("agents"))      result["agents"] = data["agents"];
    if (data.contains("instances"))   result["instances"] = data["instances"];
    if (data.contains("init"))        result["init"] = data["init"];
    if (data.contains("transitions")) result["transitions"] = data["transitions"];
    if (data.contains("verify"))      result["verify"] = data["verify"];
    if (data.contains("assert"))      result["assert"] = data["assert"];

    return result;
}
