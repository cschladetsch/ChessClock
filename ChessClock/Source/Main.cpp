#define SDL_MAIN_HANDLED

#include <exception>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "Gambit/StringUtil.hpp"

#include "ChessClock/Root.hpp"

using std::string;

using namespace boost::program_options;
using namespace boost::filesystem;

int main(int argc, char** argv)
{
    options_description desc("Options");

    string config = "main.json";
    desc.add_options()
        ("help", "Talk to Christian")
        ("resources", value<path>()->default_value("Resources"), "Set resources folder")
        ("config", value<path>()->default_value(config), "Set main config")
        ("verbosity", value<int>()->default_value(0), "Set Debug Verbosity")
        ("showFps", value<bool>()->default_value(false), "Show fps on screen")
        ;

    try
    {
        variables_map vm;
        positional_options_description p;
        store(command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        notify(vm);

        const auto resourcesPath = vm["resources"].as<path>();
        if (vm.find(config) != vm.end())
            config = vm["config"].as<string>();

        const auto configName = resourcesPath / config;
        typedef ChessClock::Root::Context Context;
        ChessClock::Root root(Gambit::NarrowString(configName.c_str()).c_str());

        return Context(
            resourcesPath.string().c_str(),
            [&root](Context &ctx) { return root.Setup(ctx); },
            [&root](Context &ctx) { return root.ProcessEvents(ctx); })
            .Run();
    }
    catch (std::exception &e)
    {
        std::cerr << fg::red << "Error: " << fg::yellow <<  e.what() << "\n";
    }

    return 1;
}

