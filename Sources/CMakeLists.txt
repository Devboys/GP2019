SET(A_USE_EX_2 ON CACHE BOOL "Enable Exercise 2")
if(A_USE_EX_2)
	add_subdirectory(ExSes2)
endif(A_USE_EX_2)

SET(A_USE_EX_4 ON CACHE BOOL "Enable Exercise 4")
if(A_USE_EX_4)
	add_subdirectory(Ex4Asteroids)
endif(A_USE_EX_4)

SET(A_USE_EX_6 ON CACHE BOOL "Enable Exercise 6")
if(A_USE_EX_6)
	add_subdirectory(Ex6Wolf)
endif(A_USE_EX_6)