#
# Author: Jin Yuqi (Ricky)
# Email: 179386223@qq.com
# Date: 2018.08.08
#

find_package(GTest REQUIRED)

add_executable(ut_sedump ut_sedump.cpp)
target_link_libraries(ut_sedump PRIVATE GTest::Main sedump)
