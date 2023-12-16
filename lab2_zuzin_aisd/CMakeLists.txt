# CMakeList.txt: проект CMake для lab2_zuzin_aisd; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (lab2_zuzin_aisd "lab2_zuzin_aisd.cpp" "lab2_zuzin_aisd.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab2_zuzin_aisd PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
