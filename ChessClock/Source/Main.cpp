#define SDL_MAIN_HANDLED

//#include "KAI/Console/Console.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "ChessClock/Root.hpp"
#include "Gambit/ThirdParty/catch.hpp"

using namespace Gambit;
using namespace rang;
using namespace boost;
using namespace program_options;
using namespace filesystem;


int main(int argc, char** argv)
{
    options_description desc("Options");

    path resourcesFolder = "Resources/";
    string mainJson = "main.json";

    desc.add_options()
        ("help", "Talk to Christian")
        ("resources_dir", value<path>(&resourcesFolder)->default_value(resourcesFolder), "Set resources folder")
        ("main", value<path>(&resourcesFolder)->default_value(mainJson), "Set main config")
        ;

    positional_options_description p;
    p.add("input", -1);

    variables_map vm;
    store(command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    notify(vm);

    const string resourcesPath = argv[1];
    const string configName = resourcesPath + argv[2];
    ChessClock::Root root(configName.c_str());
    typedef ChessClock::Root::Context Context;

    return Context(resourcesPath.c_str(),
        [&root](Context &ctx) { return root.Setup(ctx); },
        [&root](Context &ctx) { return root.ProcessEvents(ctx); })
        .Run();
}

