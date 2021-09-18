//
// Created by loghin on 15.05.2021.
//

#include "JsonTest.h"

#include <CDS/JSON>
#include <CDS/Path>
#include <fstream>
#include <sstream>

bool JsonTest::execute() noexcept {
    bool allOk = true;
    this->logBold("Starting of test Json...");

    //    constexpr static StringLiteral in1Path = "../src/cdsIntern/tests/cpp20/collection/unordered/settings.json";
    //    constexpr static StringLiteral in2Path = "../src/cdsIntern/tests/cpp20/collection/unordered/theme.json";

    String in1 = Path(__FILE__).parent() / "settings.json";
    String in2 = Path(__FILE__).parent() / "theme.json";

    StringLiteral in1Path = in1.cStr();
    StringLiteral in2Path = in2.cStr();

    //constexpr static StringLiteral inPath = __FILE__

    this->executeSubtest("settings.json (from src file's folder) tests", [in1Path, in2Path, &allOk, this] {
        std::stringstream iss;
        iss << std::ifstream(in1Path).rdbuf();
        JSON json = JSON::parse(iss.str());

        //        std::cout << json << '\n';
        this->log("JSON as String : '%s'", json.toString().cStr());

        this->log("Value for 'theme' : '%s'", json.getString("theme").cStr());
        });

    this->executeSubtest("theme.json (from src file's folder) tests", [in1Path, in2Path, &allOk, this] {
        JSON json = JSON::load(in2Path);

        //        std::cout << json << '\n';
        this->log("JSON as String : '%s'", json.toString().cStr());

        this->log("Value for 'id' : '%s'", json.getString("id").cStr());
        this->log("Value for 'name' : '%s'", json.getString("name").cStr());
        this->log("Value for 'fallbackThemes' : '%s'", json.getArray("fallbackThemes").toString().cStr());
        this->log("Array Value Index 0 in Array 'fallbackThemes' : '%s'", json.getArray("fallbackThemes").getString(0).cStr());
        this->log("Array Iteration : ");
        for (const auto& item : json.getArray("fallbackThemes")) {
            std::cout << "\t\t\t" << item.getString() << '\n';
        }

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

        this->log("Iteration for nodes");
        for (const auto& item : json) {
            this->log("\tNode : '%s'", item.toString().cStr());
        }

        std::cout << json.dump() << '\n';
        });

    this->executeSubtest("test3", [in1Path, in2Path, &allOk, this] {
        JSON j;
        j.put("a", 1);
        j.put("b", true);
        j.put("c", 1ll);
        j.put("d", 1.0f);
        j.put("e", 1.1);
        j.put("f", "abcd");
        j.put("g", String("dcef"));

        //        std::cout << j.dump() << '\n';

        JSON::Array a;
        JSON j1;
        JSON j2;
        JSON j3;

        j1.put("a", 1);
        j2.put("b", 2);
        j3.put("c", 3);

        a.put(0, j1);
        a.put(2, j3);
        a.put(1, j2);

        a.put(3, JSON().put("b", JSON::Array().put(0, JSON().put("a", 3)).put(1, 4)).put("c", false));
        j.put("h", a);


        std::cout << j.dump(10) << '\n';
        });

    allOk ? this->logOK("Json test OK") : this->logError("String test Not OK");
    return allOk;
}