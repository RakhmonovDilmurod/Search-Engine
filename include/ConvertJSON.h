#ifndef CONVERTJSON_H
#define CONVERTJSON_H

#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <cstdlib>

using json = nlohmann::json;

class OpeningError : public std::exception {
private:
    std::string message;

public:
    OpeningError(const std::string  fileName)
        : message("Failed to open file: " + fileName + ".") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class JsonFileContainingError : public std::exception {
private:
    std::string message;

public:
    JsonFileContainingError(const std::string fileName, const std::string& containerName)
        : message("Failed to find container " + containerName + " in file " + fileName + ".") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};
#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#include <limits.h>
#endif
std::string GetExecutablePath() {
#if defined(_WIN32)
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return buffer;
#elif defined(__linux__) || defined(__APPLE__)
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        return buffer;
    }
#endif
    return "";
}
std::string GetExecutableDirectory() {
    std::string executablePath = GetExecutablePath();
    size_t lastSeparator = executablePath.find_last_of("/\\");
    return (lastSeparator != std::string::npos) ? executablePath.substr(0, lastSeparator) : "";
}

 std::string executableDir = GetExecutableDirectory();
class ConverterJSON {
private:

    const std::string configJsonPath   = GetExecutableDirectory() + "\\search_engine\\config.json";
    const std::string requestsJsonPath = GetExecutableDirectory() + "\\search_engine\\requests.json";
    const std::string answersJsonPath  = GetExecutableDirectory() + "\\search_engine\\answers.json";
    json answersJsonFile;
    json requestsJsonFile;

public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments() {
        std::vector<std::string> documents;
        std::ifstream configFile(configJsonPath,std::ios::in);

        if (!configFile.is_open()) {
            throw OpeningError(configJsonPath);
        }

        json config;
        configFile >> config;

        if (config.empty()) {
            throw OpeningError(requestsJsonPath);
        }

        for (const auto& doc : config["files"]) {
            documents.push_back(doc.get<std::string>());
        }

        return documents;
    }

    int GetResponsesLimit() {
        std::ifstream configFile(configJsonPath);
        json config;
        configFile >> config;

        return config.contains("max_responses") ? config["max_responses"].get<int>() : 0; // Default value or throw an exception.
    }

    std::vector<std::string> GetRequests() {
        std::ifstream ifSJsonFile(requestsJsonPath);
        ifSJsonFile >> requestsJsonFile;
        std::vector<std::string> requests = {};

        if (requestsJsonFile.contains("requests")) {
            for (const auto& i : requestsJsonFile["requests"]) {
                requests.push_back(i.get<std::string>());
            }

        return requests;
    }
        else{
            throw JsonFileContainingError(requestsJsonPath, "requests");
        }
    }

    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
        for (int i = 0; i < answers.size(); i++) {
            std::string strI = "";
            for (int n = 0; n < 3 - std::to_string(i).length(); n++) {
                strI += "0";
            }
            strI += std::to_string(i + 1);

            if (!answers[i].empty()) {
                answersJsonFile["answers"]["request" + strI]["result"] = "true";
                for (int j = 0; j < answers[i].size(); j++) {
                    json::value_type block;
                    block["docid"] = answers[i][j].first;
                    block["rank"] = answers[i][j].second;
                    answersJsonFile["answers"]["request" + strI]["relevance"].push_back(block);
                }
            }
            std::ofstream ofstreamJsonFile(answersJsonPath);
            ofstreamJsonFile << answersJsonFile;
            ofstreamJsonFile.close();
        }
    }
};

#endif // CONVERTJSON_H
