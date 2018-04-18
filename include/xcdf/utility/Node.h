
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

#ifndef XCDF_UTILITY_NODE_H_INCLUDED
#define XCDF_UTILITY_NODE_H_INCLUDED

#include <xcdf/utility/Symbol.h>
#include <xcdf/XCDFDefs.h>

template <typename T>
class Node : public Symbol {

  public:

    Node() { }
    virtual T operator[](unsigned index) const = 0;
    virtual unsigned GetSize() const = 0;

    // Need to know more about vector fields to understand
    // proper evaluation relationships.  Treat any node as
    // if it is derived from an XCDFField.  This is a bit
    // of a kludge IMO.
    virtual const std::string& GetName() const {return NO_PARENT;}

    // Set no parent by default
    virtual bool HasParent() const {return false;}
    virtual const std::string& GetParentName() const {return NO_PARENT;}

    // Support checking second-level node relationships
    virtual bool HasGrandparent() const {return false;}
    virtual const std::string& GetGrandparentName() const {return NO_PARENT;}
    virtual unsigned GetParentIndex(unsigned index) const {UNUSED(index); return 0;}
};

template <> inline
Node<int64_t>::Node() : Symbol(SIGNED_NODE) { }

template <> inline
Node<uint64_t>::Node() : Symbol(UNSIGNED_NODE) { }

template <> inline
Node<double>::Node() : Symbol(FLOATING_POINT_NODE) { }

/*
 *  Operations to check the parent relationship between two node objects
 */
enum NodeRelationType {
  // Scalar-only relationship
  SCALAR,

  // Scalar-Vector relationships
  SCALAR_FIRST,
  SCALAR_SECOND,

  // Vector-Vector relationships
  VECTOR_VECTOR,

  // nD vector to (n-1)D vector relationships
  PARENT_FIRST,
  PARENT_SECOND
};

/*
 *  Calculate the relation type between two nodes.  The following
 *  relations are supported:
 *  1. Scalar node compared with anything.  In case of vector,
 *     resulting size is the size of the vector node.
 *  2. Node derived from a vector field compared with a similar node from
 *     the same parent. The resulting size is the size of either field.
 *  3. Node derived from a 2D+ vector field compared with a node that is
 *     a sibling if its parent.
 */
template <typename T, typename U>
NodeRelationType GetRelationType(const Node<T>& n1, const Node<U>& n2) {
  if (!n1.HasParent() && !n2.HasParent()) {
    return SCALAR;
  }
  if (!n1.HasParent()) {
    return SCALAR_FIRST;
  }
  // n1 has a parent
  if (!n2.HasParent()) {
    return SCALAR_SECOND;
  }
  // both fields have a parent
  if (n1.GetParentName() == n2.GetParentName()) {
    return VECTOR_VECTOR;
  }
  // complex or non-existing node relationship.  Check if one node
  // is a sibling of the other node's parent
  if (n2.HasGrandparent()) {
    if (n2.GetGrandparentName() == n1.GetParentName()) {
      return PARENT_FIRST;
    }
  }

  if (n1.HasGrandparent()) {
    if (n1.GetGrandparentName() == n2.GetParentName()) {
      return PARENT_SECOND;
    }
  }

  // Don't use XCDFFatal here, since we may want to catch this
  XCDFFatal("Unable to compare vector fields " <<
                          n1.GetName() << " and " << n2.GetName());

  // Unreachable
  return SCALAR;
}

#endif // XCDF_UTILITY_NODE_H_INCLUDED
