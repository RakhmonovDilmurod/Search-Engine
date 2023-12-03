# Search Engine cpp

Welcome to the Search Engine cpp project! This is a lightweight, command-line-based search engine that provides an effective and efficient way to search through a large dataset of documents.

## Prerequisites
To build and run this project, you need to have the following software installed on your system:
 
 - A C++ compiler that supports C++17 or later, such as g++, clang++, or Microsoft Visual C++
 - CMake (version 3.1 or later)

## Building and Running the Project
To build the project, follow these steps:
1. Open a terminal/command prompt and navigate to the project's root directory
2. Create a build directory
3. Run CMake to generate the build files:
   Cmake..
4. Unzip nlohmann_json file and add to project
5. Build the project using your preferred build tool.
6. After the build is complete, you can run the search engine.

## Using the Search Engine
To use the search engine, you need to have a dataset of documents. The search engine supports the following files format: config.json , requests.json , answers.json
The search engine provides a simple command-line interface for searching documents. Type the search query and press Enter to receive the search results.

1. Configuration file config.json.
Without it, the application cannot be launched. It contains the name of the search engine,
its version, database update time (how often should it be done
re-indexing the database, re-uploading files and calculating their search engine
rating), maximum number of options in the answer (if not specified, then the value
is chosen to be five).
An example of a config.json file description:
{
          "config": {
                      "name": "SkillboxSearchEngine",
                      "version": "0.1",
                      "max_responses": 5
                      },
          "files": [
                     "../resources/file001.txt",
                     "../resources/file002.txt",
                     "../resources/file003.txt",
                     "../resources/file004.txt"

   ]
}

3. File with requests requests.json.
It contains queries that need to be processed by the search engine.
An example of a requests.json file description:
  {
    "requests": [
              "some words..",
              "some words..",
              "some words..",
              "some words..".
              ]
                
  }

4. File with answers to requests answers.json.
The results of the search engine are recorded in it. If at start
application, this file does not exist in the directory with the project, then it is necessary
create. If the file already exists, then you need to erase all its contents.
An example of a config.json file description:
{
 "answers": {
"request001": {"result": "true","relevance": {"docid": 0, “rank” : 0.989,"docid": 1, “rank” : 0.897,"docid": 2, “rank” : 0.750,"docid": 3, “rank” : 0.670,"docid": 4, “rank” : 0.561}},
"request002": {"result": "true","docid": 0, “rank” : 0.769},
"request003": {"result": "false"}
 }
}
