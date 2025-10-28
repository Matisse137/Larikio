//
// Created by admin on 28/10/2025.
//

#include "../include/launch_manager.hpp"

#include "exceptions.hpp"

int Launch_manager::obj_nb = 0;

Launch_manager::Launch_manager() : arguments{}, args_number(0)
{
    obj_nb++;
    manage_exceptions(v_single_instance);

}

Launch_manager::Launch_manager(int argc, char **argv)
{
    manage_exceptions(v_single_instance);
    Launch_manager::obj_nb++;

    this->args_number = argc;
    arg_parse(argv);
}

Launch_manager::~Launch_manager()
{
    Launch_manager::obj_nb--;
}

void Launch_manager::debug()
{
    std::cout << "var obj_nb : " << Launch_manager::obj_nb << std::endl;
}

Return_code Launch_manager::manage_exceptions(std::function<void()> func)
{
    try
    {
        func();
    }
    catch (const Exceptions &e)
    {
        switch (e.type())
        {
            case Exceptions::NOT_SINGLE:
                cerr << "'Launch_manager' CLASS CANNOT BE MULTIPLE !" << endl;
                exit(1);
                break;
            default:
                cerr << "UNKNOW ERROR, BEWARE !" << endl;
        }
    }

    return Return_code::OK;
}

void Launch_manager::v_single_instance()
{
    if (Launch_manager::obj_nb > 1)
    {
        throw Exceptions(Exceptions::NOT_SINGLE, "UNAUTHORIZED INSTANCE CREATED");
    }
}

void Launch_manager::arg_parse(char *argv[])
{
    for (int i = 0; i < this->args_number + 1; i++)
    {
        this->arguments.push_back(argv[i]);
    }
}
