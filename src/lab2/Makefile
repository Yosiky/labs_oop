CC			=	g++
STD			=	-std=c++20
# CXXFLAGS	=	-Wextra -Werror -Wall

.PHONY: info clean

info:
	@echo "make clean - delete all executable files"
	@echo "make <file_name without '.cpp'> - compile a chosen file"
	@echo "Accessed files:"
	@echo "\t- base_inheritance"
	@echo "\t- c_cast"
	@echo "\t- virtual_methods"
	@echo "\t- abstract_class"
	@echo "\t- test - if you want to run your programm"
	@echo "\t- dynamic_cast"

clean:
	rm -rf base_inheritance
	rm -rf c_cast
	rm -rf virtual_methods
	rm -rf abstract_class
	rm -rf test
	rm -rf dynamic_cast

virtual_methods: virtual_methods.cpp
	$(CC) $(STD) $(CXXFLAGS) -o $@ $<

abstract_class: abstract_class.cpp
	$(CC) $(STD) $(CXXFLAGS) -o $@ $<

base_inheritance: base_inheritance.cpp 
	$(CC) $(STD) $(CXXFLAGS) -o $@ $<

c_cast: c_cast.cpp 
	$(CC) $(STD) $(CXXFLAGS) -o $@ $<

dynamic_cast: dynamic_cast.cpp
	$(CC) $(STD) $(CXXFLAGS) -o $@ $<


