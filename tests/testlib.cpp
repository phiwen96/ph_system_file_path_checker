#include "headers.hpp"
#include <ph_system_file_path_checker/handles.hpp>



string my_file_name (string name = __builtin_FILE ())
{
    return name;
};





int main( int argc, char* argv[] ) {
    
    using input_reader = system_file_path_checker <handle_path, tag::constraints::path::must_exist, tag::constraints::file_type::can_be_any, handle_path_error, handle_file_type_error>;
    input_reader reader (my_file_name (), type_list <int, char> {}, type_list <string, int> {});

    int result = Catch::Session().run( argc, argv );


    return result;
}



