
/*
Copyright (c) 2014, University of Maryland
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef XCDF_FIELD_DESCRIPTOR_INCLUDED_H
#define XCDF_FIELD_DESCRIPTOR_INCLUDED_H

#include <string>
#include <stdint.h>

class XCDFFieldDescriptor {

  public:

    XCDFFieldDescriptor() : name_ (""),
                            type_('\xff'),
                            rawResolution_(0),
                            parentName_("") { }

    ~XCDFFieldDescriptor() { }

    std::string name_;
    char type_;
    uint64_t rawResolution_;
    std::string parentName_;

    bool operator==(const XCDFFieldDescriptor& fd) const {
      return name_ == fd.name_ &&
             type_ == fd.type_ &&
             rawResolution_ == fd.rawResolution_ &&
             parentName_ == fd.parentName_;
    }

    bool operator!=(const XCDFFieldDescriptor& fd) const {
      return !(*this == fd);
    }
};

#endif // XCDF_FIELD_DESCRIPTOR_INCLUDED_H
