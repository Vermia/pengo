#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libClases PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Entity.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Pengo.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hielo.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameManager.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Snobee.cc"
)

#Y donde se encuentran los .h
target_include_directories(libClases PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)
