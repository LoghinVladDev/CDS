//
// Created by loghin on 15.05.2021.
//

#include "JsonTest.h"

#include <CDS/JSON>
#include <fstream>
#include <sstream>

bool JsonTest::execute() noexcept {
    bool allOk = true;
    this->logBold("Starting of test Json...");

    constexpr static StringLiteral in1Path = "../src/cdsIntern/tests/collection/unordered/settings.json";
    constexpr static StringLiteral in2Path = "../src/cdsIntern/tests/collection/unordered/theme.json";

    this->executeSubtest("settings.json (from src file's folder) tests", [&allOk, this]{
        std::stringstream iss;
        iss << std::ifstream(in1Path).rdbuf();
        JSON json = JSON::parse(iss.str());

//        std::cout << json << '\n';
        this->log("JSON as String : '%s'", json.toString().cStr());

        this->log("Value for 'theme' : '%s'", json.getString("theme").cStr());
    });

    this->executeSubtest("theme.json (from src file's folder) tests", [&allOk, this]{
        JSON json = JSON::load(in2Path);

//        std::cout << json << '\n';
        this->log("JSON as String : '%s'", json.toString().cStr());

        this->log("Value for 'id' : '%s'", json.getString("id").cStr());
        this->log("Value for 'name' : '%s'", json.getString("name").cStr());
        this->log("Value for 'fallbackThemes' : '%s'", json.getArray("fallbackThemes").toString().cStr());
        this->log("Array Value Index 0 in Array 'fallbackThemes' : '%s'", json.getArray("fallbackThemes").getString(0).cStr());

        this->log("Value for 'mappings' : '%s'", json.getJSON("mappings").toString().cStr());

        this->log("Value for 'mappings.menu-bar' : '%s'", json.getJSON("mappings").getString("menu-bar").cStr());

        this->log("Value for 'mappings.button' : '%s'", json.getJSON("mappings").getString("button").cStr());
        this->log("Value for 'mappings.combo' : '%s'", json.getJSON("mappings").getString("combo").cStr());

        this->log("Value for 'mappings.splitter' : '%s'", json.getJSON("mappings").getString("splitter").cStr());
        this->log("Value for 'mappings.splitter-left' : '%s'", json.getJSON("mappings").getString("splitter-left").cStr());

        this->log("Value for 'mappings.list' : '%s'", json.getJSON("mappings").getString("list").cStr());

        this->log("Value for 'mappings.widget' : '%s'", json.getJSON("mappings").getString("widget").cStr());
        this->log("Value for 'mappings.lower-widget' : '%s'", json.getJSON("mappings").getString("lower-widget").cStr());


        this->log("Value for 'icons' : '%s'", json.getJSON("icons").toString().cStr());

        this->log("Value for 'icons.window-close' : '%s'", json.getJSON("icons").getString("window-close").cStr());

        this->log("Keys for json : '%s'", json.labels().toString().cStr());
    });

    allOk ? this->logOK("Json test OK") : this->logError("String test Not OK");
    return allOk;
}