#ifndef HANDLES_HPP
#define HANDLES_HPP

struct tag
{
    struct file_type
    {
        struct file
        {
            
        };
        
        struct folder
        {
            
        };
    };
    
    struct constraints
    {
        struct path
        {
            struct must_exist;
            struct must_not_exist;
        };
        
        struct file_type
        {
            struct must_be_file;
            struct must_be_folder;
            struct can_be_any;
        };
    };
};
#endif
