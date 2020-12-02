set(EXENAME example01)

set(SOURCES
    main.cpp
)

set(HEADERS
)

include_directories(
    ../../include
)

link_directories(
)

add_executable(${EXENAME} ${SOURCES})

set(LIBRARIES
    # QT5
    Qt5::Widgets
    Qt5::Sql

    BookFiler-Widget-QT-Task-Manager-LibShared
)

if(WIN32)
    set(LIBRARIES ${LIBRARIES}
        # Windows Libraries

    )
elseif(UNIX)
    set(LIBRARIES ${LIBRARIES}
        # Unix Libraries
        dl
    )
endif()

target_link_libraries(${EXENAME} ${LIBRARIES})
