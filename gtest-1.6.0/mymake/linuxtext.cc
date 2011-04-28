// Step 1. Include necessary header files such that the stuff your                                          
// test logic needs is declared.                                                                            
//                                                                                                          
// Don't forget gtest.h, which declares the testing framework.     

#include "linuxcmd.h"
#include "gtest/gtest.h"

TEST(uname, SIMPLECALL){
  EXPECT_EQ(0,uname()); 
  ASSERT_FALSE(uname());
}
