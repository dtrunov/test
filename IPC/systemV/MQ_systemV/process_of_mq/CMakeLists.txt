include_directories(../mq)
add_executable(Sender sender.cpp)
target_link_libraries(Sender MQ_systemV)
add_executable(Receiver receiver.cpp)
target_link_libraries(Receiver MQ_systemV)
add_executable(StepicTest test.cpp)
target_link_libraries(StepicTest MQ_systemV)