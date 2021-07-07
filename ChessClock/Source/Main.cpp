#define SDL_MAIN_HANDLED

#include <codecvt>
#include <exception>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "ChessClock/Root.hpp"

using std::string;

using namespace boost;
using namespace program_options;
using namespace filesystem;

using Gambit::Logger;

#ifdef WIN32
    #pragma warning (disable:4996)
#endif

std::string NarrowString(const std::wstring &str)
{
    std::wstring_convert<
        std::codecvt_utf8_utf16< std::wstring::value_type >,
        std::wstring::value_type
    > utf16conv;
    return utf16conv.to_bytes(str);
}

Logger _log{ "Main" };

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
        ChessClock::Root root(NarrowString(configName.c_str()).c_str());

        return Context(
            resourcesPath.string().c_str(),
            [&root](Context &ctx) { return root.Setup(ctx); },
            [&root](Context &ctx) { return root.ProcessEvents(ctx); })
            .Run();
    }
    catch (std::exception &e)
    {
        std::cerr << fg::red << "Failed: " << fg::yellow <<  e.what() << "\n";
    }

    return 1;
}

