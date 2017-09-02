
set(SOURCE_FILES mq_sysV.cpp mq_sysV.h pimpl_mq_sysV.h pimpl_mq_sysV.cpp)
add_library(MQ_systemV SHARED ${SOURCE_FILES})