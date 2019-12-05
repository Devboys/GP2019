SET(A_USE_EX_02 ON CACHE BOOL "Enable Exercise 2")
if(A_USE_EX_02)
	add_subdirectory(ExSes2)
endif(A_USE_EX_02)

SET(A_USE_EX_04 ON CACHE BOOL "Enable Exercise 4")
if(A_USE_EX_04)
	add_subdirectory(Ex4Asteroids)
endif(A_USE_EX_04)

SET(A_USE_EX_06 ON CACHE BOOL "Enable Exercise 6")
if(A_USE_EX_06)
	add_subdirectory(Ex6Wolf)
endif(A_USE_EX_06)

SET(A_USE_EX_08 ON CACHE BOOL "Enable Exercise 8")
if(A_USE_EX_08)
	add_subdirectory(Ex8Bird)
endif(A_USE_EX_08)

SET(A_USE_EX_10 ON CACHE BOOL "Enable Exercise 10")
if(A_USE_EX_10)
	add_subdirectory(Ex10Platformer)
endif(A_USE_EX_10)

SET(A_USE_LotM ON CACHE BOOL "Add Light of the Moon")
if(A_USE_LotM)
	add_subdirectory(LightOfTheMoon)
endif(A_USE_LotM)