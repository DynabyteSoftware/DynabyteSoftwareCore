find_package(Boost REQUIRED COMPONENTS system)

set(NETWORKING_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE NETWORKING_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE NETWORKING_HEADERS "${NETWORKING_INCLUDE}/*.h")

if(Boost_FOUND)
  set(BOOST_IMPLEMENTATION_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/BoostImplementation/include")
  file(GLOB_RECURSE BOOST_IMPLEMENTATION_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/BoostImplementation/src/*.cpp")
  file(GLOB_RECURSE BOOST_IMPLEMENTATION_HEADERS "${BOOST_IMPLEMENTATION_INCLUDE}/*.h")
endif(Boost_FOUND)

add_library(NetworkingDynamic SHARED ${NETWORKING_HEADERS} ${NETWORKING_SOURCE}
                                     ${BOOST_IMPLEMENTATION_HEADERS} ${BOOST_IMPLEMENTATION_SOURCE})
set_target_properties(NetworkingDynamic PROPERTIES OUTPUT_NAME Networking)
target_include_directories(NetworkingDynamic
                           PUBLIC ${NETWORKING_INCLUDE}
                           PRIVATE ${BOOST_IMPLEMENTATION_INCLUDE})
target_compile_definitions(NetworkingDynamic PRIVATE NETWORKING_DYNAMIC $<$<BOOL:Boost_FOUND>:USE_BOOST>)
target_link_libraries(NetworkingDynamic CoreDynamic Boost::system)