file(GLOB_RECURSE libeurointroduction_SRC
    "*.h"
    "*.cpp"
)

add_library(eurointroduction SHARED ${libeurointroduction_SRC})

target_link_libraries(eurointroduction ${Boost_LIBRARIES})

install(TARGETS eurointroduction DESTINATION lib)

#collect all headers from EzLogger dirs
file(GLOB ezlogger_HEADERS
    "EzLogger/*.h"
)

install(FILES ${ezlogger_HEADERS} DESTINATION ${header_destination}/EzLogger)

file(GLOB ezlogger_HEADERS
    "EzLogger/output/*.h"
)

install(FILES ${ezlogger_HEADERS} DESTINATION ${header_destination}/EzLogger)

file(GLOB ezlogger_HEADERS
    "EzLogger/output/formatters/*.h"
)

install(FILES ${ezlogger_HEADERS} DESTINATION ${header_destination}/EzLogger)

file(GLOB ezlogger_HEADERS
    "EzLogger/output/acceptors/*.h"
)

install(FILES ${ezlogger_HEADERS} DESTINATION ${header_destination}/EzLogger)

file(GLOB ezlogger_HEADERS
    "EzLogger/output/writers/*.h"
)

install(FILES ${ezlogger_HEADERS} DESTINATION ${header_destination}/EzLogger)

#ThreadSafeQueue
install(FILES ThreadSafeQueue/ThreadSafeQueue.h DESTINATION ${header_destination}/ThreadSafeQueue)

#Rendezvous
file(GLOB rendezvous_HEADERS
    "Rendezvous/*.h"
)

install(FILES ${rendezvous_HEADERS} DESTINATION ${header_destination}/Rendezvous)

#FunctionTimer
file(GLOB FunctionTimer_HEADERS
    "FunctionTimer/*.h"
)

install(FILES ${FunctionTimer_HEADERS} DESTINATION ${header_destination}/FunctionTimer)

#InterruptibleWait
file(GLOB InterruptibleWait_HEADERS
    "InterruptibleWait/*.h"
)

install(FILES ${InterruptibleWait_HEADERS} DESTINATION ${header_destination}/InterruptibleWait)

#Util
file(GLOB Util_HEADERS
    "Util/*.h"
)

install(FILES ${Util_HEADERS} DESTINATION ${header_destination}/Util)
