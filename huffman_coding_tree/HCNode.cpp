
#include "HCNode.h"

using namespace std;

bool HCNode::operator<(const HCNode& other) {
          // if counts are different, just compare counts
        if(count != other.count) return count > other.count;
  
  // counts are equal. use symbol value to break tie.
  // (for this to work, internal HCNodes 
  // must have symb set.)
        return symbol < other.symbol;

}
