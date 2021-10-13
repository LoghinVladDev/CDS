//
// Created by loghin on 11.10.2021.
//

#ifndef CDS_REQUEST_HPP
#define CDS_REQUEST_HPP

#include <CDS/Object>
#include <CDS/Socket>
#include <CDS/Pointer>

#include <functional>

class Request : public Object {
private:

    Socket socket {};

    String _outParams;

public:


};

__CDS_RegisterParseType(Request)

#endif //CDS_REQUEST_HPP
