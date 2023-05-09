#include "maths.h"
#include "gtest/gtest.h"

TEST(AddTest, Valid)
{
  ASSERT_EQ(15,addition(7,8));
  ASSERT_EQ(0,addition(0,0));
  ASSERT_EQ(-2,addition(7,-9));
}

TEST(AddTest, NonValid)
{
  ASSERT_NE(11,addition(7,8));
  ASSERT_NE(1,addition(0,0));
  ASSERT_NE(-1,addition(7,-9));
}

TEST(SubtractTest, Valid)
{
  ASSERT_EQ(-1,soustraction(7,8));
  ASSERT_EQ(0,soustraction(0,0));
  ASSERT_EQ(16,soustraction(7,-9));
}

TEST(SubtractTest, NonValid)
{
  ASSERT_NE(11,soustraction(7,8));
  ASSERT_NE(1,soustraction(0,0));
  ASSERT_NE(-1,soustraction(7,-9));
}
TEST(MultiplyTest, Valid)
{
  ASSERT_EQ(56,multiplication(7,8));
  ASSERT_EQ(0,multiplication(0,0));
  ASSERT_EQ(-63,multiplication(7,-9));
}

TEST(MultiplyTest, NonValid)
{
  ASSERT_NE(55,multiplication(7,8));
  ASSERT_NE(1,multiplication(0,0));
  ASSERT_NE(-1,multiplication(7,-9));
}

TEST(DivTest, Valid)
{
  int etat=0;
  float result = division(5,2,&etat);
  ASSERT_EQ(etat,1);
  ASSERT_FLOAT_EQ(result,2.5);
}

TEST(DivTest, NonValid)
{
  int etat = 0;
  float resukt = division(5,2,&etat);
  ASSERT_EQ(etat,1);
  ASSERT_NE(1.0,division(5,2,&etat));
}

TEST(DivTest, UnValid)
{
	int etat=0;
	float result = division(2,0,&etat);
	ASSERT_EQ(etat,0);
}




int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
