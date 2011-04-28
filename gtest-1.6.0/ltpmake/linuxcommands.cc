#include "linuxcmd.h"
#include "gtest/gtest.h"

TEST(ldtest, LinuxCommands){
  EXPECT_EQ(0, ld()); 
}

TEST(ldtest1, LinuxCommands){
  EXPECT_EQ(0, lda(1)); 
}
TEST(ldtest2, LinuxCommands){
  EXPECT_EQ(0, lda(2)); 
}
TEST(ldtest3, LinuxCommands){
  EXPECT_EQ(0, lda(3)); 
}
TEST(ldtest4, LinuxCommands){
  EXPECT_EQ(0, lda(4)); 
}
TEST(ldtest5, LinuxCommands){
  EXPECT_EQ(0, lda(5)); 
}
TEST(ldtest6, LinuxCommands){
  EXPECT_EQ(0, lda(6)); 
}
TEST(ldtest7, LinuxCommands){
  EXPECT_EQ(0, lda(7)); 
}


TEST(artest, LinuxCommands){
  EXPECT_EQ(0, ar()); 
}

TEST(cptest, LinuxCommands){
  EXPECT_EQ(0, cp()); 
}

TEST(cpiotest, LinuxCommands){
  EXPECT_EQ(0, cpio()); 
}

TEST(crontest, LinuxCommands){
  EXPECT_EQ(0, cron()); 
}

TEST(filetest, LinuxCommands){
  EXPECT_EQ(0, file()); 
}

TEST(gziptest, LinuxCommands){
  EXPECT_EQ(0, gzip()); 
}

TEST(lddtest, LinuxCommands){
  EXPECT_EQ(0, ldd()); 
}

TEST(lntest, LinuxCommands){
  EXPECT_EQ(0, ln()); 
}

TEST(logrotatetest, LinuxCommands){
  EXPECT_EQ(0, logrotate()); 
}

TEST(mailtest, LinuxCommands){
  EXPECT_EQ(0, mail()); 
}

TEST(mkdirtest, LinuxCommands){
  EXPECT_EQ(0, mkdir()); 
}

TEST(mvtest, LinuxCommands){
  EXPECT_EQ(0, mv()); 
}

TEST(nmtest, LinuxCommands){
  EXPECT_EQ(0, nm()); 
}

TEST(objdumptest, LinuxCommands){
  EXPECT_EQ(0, objdump()); 
}

TEST(sizetest, LinuxCommands){
  EXPECT_EQ(0, size()); 
}

TEST(tartest, LinuxCommands){
  EXPECT_EQ(0, tar()); 
}

TEST(unziptest, LinuxCommands){
  EXPECT_EQ(0, unzip()); 
}



