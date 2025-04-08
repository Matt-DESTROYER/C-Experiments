# C Dynamic Arrays

A simple library for dynamic (resizable on demand) arrays in C.

Use `build.sh` to build the shared library and demo project and use `setup.sh` (which automatically calls the build script) to install the header and library in the correct directories.

To link the library, use `-Wl,-rpath,/path/to/library`, you can see how this works in `build.sh`.

Contains the following methods (too lazy too write proper docs right now, the names are mostly self-explanatory, look inside `dynamic_array.h` for brief explanations):
```c
dynamic_array_t* make_dynamic_arr(size_t length);
size_t dynamic_arr_at(dynamic_array_t* array, int index);
void dynamic_arr_set(dynamic_array_t* array, int index, size_t value);
void dynamic_arr_resize(dynamic_array_t* array, size_t length);
void dynamic_arr_append(dynamic_array_t* array, size_t value);
void dynamic_arr_pop(dynamic_array_t* array);
void dynamic_arr_destroy(dynamic_array_t* array);
void dynamic_arr_print(dynamic_array_t* array, const char* name, char typeflag);
```

> Note: Currently only allocates `sizeof(size_t)` bytes for each element!!!
