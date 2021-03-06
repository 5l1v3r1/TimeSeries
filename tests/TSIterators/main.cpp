

#include "gtest/gtest.h"
#include <TimeSeries.h>
#include <math.h>
#include <numeric>

// http://www.cplusplus.com/reference/iterator/
namespace
{
  class ATSIterator : public ::testing::Test
  {
  protected:
    ATSIterator() {}

    virtual ~ATSIterator() {}
  };

  TEST(ATSIterator, CanBeConstructed)
  {
    auto s  = TimeSeries::ScalarTs({0., 1., 2.}, {33., 22., 11.});
    auto it = std::begin(s);
    TimeSeries::ScalarTs::iterator_t it2{it};
    EXPECT_EQ(std::begin(s), it);
    EXPECT_EQ(it, it2);
  }

  TEST(ATSIterator, CanBeCopyConstructed)
  {
    auto s   = TimeSeries::ScalarTs({0., 1., 2.}, {33., 22., 11.});
    auto it  = std::begin(s);
    auto it2 = it;
    EXPECT_EQ(it2, it);
  }

  TEST(ATSIterator, CanDereference)
  {
    auto s  = TimeSeries::ScalarTs({0., 1., 2.}, {33., 22., 11.});
    auto it = s.begin();
    auto v  = *it;
    EXPECT_EQ(v.v(), 33.);
    EXPECT_EQ((*it).v(), 33.);
    EXPECT_EQ(it->v(), 33.);
  }

  TEST(ATSIterator, CanPrePostIncrement)
  {
    auto s  = TimeSeries::ScalarTs({0., 1., 2.}, {33., 22., 11.});
    auto it = s.begin();
    it++;
    EXPECT_EQ(it->v(), 22.);
    ++it;
    EXPECT_EQ(it->v(), 11.);
    EXPECT_EQ(*it--, 11.);
    EXPECT_EQ(*it, 22.);
  }

  TEST(ATSIterator, CanDoArithmetic)
  {
    auto s   = TimeSeries::ScalarTs({0., 1., 2.}, {33., 22., 11.});
    auto beg = s.begin();
    auto end = s.end();

    EXPECT_EQ((beg + 0)->v(), 33.);
    EXPECT_EQ((beg + 1)->v(), 22.);
    EXPECT_EQ((beg + 2)->v(), 11.);
    EXPECT_EQ((end - 1)->v(), 11.);
    EXPECT_EQ((1 + beg)->v(), 22.);
    EXPECT_EQ((-1 + end)->v(), 11.);
  }

  TEST(ATSIterator, CanCompare)
  {
    auto s   = TimeSeries::ScalarTs({0., 1., 2.}, {33., 22., 11.});
    auto it1 = std::begin(s);
    auto it2 = std::begin(s) + 1;
    EXPECT_LT(it1, it2);
    EXPECT_GT(it2, it1);
    EXPECT_EQ(it1, std::begin(s));
    EXPECT_NE(it1, it2);
  }

} // namespace

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
