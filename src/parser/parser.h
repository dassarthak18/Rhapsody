// parser.h
#pragma once
#include "json.hpp"
#include <unordered_map>
#include <string>

std::unordered_map<std::string, nlohmann::json> parse_json_file(const std::string& filename);
