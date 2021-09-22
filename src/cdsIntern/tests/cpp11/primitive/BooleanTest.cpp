//
// Created by loghin on 05.04.2021.
//

#include "BooleanTest.h"
#include <CDS/Boolean>
#include <CDS/Thread>
#include <CDS/Integer>

auto BooleanTest::execute() noexcept -> bool{
    bool allOk = true;
    this->logBold("Start of test Boolean...");

    this->executeSubtest("Constructor Test", [this, &allOk]{
        {
            Boolean empty;
            this->log("Constructed empty Boolean : '%s'", empty.toString().cStr());
            if (empty) {
                this->logWarning("Empty Boolean Construction Error");
                allOk = false;
            }
        }

        {
            bool trueValue = true;
            bool falseValue = false;

            Boolean fromTrueValue(trueValue);
            Boolean fromFalseValue(falseValue);

            this->log("Constructed Boolean from literal : '%s', '%s'", (trueValue ? "true" : "false"), fromTrueValue.toString().cStr());
            this->log("Constructed Boolean from literal : '%s', '%s'", (falseValue ? "true" : "false"), fromFalseValue.toString().cStr());

            if ( ! fromTrueValue || fromFalseValue ) {
                this->logWarning("From Literal Construction Error");
                allOk = false;
            }

            Boolean copyFromTrue (fromTrueValue);
            Boolean copyFromFalse (fromFalseValue);

            this->log("Copied Boolean. From '%s', To '%s'", fromTrueValue.toString().cStr(), copyFromTrue.toString().cStr());
            this->log("Copied Boolean. From '%s', To '%s'", fromFalseValue.toString().cStr(), copyFromFalse.toString().cStr());

            if ( ! copyFromTrue || copyFromFalse ) {
                this->logWarning("Copy Constructor Error");
                allOk = false;
            }

            Boolean moved ( std::move (fromTrueValue) );

            this->log("Moved Boolean. From '%s', To '%s'", fromTrueValue.toString().cStr(), moved.toString().cStr());
            if ( !moved ) {
                this->logWarning("Move Constructor Error");
                allOk = false;
            }
        }
    });

    this->executeSubtest("Operator Tests", [&allOk, this]{
        bool trueValue = true;
        bool falseValue = false;

        Boolean objTrueValue(true);
        Boolean objFalseValue(false);

        Boolean assigned;

        assigned = objTrueValue;
        this->log("Operator = result : '%s'", assigned.toString().cStr());

        if (! assigned) {
            this->logWarning("Operator = Error");
            allOk = false;
        }

        assigned = objFalseValue;
        this->log("Operator = result : '%s'", assigned.toString().cStr());

        if (assigned) {
            this->logWarning("Operator = Error");
            allOk = false;
        }

        assigned = trueValue;
        this->log("Operator = result : '%s'", assigned.toString().cStr());
        if (! assigned) {
            this->logWarning("Operator = Error");
            allOk = false;
        }

        assigned = falseValue;
        this->log("Operator = result : '%s'", assigned.toString().cStr());
        if (assigned) {
            this->logWarning("Operator = Error");
            allOk = false;
        }

        this->log("Obj && Obj : '%s' && '%s' = '%s'", objTrueValue.toString().cStr(), objTrueValue.toString().cStr(), (objTrueValue && objTrueValue).toString().cStr());
        this->log("Obj && Obj : '%s' && '%s' = '%s'", objTrueValue.toString().cStr(), objFalseValue.toString().cStr(), (objFalseValue && objTrueValue).toString().cStr());
        this->log("Obj && Obj : '%s' && '%s' = '%s'", objFalseValue.toString().cStr(), objTrueValue.toString().cStr(), (objTrueValue && objFalseValue).toString().cStr());
        this->log("Obj && Obj : '%s' && '%s' = '%s'", objFalseValue.toString().cStr(), objFalseValue.toString().cStr(), (objFalseValue && objFalseValue).toString().cStr());

        if (
                ! ( objTrueValue && objTrueValue ) ||
                ( objTrueValue && objFalseValue ) ||
                ( objFalseValue && objTrueValue ) ||
                ( objFalseValue && objFalseValue )
        ) {
            this->logWarning("Operator && error between obj, obj");
            allOk = false;
        }

        auto boolToString = [](bool value) { return value ? "true" : "false"; };

        this->log("Obj && Trivial : '%s' && '%s' = '%s'", objTrueValue.toString().cStr(), boolToString(true), (objTrueValue && true).toString().cStr());
        this->log("Obj && Trivial : '%s' && '%s' = '%s'", objTrueValue.toString().cStr(), boolToString(false), (objTrueValue && false).toString().cStr());
        this->log("Obj && Trivial : '%s' && '%s' = '%s'", objFalseValue.toString().cStr(), boolToString(true), (objFalseValue && true).toString().cStr());
        this->log("Obj && Trivial : '%s' && '%s' = '%s'", objFalseValue.toString().cStr(), boolToString(false), (objFalseValue && false).toString().cStr());

        if (
                ! ( objTrueValue && true ) ||
                ( objTrueValue && false ) ||
                ( objFalseValue && true ) ||
                ( objFalseValue && false )
        ) {
            this->logWarning("Operator && error between obj, obj");
            allOk = false;
        }

        this->log("Trivial && Obj : '%s' && '%s' = '%s'", boolToString(true), objTrueValue.toString().cStr(), Boolean(true && objTrueValue).toString().cStr());
        this->log("Trivial && Obj : '%s' && '%s' = '%s'", boolToString(true), objFalseValue.toString().cStr(), Boolean(true && objFalseValue).toString().cStr());
        this->log("Trivial && Obj : '%s' && '%s' = '%s'", boolToString(false), objTrueValue.toString().cStr(), Boolean(false && objTrueValue).toString().cStr());
        this->log("Trivial && Obj : '%s' && '%s' = '%s'", boolToString(false), objFalseValue.toString().cStr(), Boolean(false && objFalseValue).toString().cStr());

        if (
                ! ( true && objTrueValue ) ||
                ( true && objFalseValue ) ||
                ( false && objTrueValue ) ||
                ( false && objFalseValue )
        ) {
            this->logWarning("Operator && error between obj, obj");
            allOk = false;
        }

        this->log("Obj || Obj : '%s' || '%s' = '%s'", objTrueValue.toString().cStr(), objTrueValue.toString().cStr(), (objTrueValue || objTrueValue).toString().cStr());
        this->log("Obj || Obj : '%s' || '%s' = '%s'", objTrueValue.toString().cStr(), objFalseValue.toString().cStr(), (objFalseValue || objTrueValue).toString().cStr());
        this->log("Obj || Obj : '%s' || '%s' = '%s'", objFalseValue.toString().cStr(), objTrueValue.toString().cStr(), (objTrueValue || objFalseValue).toString().cStr());
        this->log("Obj || Obj : '%s' || '%s' = '%s'", objFalseValue.toString().cStr(), objFalseValue.toString().cStr(), (objFalseValue || objFalseValue).toString().cStr());

        if (
                ! ( objTrueValue || objTrueValue ) ||
                ! ( objTrueValue || objFalseValue ) ||
                ! ( objFalseValue || objTrueValue ) ||
                ( objFalseValue || objFalseValue )
        ) {
            this->logWarning("Operator || error between obj, obj");
            allOk = false;
        }

        this->log("Obj || trivial : '%s' || '%s' = '%s'", objTrueValue.toString().cStr(), boolToString(true), (objTrueValue || true).toString().cStr());
        this->log("Obj || trivial : '%s' || '%s' = '%s'", objTrueValue.toString().cStr(), boolToString(false), (objTrueValue || false).toString().cStr());
        this->log("Obj || trivial : '%s' || '%s' = '%s'", objFalseValue.toString().cStr(), boolToString(true), (objFalseValue || true).toString().cStr());
        this->log("Obj || trivial : '%s' || '%s' = '%s'", objFalseValue.toString().cStr(), boolToString(false), (objFalseValue || false).toString().cStr());

        if (
                ! ( objTrueValue || true ) ||
                ! ( objTrueValue || false ) ||
                ! ( objFalseValue || true ) ||
                ( objFalseValue || false )
        ) {
            this->logWarning("Operator || error between obj, obj");
            allOk = false;
        }

        this->log("Trivial || Obj : '%s' || '%s' = '%s'", boolToString(true), objTrueValue.toString().cStr(), Boolean(true || objTrueValue).toString().cStr());
        this->log("Trivial || Obj : '%s' || '%s' = '%s'", boolToString(true), objFalseValue.toString().cStr(), Boolean(true || objFalseValue).toString().cStr());
        this->log("Trivial || Obj : '%s' || '%s' = '%s'", boolToString(false), objTrueValue.toString().cStr(), Boolean(false || objTrueValue).toString().cStr());
        this->log("Trivial || Obj : '%s' || '%s' = '%s'", boolToString(false), objFalseValue.toString().cStr(), Boolean(false || objFalseValue).toString().cStr());

        if (
                ! ( true || objTrueValue ) ||
                ! ( true || objFalseValue ) ||
                ! ( false || objTrueValue ) ||
                ( false || objFalseValue )
        ) {
            this->logWarning("Operator || error between obj, obj");
            allOk = false;
        }

        this->log("! '%s' = '%s'", objTrueValue.toString().cStr(), (! objTrueValue).toString().cStr());
        this->log("! '%s' = '%s'", objFalseValue.toString().cStr(), (! objFalseValue).toString().cStr());

        if ( ! objTrueValue || ! ( ! objFalseValue ) ) {
            this->logWarning("Operator ! error");
            allOk = false;
        }

        this->log("Obj == Obj : '%s' == '%s' -> '%s'", objTrueValue.toString().cStr(), objTrueValue.toString().cStr(), boolToString(objTrueValue == objTrueValue));
        this->log("Obj == Obj : '%s' == '%s' -> '%s'", objTrueValue.toString().cStr(), objFalseValue.toString().cStr(), boolToString(objTrueValue == objFalseValue));
        this->log("Obj == Obj : '%s' == '%s' -> '%s'", objFalseValue.toString().cStr(), objTrueValue.toString().cStr(), boolToString(objFalseValue == objTrueValue));
        this->log("Obj == Obj : '%s' == '%s' -> '%s'", objFalseValue.toString().cStr(), objFalseValue.toString().cStr(), boolToString(objFalseValue == objFalseValue));

        if (
            ! ( objTrueValue == objTrueValue ) ||
            ( objTrueValue == objFalseValue ) ||
            ( objFalseValue == objTrueValue ) ||
            ! ( objFalseValue == objFalseValue )
        ) {
            this->logWarning("Operator == error");
            allOk = false;
        }

        this->log("Trivial == Obj : '%s' == '%s' -> '%s'", boolToString(true), objTrueValue.toString().cStr(), boolToString(true == objTrueValue));
        this->log("Trivial == Obj : '%s' == '%s' -> '%s'", boolToString(true), objFalseValue.toString().cStr(), boolToString(true == objFalseValue));
        this->log("Trivial == Obj : '%s' == '%s' -> '%s'", boolToString(false), objTrueValue.toString().cStr(), boolToString(false == objTrueValue));
        this->log("Trivial == Obj : '%s' == '%s' -> '%s'", boolToString(false), objFalseValue.toString().cStr(), boolToString(false == objFalseValue));

        if (
            ! (true == objTrueValue ) ||
            (true == objFalseValue ) ||
            (false == objTrueValue ) ||
            ! (false == objFalseValue )
        ) {
            this->logWarning("Operator == error");
            allOk = false;
        }

        this->log("Obj == Trivial : '%s' == '%s' -> '%s'", objTrueValue.toString().cStr(), boolToString(true), boolToString(objTrueValue == true));
        this->log("Obj == Trivial : '%s' == '%s' -> '%s'", objTrueValue.toString().cStr(), boolToString(false), boolToString(objTrueValue == false));
        this->log("Obj == Trivial : '%s' == '%s' -> '%s'", objFalseValue.toString().cStr(), boolToString(true), boolToString(objFalseValue == true));
        this->log("Obj == Trivial : '%s' == '%s' -> '%s'", objFalseValue.toString().cStr(), boolToString(false), boolToString(objFalseValue == false));

        if (
            ! ( objTrueValue == true ) ||
            ( objTrueValue == false ) ||
            ( objFalseValue == true ) ||
            ! ( objFalseValue == false )
        ) {
            this->logWarning("Operator == error");
            allOk = false;
        }


        this->log("Obj != Obj : '%s' != '%s' -> '%s'", objTrueValue.toString().cStr(), objTrueValue.toString().cStr(), boolToString(objTrueValue != objTrueValue));
        this->log("Obj != Obj : '%s' != '%s' -> '%s'", objTrueValue.toString().cStr(), objFalseValue.toString().cStr(), boolToString(objTrueValue != objFalseValue));
        this->log("Obj != Obj : '%s' != '%s' -> '%s'", objFalseValue.toString().cStr(), objTrueValue.toString().cStr(), boolToString(objFalseValue != objTrueValue));
        this->log("Obj != Obj : '%s' != '%s' -> '%s'", objFalseValue.toString().cStr(), objFalseValue.toString().cStr(), boolToString(objFalseValue != objFalseValue));

        if (
            ( objTrueValue != objTrueValue ) ||
            ! ( objTrueValue != objFalseValue ) ||
            ! ( objFalseValue != objTrueValue ) ||
            ( objFalseValue != objFalseValue )
        ) {
            this->logWarning("Operator != error");
            allOk = false;
        }

        this->log("Trivial != Obj : '%s' != '%s' -> '%s'", boolToString(true), objTrueValue.toString().cStr(), boolToString(true != objTrueValue));
        this->log("Trivial != Obj : '%s' != '%s' -> '%s'", boolToString(true), objFalseValue.toString().cStr(), boolToString(true != objFalseValue));
        this->log("Trivial != Obj : '%s' != '%s' -> '%s'", boolToString(false), objTrueValue.toString().cStr(), boolToString(false != objTrueValue));
        this->log("Trivial != Obj : '%s' != '%s' -> '%s'", boolToString(false), objFalseValue.toString().cStr(), boolToString(false != objFalseValue));

        if (
            (true != objTrueValue ) ||
            ! (true != objFalseValue ) ||
            ! (false != objTrueValue ) ||
            (false != objFalseValue )
        ) {
            this->logWarning("Operator != error");
            allOk = false;
        }

        this->log("Obj != Trivial : '%s' != '%s' -> '%s'", objTrueValue.toString().cStr(), boolToString(true), boolToString(objTrueValue != true));
        this->log("Obj != Trivial : '%s' != '%s' -> '%s'", objTrueValue.toString().cStr(), boolToString(false), boolToString(objTrueValue != false));
        this->log("Obj != Trivial : '%s' != '%s' -> '%s'", objFalseValue.toString().cStr(), boolToString(true), boolToString(objFalseValue != true));
        this->log("Obj != Trivial : '%s' != '%s' -> '%s'", objFalseValue.toString().cStr(), boolToString(false), boolToString(objFalseValue != false));

        if (
            ( objTrueValue != true ) ||
            ! ( objTrueValue != false ) ||
            ! ( objFalseValue != true ) ||
            ( objFalseValue != false )
        ) {
            this->logWarning("Operator != error");
            allOk = false;
        }

        this->log("obj.equals(obj) : '%s'.equals('%s') = '%s'", objTrueValue.toString().cStr(), objTrueValue.toString().cStr(), boolToString(objTrueValue.equals(objTrueValue)));
        this->log("obj.equals(obj) : '%s'.equals('%s') = '%s'", objTrueValue.toString().cStr(), objFalseValue.toString().cStr(), boolToString(objTrueValue.equals(objFalseValue)));
        this->log("obj.equals(obj) : '%s'.equals('%s') = '%s'", objFalseValue.toString().cStr(), objTrueValue.toString().cStr(), boolToString(objFalseValue.equals(objTrueValue)));
        this->log("obj.equals(obj) : '%s'.equals('%s') = '%s'", objFalseValue.toString().cStr(), objFalseValue.toString().cStr(), boolToString(objFalseValue.equals(objFalseValue)));

        if (
            ! objTrueValue.equals(objTrueValue) ||
            objTrueValue.equals(objFalseValue) ||
            objFalseValue.equals(objTrueValue) ||
            ! objFalseValue.equals(objFalseValue)
        ) {
            this->logWarning("equals Error");
            allOk = false;
        }

        String otherObj = "true";

        this->log("obj.equals(obj) : '%s'.equals('%s') = '%s'", objTrueValue.toString().cStr(), otherObj.cStr(), boolToString(objTrueValue.equals(otherObj)));
        this->log("obj.equals(obj) : '%s'.equals('%s') = '%s'", objFalseValue.toString().cStr(), otherObj.cStr(), boolToString(objFalseValue.equals(otherObj)));
        this->log("obj.equals(obj) : '%s'.equals('%s') = '%s'", otherObj.cStr(), objTrueValue.toString().cStr(), boolToString(otherObj.equals(objTrueValue)));
        this->log("obj.equals(obj) : '%s'.equals('%s') = '%s'", otherObj.cStr(), objFalseValue.toString().cStr(), boolToString(otherObj.equals(objFalseValue)));

        if (
            objTrueValue.equals(otherObj) ||
            objFalseValue.equals(otherObj) ||
            otherObj.equals(objTrueValue) ||
            otherObj.equals(objFalseValue)
        ) {
            this->logWarning("equals Error");
            allOk = false;
        }

        this->log("from string : '%s'", Boolean::parse("True").toString().cStr());
        this->log("from string : '%s'", Boolean::parse("true").toString().cStr());
        this->log("from string : '%s'", Boolean::parse("False").toString().cStr());
        this->log("from string : '%s'", Boolean::parse("false").toString().cStr());

        if (Boolean::parse("True") || Boolean::parse("False") || Boolean::parse("false") || !Boolean::parse("true")) {
            this->logWarning("parse error");
            allOk = false;
        }
    });

    this->executeSubtest("Boolean::Atomic Tests", [& allOk, this] {
        Boolean::Atomic empty;
        Integer::Atomic counter = 1;

        this->log("Nothing to test, only testing non-blocking of atomics");

        Boolean::Atomic v1 = true;
        Boolean::Atomic v2 = false;

        auto thFunction = [& empty, & counter, &v1, &v2, this, &allOk] {
            int threadIndex = counter++;

            for (Index i = 0; i < 10000; i ++ ) {
                v1 = !v1;
                v2 = v1;
                v2 = !v2;
                v2 = !v1;
                v1 = v2;
            }

            for (Index i = 0; i < 10000; i ++ ) {
                v1 = v1 && v2;
                v2 = v1 || v2 && v1;
                v1 = v1 || v2;
                v2 = v1 && v2 || !v1;
                v2 = v1;
                v2 = ! v1;
            }

            if (v1 == v2) {
                this->log("Thread %d, Variation to ==", threadIndex);
            } else if (v1 != v2) {
                this->log("Thread %d, Variation to !=", threadIndex);
            } else {
                this->logWarning("Thread %d, Variation inside == or != function caused malfunctioned if elseif branch", threadIndex);
            }

            this->log("Thread %d, Version of bool : '%s'; '%s'", threadIndex, v1.toString().cStr(), v2.toString().cStr());
        };

        Array < Runnable <decltype(thFunction)> * > threads = {
                new Runnable <decltype(thFunction)> (thFunction),
                new Runnable <decltype(thFunction)> (thFunction),
                new Runnable <decltype(thFunction)> (thFunction),
                new Runnable <decltype(thFunction)> (thFunction),
                new Runnable <decltype(thFunction)> (thFunction)
        };

        threads.forEach([](Runnable < decltype(thFunction) > * e){e->start();});
        threads.forEach([](Runnable < decltype(thFunction) > * e){e->join();});
        threads.forEach([](Runnable < decltype(thFunction) > * e){delete e;});
    });

    return allOk;
}
