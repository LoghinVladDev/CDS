/*
 * Created by loghin on 15.05.2021.
 */

#include "JsonTest.h"

#include <sstream>
#include <fstream>
#include <CDS/util/JSON>
#include <CDS/filesystem/Path>

using namespace cds;

bool JsonTest::execute() noexcept {
    using namespace filesystem;
    bool allOk = true;
    this->logBold("Starting of test Json...");

    String in1 = Path(__FILE__).parent() / "settings.json";
    String in2 = Path(__FILE__).parent() / "theme.json";

    StringLiteral in1Path = in1.cStr();
    StringLiteral in2Path = in2.cStr();


    this->executeSubtest("settings.json (from src file's folder) tests", [in1Path, in2Path, &allOk, this]{
        std::stringstream iss;
        iss << std::ifstream(in1Path).rdbuf();
        auto json = json :: parseJson (iss.str());
        this->log("JSON as String : '%s'", json.toString().cStr());

        this->log("Value for 'theme' : '%s'", json.getString("theme").cStr());
    });

    this->executeSubtest("theme.json (from src file's folder) tests", [in1Path, in2Path, &allOk, this]{
        auto json = json :: loadJson ( in2Path );

        this->log("JSON as String : '%s'", json.toString().cStr());

        this->log("Value for 'id' : '%s'", json.getString("id").cStr());
        this->log("Value for 'name' : '%s'", json.getString("name").cStr());
        this->log("Value for 'fallbackThemes' : '%s'", json.getArray("fallbackThemes").toString().cStr());
        this->log("Array Value Index 0 in Array 'fallbackThemes' : '%s'", json.getArray("fallbackThemes").getString(0).cStr());
        this->log("Array Iteration : ");
        for (const auto &item : json.getArray("fallbackThemes")) {
            std::cout << "\t\t\t" << item.getString() << '\n';
        }

        this->log("Value for 'mappings' : '%s'", json.getJson("mappings").toString().cStr());
        this->log("Value for 'mappings.menu-bar' : '%s'", json.getJson("mappings").getString("menu-bar").cStr());

        this->log("Value for 'mappings.button' : '%s'", json.getJson("mappings").getString("button").cStr());
        this->log("Value for 'mappings.combo' : '%s'", json.getJson("mappings").getString("combo").cStr());


        this->log("Value for 'mappings.splitter' : '%s'", json.getJson("mappings").getString("splitter").cStr());
        this->log("Value for 'mappings.splitter-left' : '%s'", json.getJson("mappings").getString("splitter-left").cStr());

        this->log("Value for 'mappings.list' : '%s'", json.getJson("mappings").getString("list").cStr());

        this->log("Value for 'mappings.widget' : '%s'", json.getJson("mappings").getString("widget").cStr());
        this->log("Value for 'mappings.lower-widget' : '%s'", json.getJson("mappings").getString("lower-widget").cStr());


        this->log("Value for 'icons' : '%s'", json.getJson("icons").toString().cStr());

        this->log("Value for 'icons.window-close' : '%s'", json.getJson("icons").getString("window-close").cStr());

        this->log("Keys for json : '%s'", json.keys().toString().cStr());
        this->log("Iteration for nodes");
        for (const auto &item : json) {
            this->log("\tNode : '%s'", item.toString().cStr());
        }

        std::cout << json :: dump ( json ) << '\n';
    });

    this->executeSubtest("test3", [in1Path, in2Path, &allOk, this]{

        json :: JsonObject j;
        j.put("a", 1);
        j.put("b", true);
        j.put("c", 1ll);
        j.put("d", 1.0f);
        j.put("e", 1.1);
        j.put("f", "abcd");
        j.put("g", String("dcef"));

        json ::  JsonArray a;
        json ::  JsonObject j1;
        json ::  JsonObject j2;
        json ::  JsonObject j3;

        j1.put("a", 1);
        j2.put("b", 2);
        j3.put("c", 3);

        a.pushBack(j1);
        a.pushBack(j3);
        a.pushBack(j2);

        a.pushBack( json ::  JsonObject().put("b", json ::  JsonArray().pushBack(json ::  JsonObject().put("a", 3)).pushBack(4)).put("c", false));
        j.put("h", a);

        std :: cout << json::dump ( j, 10 ) << '\n';
    });

    allOk ? this->logOK("Json test OK") : this->logError("String test Not OK");
    return allOk;
}
