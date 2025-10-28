//
// Created by admin on 28/10/2025.
//

#ifndef LANGUAGES_LAUNCH_MANAGER_HPP
#define LANGUAGES_LAUNCH_MANAGER_HPP
#include "defines.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

class Launch_manager
{
    public:
        Launch_manager();
        Launch_manager(int argc, char** argv);
        ~Launch_manager();

        static void debug();

    private:
        static int obj_nb; // current number of objects that uses this class
        vector<string> arguments; // args of the main function
        int args_number; // number of args entered

        static void v_single_instance();
        static Return_code manage_exceptions(std::function<void()> func);


        void arg_parse(char** argv);
};


#endif //LANGUAGES_LAUNCH_MANAGER_HPP