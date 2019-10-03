SET(USE_EX_2 ON CACHE BOOL "Enable Exercise 2")
if(USE_EX_2)
	add_subdirectory(ExSes2)
endif(USE_EX_2)

SET(USE_EX_4 ON CACHE BOOL "Enable Exercise 4")
if(USE_EX_4)
	add_subdirectory(Ex4Asteroids)
endif(USE_EX_4)

SET(USE_EX_6 ON CACHE BOOL "Enable Exercise 6")
if(USE_EX_6)
	add_subdirectory(Ex6Wolf)
endif(USE_EX_6)