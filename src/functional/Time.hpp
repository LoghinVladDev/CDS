//
// Created by loghin on 20/09/2021.
//

#ifndef CDS_TIME_HPP
#define CDS_TIME_HPP

#include <CDS/Object>
#include <ctime>

class DateTime : public Object {
private:
    time_t _raw;

public:
    
};

class Duration {

};

__CDS_RegisterParseType(DateTime)
__CDS_RegisterParseType(Duration)

#endif //CDS_TIME_HPP
