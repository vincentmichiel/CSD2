//
//  block.hpp
//  pointers
//
//  Created by Vincent Van den Broeck on 03/11/2023.
//

#ifndef block_hpp
#define block_hpp

#include <stdio.h>

class Block {
private:
    int pSize;
public:
    void setSize(int size);
    int getSize();
};

#endif /* block_hpp */
